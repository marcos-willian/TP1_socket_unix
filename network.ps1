$remoteport = bash.exe -c "ip addr show eth0 | grep 'inet\b' | awk '{print $2}' | cut -d/ -f1" 
$found = $remoteport -match '\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}'; 
if ( $found ) { 
    $remoteport = $matches[0]; 
} else { 
    Write-Output "The Script Exited, the ip address of WSL 2 cannot be found"; 
    exit; 
} 
$ports = @(3000, 3001, 5000, 5500, 19000, 19002, 19006); 
Invoke-Expression "netsh interface portproxy reset"; 
for ( $i = 0; $i -lt $ports.length; $i++ ) { 
    $port = $ports[$i]; Invoke-Expression "netsh interface portproxy add v4tov4 listenport=$port connectport=$port connectaddress=$remoteport"; 
} Invoke-Expression "netsh interface portproxy show v4tov4";