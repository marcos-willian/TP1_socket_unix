all: Simple EXP1 EXP2

Simple: STserver STclient

STserver: Simple_talk_Server.c
	gcc Simple_talk_Server.c -o STserver

STclient: Simple_talk_client.c
	gcc Simple_talk_client.c -o STclient

EXP1: EXP1_Client.c
	gcc EXP1_Client.c -o EXP1client

EXP2: EXP2server EXP2client

EXP2server: EXP2_Server.c
	gcc EXP2_Server.c -o EXP2server

EXP2client: EXP2_Client.c
	gcc -g EXP2_Client.c -o EXP2client

clean: 
	rm STserver STclient EXP1client EXP2server EXP2client