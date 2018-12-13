//********************************************************************
//
// Author: Lyubov Sidlinskaya
//
// To run file:
// gcc listIPDNS.c -o listIPDNS
// ./listIPDNS.exe subnet network_addr
//
// To run file on linux: 
// Link math library using -lm
//
// gcc listIPDNS.c -o listIPDNS -lm
// ./listIPDNS subnet network_addr
//
//********************************************************************


#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <math.h>


//********************************************************************
// Get_Mask_Info  Function
//
// This function accepts the subnet mask as input and
// calculates the bits needed for subnet mask / network.
// The bits needed for the network are returned to the calling function.
//
// Return Value
// ------------
// count 		int 	Counter for the bits for the network address                 
//
// Value Parameters
// ----------------
// NONE
//
// Reference Parameters
// --------------------
// mask_prefix 	char	The subnet address
//
// Local Variables
// ---------------
// int_binary 	int 	Int value for success or failure
// bin_address	in_addr Holds the numeric binary form of address	
// mask 		in_addr Struct to hold the binary form
// hl_mask 		uint32  Host long version of mask addr
// count 		int 	Counter for the bit values
// bit_one 		u_int	Holds value for bit, of 1 or 0
//
//*******************************************************************
static int get_mask_info(const char *mask_prefix)
{
	int int_binary;
	struct in_addr bin_address;

	// Convert address into numeric binary form
	int_binary = inet_pton(AF_INET, mask_prefix, &bin_address);

	if (int_binary == 0)
		return -1;

	struct in_addr mask = bin_address;
	uint32_t hl_mask = ntohl(mask.s_addr);

	int count = 0;
	unsigned int bit_one = 0;

	// Count the number of bits needed for the network address.
	while (hl_mask > 0) {
		if (hl_mask & 1) {
			bit_one = 1;
			count++;		// Increment counter
		} else {
			if (bit_one) {
				return -1;
			}
		}
		hl_mask >>= 1;
	}
	// Return the bit count
	return count;
}



//********************************************************************
// Main  Function
//
// This function does the main work for this program. It accepts cmd line 
// arguments for the subnet and network address. It then determines the
// number of hosts possible for the given subnet and prints their ip address
// and DNS name. 
//
// Return Value
// ------------
// count 		int 	Counter for the bits for the network address                 
//
// Value Parameters
// ----------------
// argc			int		Arguments from command line
// 
// Reference Parameters
// --------------------
// argv[]		char	Array holding arguments
//
// Local Variables
// ---------------
// hostptr			hostent 	Holds the info of Ip address	
// ip_addr			in_addr 	Struct for holding the start IP 
// new_addr 		in_addr 	Struct which holds pointer to the starting IP value
// subnet_mask 		char		Holds the subnet mask passed in as cmd arg
// network_addr 	char		Holds the network address passed in as cmd arg
// subnet_mask_long u_long		Unsigned long of subnet mask
// netwrk_addr_long u_lomg		Unsigned long of network address
// net_mask			int 		The number of bits of network
// host_mask		int 		The number of bits for host
// max_hosts		int 		The number for host allowed for subnet
// ip_start			u_long 		Starting address for ip's
// host_count		int 		Counter for hosts
//*******************************************************************

int main(int argc, char* argv[]) {

	struct in_addr* new_addr;
	struct hostent *hostptr;
	struct in_addr ip_addr;

	// Variables for the file being received

	if (argv[1] == NULL){
		printf("Enter the Subnet Mask as first cmd argument.\n");
		printf("Enter the Network Address as second cmd argument.");
		exit(1);
	}
	if (argv[2] == NULL){
		printf("Enter the Subnet Mask as first cmd argument.\n");
		printf("Enter the Network Address as second cmd argument.");
		exit(1);
	}
	
	// First argument: Subnet Mask address	
	char *subnet_mask = argv[1];
	// Second argument: Network Address
	char *network_addr = argv[2];

	// Convert to decimal notation
	u_long subnet_mask_long = inet_addr(subnet_mask);
	u_long network_addr_long = inet_addr(network_addr);

	// The number of bits for subnet mask
	int net_mask = get_mask_info(subnet_mask);
	// The number of bits for host mask
	int host_mask = 32 - net_mask ;
	// Number of possible hosts on mask
	int max_hosts = pow(2, host_mask) - 2;
	
	// Print the bits available.
	printf("Netmask is: %d bits.  ", net_mask);
	printf("Hostmask is: %d bits.  ", host_mask);
	printf("Max hosts is: %d\n\n", max_hosts);

	// Get the starting ip address
	unsigned long ip_start = subnet_mask_long & network_addr_long;

	// Set the start value in the struct
    ip_addr.s_addr = ip_start;

    // Counter for max number of hosts possible for subnet
	int host_count = 1;

	while (host_count <= max_hosts){
		// Increment the address by 1 & reassign
		ip_addr.s_addr = htonl(ntohl(ip_addr.s_addr) + 1);
		new_addr = (struct in_addr *) &ip_addr;

		// Get host info by IP address
		hostptr = gethostbyaddr(new_addr, 4, AF_INET);
		if( hostptr != NULL)
		{
			printf("%s", inet_ntoa(*new_addr));		// Print the Address
			printf("\t%s\n",  hostptr->h_name);		// Print name
		}
		// If hostptr is NULL
		else{
			printf("%s", inet_ntoa(*new_addr));
			printf(" \tHost cannot be reached\n");
		}
		host_count++; // Increment counter
		
	}
	printf("\n\n ~ End of found hosts");
	exit(1);

}
