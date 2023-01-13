from sympy import *
# Global Definition of 60Hz, Omega=120*PI
import math
omega=120*math.pi


# colorful output
def color_output(color, line, newline):
    if color=="red":
        code="31m"
    elif color=="yellow":
        code="33m"
    elif color=="green":
        code="32m"
    elif color=="cyan":
        code="36m"
    elif color=="purple":
        code="35m"
    else:
        code="37m" # white
    if newline:
        print("\033[1;"+code+line+"\033[0m")
    else:
        print("\033[1;"+code+line+"\033[0m", end=" ")
    return

# get desired component type
def get_type():
    while(True):
        color_output("purple", "Choose component type(R/L/C):", False)
        ans=input()
        if ans=="R" or ans=="r" or ans=="L" or ans=="l" or ans=="C" or ans=="c":
            return ans
        else:
            color_output("white", "Invalid component type", True)

# get component value
def get_val(ans):
    if ans=="C" or ans=="c":
        color_output("cyan", "Enter component value(Unit: nF):", False)
        answer=input()
        return float(answer)*pow(10,-9)
    elif ans=="L" or ans=="l":
        color_output("cyan", "Enter component value(Unit: mH):", False)
        answer=input()
        return float(answer)*pow(10,-3)
    elif ans=="R" or ans=="r":
        color_output("cyan", "Enter component value(Unit: Ω):", False)
        answer=input()
        return answer

# transfer given value to impedance based on its type
def to_impedance(val, omega, typ):
    if typ=="C" or typ=="c":
        return "-"+str(round(1/(float(val)*omega),3))+"j"
    elif typ=="L" or typ=="l":
        return str(round(float(val)*omega,3))+"j"
    else:
        return str(val)+"+0j"

# Series connection total impendance
def series_Z(val1, type1, val2, type2):
    z1=complex(to_impedance(val1, omega, type1))
    z2=complex(to_impedance(val2, omega, type2))
    result=complex(z1+z2)
    return complex(round(result.real,3), round(result.imag, 3))
    
# Parallel connection total impedance
def parallel_Z(val3, type3, val4, type4):
    z3=complex(to_impedance(val3, omega, type3))
    z4=complex(to_impedance(val4, omega, type4))
    if z3+z4==0:
        return 0
    else:
        result=complex((z3*z4)/(z3+z4))
        return complex(round(result.real,3), round(result.imag, 3))
        
# circuit analyze
def circuit_analyze(Z1, Z2):
    Equa=Matrix([[str(Z1), "-("+str(Z1)+")", "110"], [str(Z1), "-("+str(complex(Z1)+complex(Z2))+")", "0"]])
    return Equa.evalf().rref()

# replace '*' and 'I' symbol with 'j'
def reorder(curr):
    curr=curr.replace(" ", "")
    curr=curr.replace("*", "")
    curr=curr.replace("I", "j")
    return str(curr)
    
# find current magnitude
def curr_mag(current):
    return str(round(float(abs(complex(current))),2))

# find current phase
def curr_phase(current):
    import cmath
    if cmath.phase(complex(current))>=0:
        result="+"+str(round(float(cmath.phase(complex(current))),2))
    else:
        result=str(round(float(cmath.phase(complex(current))),2))
    return result

# calculate power
def cal_power(Vm, Im, phaseV, phaseI):
    import numpy as np
    result=0.5*float(Vm)*float(Im)*np.cos(float(phaseV)-float(phaseI))
    return result
    
# print out current curve
def plot_result(mag, omega, phase, title):
    import numpy as np
    import matplotlib.pyplot as plt
    time=np.arange(0,0.05,0.0001)
    volt=110.00*np.sin(float(omega)*time+0.0)
    curr=float(mag)*np.sin(float(omega)*time+float(phase))
    plt.plot(time, volt, label='Voltage', linewidth=4)
    plt.plot(time, curr, label='Current', linewidth=4)
    plt.legend()
    plt.title(title)
    plt.xlabel('Time')
    plt.ylabel('Amplitude')
    plt.grid(True, which='both')
    plt.axhline(y=0, color='k')
    plt.show()
    return

