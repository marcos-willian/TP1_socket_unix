Simple: STserver STclient

STserver: Simple_talk_Server.c
	gcc Simple_talk_Server.c -o STserver

STclient: Simple_talk_client.c
	gcc Simple_talk_client.c -o STclient


clean: 
	rm *.o