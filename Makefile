UDP: UDPserver UDPclient

UDPserver: UDPserver.c
	gcc UDPserver.c -o UDPserver

UDPclient: client.c
	gcc UDPclient.c -o UDPclient
	