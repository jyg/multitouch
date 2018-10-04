/*
 *********************************************************************
 * TouchscreenSend : sending hid events by osc
 * 2018 Jean-Yves Gratius
 *********************************************************************
 * CREDITS :
 *
 * $Id: evtest.c,v 1.23 2005/02/06 13:51:42 vojtech Exp $
 *
 *  Copyright (c) 1999-2000 Vojtech Pavlik
 *
 *  Event device test program
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * Should you need to contact me, the author, you can do so either by
 * e-mail - mail your message to <vojtech@ucw.cz>, or by paper mail:
 * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic
 */

#include <stdint.h>

#include <linux/input.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#ifndef EV_SYN
#define EV_SYN 0
#endif


#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
#define OFF(x)  ((x)%BITS_PER_LONG)
#define BIT(x)  (1UL<<OFF(x))
#define LONG(x) ((x)/BITS_PER_LONG)
#define test_bit(bit, array)	((array[LONG(bit)] >> OFF(bit)) & 1)

char *absval[5] = { "Value", "Min  ", "Max  ", "Fuzz ", "Flat " };

/* 
 *******************************************************************************************************
 * Merged code from oscpack lib : SimpleSend.cpp 
 * (Simple example of sending an OSC message using oscpack.)
 *******************************************************************************************************
*/

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"


#define ADDRESS "127.0.0.1"
#define PORT 7000

#define OUTPUT_BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
    int fd, rd, i, j, k;
	struct input_event ev[64];
	int version;
	unsigned short id[4];
	unsigned long bit[EV_MAX][NBITS(KEY_MAX)];
	char name[256] = "Unknown";
	int abs[5];

	if (argc < 2) {
		printf("Usage: evtest /dev/input/eventX\n");
		printf("Where X = input device number\n");
		return 1;
	}

	if ((fd = open(argv[argc - 1], O_RDONLY)) < 0) {
		perror("evtest");
		return 1;
	}
	if (ioctl(fd, EVIOCGVERSION, &version)) {
		perror("evtest: can't get version");
		return 1;
	}
	printf("Input driver version is %d.%d.%d\n",
		version >> 16, (version >> 8) & 0xff, version & 0xff);

	ioctl(fd, EVIOCGID, id);
	printf("Input device ID: bus 0x%x vendor 0x%x product 0x%x version 0x%x\n",
		id[ID_BUS], id[ID_VENDOR], id[ID_PRODUCT], id[ID_VERSION]);

	ioctl(fd, EVIOCGNAME(sizeof(name)), name);
	printf("Input device name: \"%s\"\n", name);
	
	memset(bit, 0, sizeof(bit));
	ioctl(fd, EVIOCGBIT(0, EV_MAX), bit[0]);
	
	printf("Listening ... (interrupt to exit)\n");


    UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, PORT ) );
    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
   
	while (1) {
		rd = read(fd, ev, sizeof(struct input_event) * 64);

		if (rd < (int) sizeof(struct input_event)) {
			printf("yyy\n");
			perror("\nevtest: error reading");
			return 1;
		}

		
	
		for (i = 0; i < rd / sizeof(struct input_event); i++)
{			
			p.Clear();
			p << osc::BeginBundleImmediate;
			if (ev[i].type == EV_SYN) {
				printf("EV_SYN : Event: time %ld.%06ld, -------------- %s ------------\n",
					ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].code ? "Config Sync" : "Report Sync" );
    				p << osc::BeginMessage( "/sync" )  << (int)ev[i].time.tv_sec  << osc::EndMessage;
			} else if (ev[i].type == EV_MSC) {
				printf("EV_MSC : Event: time %ld.%06ld, type %d , code %d, value %02x\n",
					ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].type,	ev[i].code,	ev[i].value);
				p << osc::BeginMessage( "/msc" )  << (int)ev[i].code << (int)ev[i].value  << 						osc::EndMessage;
			} else if (ev[i].type == EV_KEY) {
				printf("EV_KEY : Event: time %ld.%06ld, type %d , code %d, value %02x\n",
					ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].type,	ev[i].code,	ev[i].value);
				p << osc::BeginMessage( "/key" )   << (int)ev[i].code << (int)ev[i].value  << 						osc::EndMessage;
			} else if (ev[i].type == EV_ABS) {
				printf("EV_ABS : Event: time %ld.%06ld, type %d , code %d, value %02x\n",
					ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].type,	ev[i].code,	ev[i].value);
				p << osc::BeginMessage( "/abs" )  <<  (int)ev[i].code << (int)ev[i].value  << 						osc::EndMessage;
			} else {
				printf("Event autre type: time %ld.%06ld, type %d, code %d , value %d\n",
					ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].type,
					ev[i].code,
					ev[i].value);
				p << osc::BeginMessage( "/other" )  << (int)ev[i].type << (int)ev[i].code << 						(int)ev[i].value  << osc::EndMessage;
				}	
		p<< osc::EndBundle;
 		transmitSocket.Send( p.Data(), p.Size() );
		
  }

	}  
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/test1" ) 
            << true << 23 << (float)3.1415 << "hello" << osc::EndMessage
        << osc::BeginMessage( "/test2" ) 
            << true << 24 << (float)10.8 << "world" << osc::EndMessage
        << osc::EndBundle;
    
    transmitSocket.Send( p.Data(), p.Size() );
}

