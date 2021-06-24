UDP: UDPserver UDPclient

UDPserver: UDPserver.c
	gcc UDPserver.c -o UDPserver

UDPclient: UDPclient.c
	gcc UDPclient.c -o UDPclient


TCP: TCPserver TCPclient

TCPserver: TCPserver.c
	gcc TCPserver.c -o TCPserver

TCPclient: client.c
	gcc TCPclient.c -o TCPclient