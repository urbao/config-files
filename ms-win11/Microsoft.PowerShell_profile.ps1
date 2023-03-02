# oh-my-posh
oh-my-posh init pwsh --config "$env:POSH_THEMES_PATH\multiverse-neon.omp.json" | Invoke-Expression

# Terminal-Icons conifgure
Import-Module Terminal-Icons
# PSReadline
Set-PSReadLineOption -PredictionSource History
Set-PSReadLineOption -PredictionView ListView
Set-PSReadlineKeyHandler -Key Tab -Function MenuComplete

# Alias Part
Set-Alias -Name vim -Value nvim
Set-Alias ll ls
Set-Alias grep findstr
Set-Alias -Name g -Value git
Set-Alias -Name top -Value btop
Set-Alias -Name his -Value history
Set-Alias -Name psd -Value pushd
Set-Alias -Name ppd -Value popd
Set-Alias -Name touch -Value New-Item
Set-Alias -Name tr -Value recycle-bin

# Utilities
function which($command){
        Get-Command -Name $command -ErrorAction SilentlyContinue|
                Select-Object -ExpandProperty Path -ErrorAction SilentlyContinue
}

function rmrf {
     <#
        .DESCRIPTION
        Deletes the specified file or directory.

        .PARAMETER target
        Target file or directory to be deleted.

        .NOTES
        This is an equivalent command of "rm -rf" in Unix-like systems.
        #>
    Param(
        [Parameter(Mandatory=$true)]
        [string]$Target
    )
    Remove-Item -Recurse -Force $Target
}

<# function that suppports jump back prev directory like zsh#>
function ..{cd ..}
function ...{
    cd ..
    cd ..
}
function ....{
    cd ..
    cd ..
    cd ..
}
