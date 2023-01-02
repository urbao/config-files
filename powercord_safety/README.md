# Power-Cord-Calculator
## About
#### Environment: Ubuntu 22.04.1 LTS(64bit)<br>
#### Language: Python 3.10.6<br>
#### Text Editor: Micro Text Editor<br>

## Analyze Circuit 
![circuit](https://user-images.githubusercontent.com/83464781/208340038-2718c412-7313-4adb-b188-3c3d9ebeda33.png)<br><br>
## Method:
### Run command 'python3 ~/TargetDirectory/main.py' in terminal
1.Choose type and value of components as you desire<br>
![image](https://user-images.githubusercontent.com/83464781/208340230-cfa327be-ffe8-44e2-beef-76da02d6974d.png)<br><br>
2.Press Enter to see result<br>
![image](https://user-images.githubusercontent.com/83464781/208340279-067f85f4-5e97-4277-966c-d211172c6a75.png)<br><br>
3.Check Total Voltage and Total Current diagram that pops out<br>
![image](https://user-images.githubusercontent.com/83464781/208340406-33fdbfd3-2c49-4b5b-b66f-f01e499466e0.png)<br><br>
4.Analyze Result has three different three conditions<br>
(a) 0W to 1150W[SAFE]:![image](https://user-images.githubusercontent.com/83464781/208340605-9ddd2895-0559-438a-90b9-c663f7df5fb9.png)<br><br>
(b) 1150W to 1650W[WARNING]:![image](https://user-images.githubusercontent.com/83464781/208340715-0a505925-ebc4-4b62-915b-40782ef8bc60.png)<br><br>
(c) Bigger than 1650W[DANGEROUS]:<br>![image](https://user-images.githubusercontent.com/83464781/208340786-227d842c-234c-4277-b571-561842e2506c.png)<br>
### (If Circuit Breaker operates, then we need to reset all components to prevent circuits from being destoryed)<br><br>
## Others:
### Test Setup Parameter:<br>
![setup](https://user-images.githubusercontent.com/83464781/208341024-d5759873-a600-49a0-bf10-0e3692c3e48d.png)<br><br>
### Pspice Simulation result:<br>
#### Good:<br>
![good](https://user-images.githubusercontent.com/83464781/208341044-b4f12296-ebbe-4817-b77e-4a1046986467.png)<br><br>
#### Warning:<br>
![warning](https://user-images.githubusercontent.com/83464781/208341068-b0e319c0-55d5-49d1-aa61-614ec9cf21b2.png)<br><br>
#### Dangerous:<br>
![dangerous](https://user-images.githubusercontent.com/83464781/208341090-159dc808-ae8e-4120-95e9-d3b33687f5c9.png)<br><br>
