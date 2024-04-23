// CARAMIDA-STOIAN PETRISOR-CRISTIAN 324CB
#include "queue.h"
#include "lib.h"
#include "protocols.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>

struct arp_table_entry *arp_table; // Tabelul ARP
struct route_table_entry *rtable; // Tabelul de rutare

int arp_table_len; // Lungimea tabelului ARP
int rtable_len; // Lungimea tabelului de rutare

struct arp_table_entry *get_arp_entry (uint32_t ip_dest){
    int i = 0;
    while(i < arp_table_len) {
        if(arp_table[i].ip == ip_dest)
            return &arp_table[i];
        i++;
    }
    return NULL;
}


struct route_table_entry *longest_prefix_match(uint32_t ip_dest, struct route_table_entry *rtable) {
	int left = 0;
	int right = rtable_len;
	int pos_max_mask = -1;

	while (left <= right) {
		int middle = (left + right) / 2;
		// Extrage mastile si prefixele
		uint32_t middle_prefix = ntohl(rtable[middle].prefix);
		uint32_t middle_mask = ntohl(rtable[middle].mask);
		uint32_t pos_max_rtable  = ntohl(rtable[pos_max_mask].mask);
		uint32_t prefix = middle_prefix;
		uint32_t dest_mask = ip_dest & middle_mask;

		// Cauta cea mai lunga potrivire a prefixului
		if (dest_mask == prefix) {  
			if (pos_max_mask < 0 || middle_mask > pos_max_rtable) {
				left = middle + 1;
				pos_max_mask = middle;
			} else {
				left = middle + 1;
			}
		} 

		// Cauta adresa IP corecta
		if (dest_mask < prefix) {
			right = middle - 1;
		} else { 
			left = middle + 1;
		}
	}
	return &rtable[pos_max_mask];
}

int comp(const void *a, const void *b) {
	struct route_table_entry *aa = (struct route_table_entry*) a;
	struct route_table_entry *bb = (struct route_table_entry*) b;

	// Extrage IP-urile si mastile
	uint32_t aa_ip = aa->prefix & aa->mask;
	uint32_t bb_ip = bb->prefix & bb->mask;
	uint32_t aa_mask = ntohl(aa->mask);
	uint32_t bb_mask = ntohl(bb->mask);

	// Pentru IP-urile egale, compara mastile
	if (aa_ip == bb_ip) {
		return (aa_mask > bb_mask);
	}

	// Compara IP-urile
	return ntohl(aa_ip) > ntohl(bb_ip);
}

void build_icmphdr(struct icmphdr *icmp, uint8_t type) {
	icmp->type = type;
	icmp->un.echo.id = 0;
	icmp->code = 0;
	icmp->un.echo.sequence = 0;
	icmp->checksum = checksum((uint16_t *)icmp, sizeof(struct icmphdr));
}

int main(int argc, char *argv[])
{
	char buf[MAX_PACKET_LEN];
	// Do not modify this line
	init(argc - 2, argv + 2);

	rtable = malloc(sizeof(struct route_table_entry) * 100000);
	if (rtable == NULL) {
		printf("Error: failed to allocate memory for routing table.\n");
		free(rtable);
		return 1;
	}

	arp_table = malloc(sizeof(struct arp_table_entry) * 100);
	if (arp_table == NULL) {
		printf("Error: failed to allocate memory for ARP table.\n");
		free(rtable);
    	return 1;
	}

	rtable_len = read_rtable(argv[1], rtable);
	arp_table_len = parse_arp_table("arp_table.txt", arp_table);

	// Sorteaza tabela de rutare dupa adresa IP si masca de subretea
	qsort(rtable, rtable_len, sizeof(struct route_table_entry), comp);

	while (1) {
		// Primeste un pachet de la orice legatura si verifica erorile
		int interface;
		size_t len;

		interface = recv_from_any_link(buf, &len);
		if(interface < 0){
			printf("Error: didn't receive packets.\n");
			continue;
		}

		// Extrage antetul pentru Ethernet si IP din pachet
		struct ether_header *eth_hdr = (struct ether_header *) buf;
		struct iphdr *ip_hdr = (struct iphdr *)(buf + sizeof(struct ether_header));

		// Verifica suma de control a pachetului si abandoneaza pachetul daca este incorecta
		const uint16_t sum = ntohs(ip_hdr->check);
		ip_hdr->check = 0;
		if (sum != checksum((uint16_t *)ip_hdr, sizeof(struct iphdr))){
			printf("Error: incorrect checksum in packet.\n");
			continue;
		} 

		// Gaseste cea mai buna ruta pe baza adresei de destinatie
		const struct route_table_entry *rentry = longest_prefix_match(ntohl(ip_hdr->daddr), rtable);
		if (rentry == NULL) {
			// Daca nu se gaseste nicio ruta, abandoenaza pachetul
			printf("Error: no route found for packet.\n");
			continue;
		}

		// Verifica TTL-ul si abandoneaza pachetul daca a fost depasit
		if (ip_hdr->ttl < 1) {
			printf("Error: TTL exceeded in packet.\n");
			continue;
		} 
		ip_hdr->ttl--;

 		// Actualizeaza checksum-ul si adresele MAC ale pachetului		
		ip_hdr->check = htons(checksum((uint16_t *)ip_hdr, sizeof(struct iphdr)));
		interface = rentry->interface;
		get_interface_mac(interface, eth_hdr->ether_shost);

		const struct arp_table_entry *mentry = get_arp_entry(rentry->next_hop);
		if (mentry == NULL){
			// In cazul in care nu exista o adresa MAC, abandoneaza pachetul
			printf("Error: no MAC address found for packet.\n");
			continue;
		}
		memcpy(eth_hdr->ether_dhost, mentry->mac, 6);

		// Trimitere pachet
		send_to_link(interface, buf, len);
	}
}
