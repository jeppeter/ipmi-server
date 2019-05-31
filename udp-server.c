
/* Sample UDP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "udp-server.h"
#include "rmcp.h"
#include "asf.h"
#include "ipmi-session.h"
#include "ipmi-sensor.h"
#include "log.h"
#include "config.h"
#include <stdlib.h>
#include <time.h>

#ifdef TARGET_RPI
	#warning BUILD TARGET: RPI
#elif TARGET_ODROID
	#warning BUILD TARGET: ODROID
#else
	#warning BUILD TARGET: NORMAL
#endif
#include  <signal.h>
void exit_cleanup() {
	LOG_DEBUG("Cleanup..");
	sensors_cleanup();
	LOG_DEBUG(". done, exiting");
	fflush(stdout);	
	fflush(stderr);
	exit(0);
}

int main(int argc, char**argv)
{
	int port = RMCP_UDP_PORT;
	// padd current password with zeros
	password_padded = calloc(16, sizeof(uint8_t));
	memcpy(password_padded, password, MIN(strlen(password), 16));

	if (argc > 1) {
		port = atoi(argv[1]);
	}
	if (argc > 2) {
		set_log_level(LOG_DEBUG_LEVEL);
	}
	if (argc > 3) {
		set_log_level(LOG_TRACE_LEVEL);
	}


	// initialize sensors
	sensors_init();

	// init random seed
	srand(time(NULL));

	// cleanup at exit
	//atexit(sensors_cleanup);
	signal(SIGINT, exit_cleanup);

	int sockfd,bytes_recved;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	unsigned char mesg[1000];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(port);
	LOG_DEBUG("Starting IPMI Server on Port %d",port);
	if (bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1) {
		LOG_ERROR("Could not open UDP socket on Port %d, exiting.",port);
		exit_cleanup();
	}

	for (;;) {
		len = sizeof(cliaddr);
		bytes_recved = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);

		LOG_BUFFER_DEBUG(mesg,bytes_recved,"REC:");
		mesg[bytes_recved] = 0;


		// create internal packet
		protocol_data* packet_in = malloc(sizeof(protocol_data));
		packet_in->data = mesg;
		packet_in->length = bytes_recved;

		// handle answer packet
		protocol_data* packet_out = rmcp_process_packet(packet_in);
		if (packet_out->length > 0) {
			sendto(sockfd,packet_out->data,packet_out->length,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
		} else {
			LOG_ERROR("Error in udp-server.c: No Packetdata.");
		}

		// cleanup
		if (packet_out->length > 0) {
			free(packet_out->data);
		}
		free(packet_in);
		free(packet_out);
	}
}