def setup(resetORnot):
    # get value and types of components
    color_output("yellow", "=====Z1 Part=====", True)
    Z1_type=get_type();
    Z1_val=get_val(Z1_type);
    color_output("yellow", "=====Z2 Part=====", True)
    Z2_type=get_type();
    Z2_val=get_val(Z2_type);
    color_output("yellow", "=====Z3 Part=====", True)
    Z3_type=get_type();
    Z3_val=get_val(Z3_type);
    color_output("yellow", "=====Z4 Part=====", True)
    Z4_type=get_type();
    Z4_val=get_val(Z4_type);
    # calculate each component's impedance and print out
    color_output("yellow", "\n====Impedance====", True)
    color_output("purple", "Z1:",False)
    color_output("cyan", to_impedance(Z1_val, omega, Z1_type), False)
    color_output("cyan", "(Ω)", True)
    color_output("purple", "Z2:",False)
    color_output("cyan", to_impedance(Z2_val, omega, Z2_type), False)
    color_output("cyan", "(Ω)", True)
    color_output("purple", "Z3:",False)
    color_output("cyan", to_impedance(Z3_val, omega, Z3_type), False)
    color_output("cyan", "(Ω)", True)
    color_output("purple", "Z4:",False)
    color_output("cyan", to_impedance(Z4_val, omega, Z4_type), False)
    color_output("cyan", "(Ω)", True)
    # find Series and Parallel connection
    seriesZ=series_Z(Z1_val, Z1_type, Z2_val, Z2_type)
    parallelZ=parallel_Z(Z3_val, Z3_type, Z4_val, Z4_type)
    seriesZ=str(seriesZ).replace('(','')
    parallelZ=str(parallelZ).replace('(','')
    seriesZ=str(seriesZ).replace(')','')
    parallelZ=str(parallelZ).replace(')','')
    color_output("green","Series:", False)
    color_output("yellow", str(seriesZ), False)
    color_output("yellow", "(Ω)", True)
    color_output("green","Parallel:", False)
    color_output("yellow", str(parallelZ), False)
    color_output("yellow", "(Ω)", True)
    # analyze result of circuit
    result=circuit_analyze(seriesZ, parallelZ)
    color_output("red", "\n=====Result=====", True)
    it=reorder(str(result[0][2]))
    It=curr_mag(it)+"sin(120πt"+curr_phase(it)+")"
    color_output("cyan", "V_source:", False)
    color_output("white", "110sin(120πt+0.0)(V)", True)
    color_output("cyan", "I_total:", False)
    color_output("white", It+"(A)", True)
    color_output("cyan", "Real Power:", False)
    color_output("white", str(round(cal_power(110.0,curr_mag(it),0.0, curr_phase(it)),3))+"(W)", True)
    # compare safe or not
    color_output("purple", "Analyze result:", False)
    if round(cal_power(110.0,curr_mag(it),0.0, curr_phase(it)),3)>1650:
        color_output("red", "[DANGEROUS]", True)
        color_output("red", "\nCiruit Breaker Operation[Done]", True)
        color_output("cyan", "V_source:", False)
        color_output("white", "110sin(120πt+0.0)(V)", True)
        color_output("cyan", "I_total:", False)
        color_output("white", "0(A)", True)
        color_output("white", "\n===Plz Reset All Components for your safety===", True)
        setup(True)
    elif 1650-round(cal_power(110.0,curr_mag(it),0.0, curr_phase(it)),3)<500:
        color_output("yellow", "[WARNING]", True)
    else:
        color_output("green", "[SAFE]", True)
    # print out waveform
    if resetORnot==False:
        plot_result(curr_mag(it), omega, curr_phase(it), 'First Analyze Result')
    else:
        plot_result(curr_mag(it), omega, curr_phase(it), 'After Reset Components')
    return

##-----------Main Part of Code-----------##
color_output("red", "-- Max Tolerable Power:", False)
color_output("red", "1650(W)", True)
color_output("cyan", "-- Voltage Source Amplitude:", False)
color_output("yellow", "110(V)", True)
color_output("cyan", "-- Voltage Source Omega:", False)
color_output("yellow", "120π(60Hz)", True)
color_output("cyan", "-- Voltage Source Phase:", False)
color_output("yellow", "0\n", True)
setup(False)
