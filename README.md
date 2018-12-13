# List_IP_Dns

Author: Lyubov Sidlinskaya


Contents of Directory:
	listIPDNS.c
	makefile
	Readme.txt

HW5 : ListIPDNS

	This program accepts cmd line arguments for the subnet and network address.
	It then determines the number of hosts possible for the given subnet and prints their ip address and DNS name. 

	The first step the program takes is determining the number of bits allocated for the network portion of the subnet mask / address. It then calculates the space left for the host address. Next it calculates the max number of hosts possible
	for the given subnet and network address. Then it loops through and for each
	ip address it prints the ip and Dns name. 


To run file using MAKEFILE:
	make -f makefile


To run file manually:

	gcc listIPDNS.c -o listIPDNS
	./listIPDNS.exe subnet network_addr

To run file on linux: 
	Link math library using -lm

	gcc listIPDNS.c -o listIPDNS -lm
	./listIPDNS subnet network_addr
