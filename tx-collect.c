/*
 * Copyright (c) 2007, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         Example of how the collect primitive works.
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"
#include "lib/random.h"
#include "net/rime/rime.h"
#include "net/rime/collect.h"
#include "dev/leds.h"
#include "dev/button-sensor.h"

#include "net/netstack.h"

#include <stdio.h>

static struct collect_conn tc;

/*---------------------------------------------------------------------------*/
PROCESS(example_collect_process, "Test collect process");
AUTOSTART_PROCESSES(&example_collect_process);
/*---------------------------------------------------------------------------*/
static void
recv(const linkaddr_t *originator, uint8_t seqno, uint8_t hops)
{
  printf("Data received from %d.%d, seqno %d, hops %d: len %d '%s'\n",
	 originator->u8[0], originator->u8[1],
	 seqno, hops,
	 packetbuf_datalen(),
	 (char *)packetbuf_dataptr());
}
/*---------------------------------------------------------------------------*/
static const struct collect_callbacks callbacks = { recv };
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(example_collect_process, ev, data)
{
  static struct etimer start;
  static struct etimer et;
  
  PROCESS_BEGIN();

  collect_open(&tc, 130, COLLECT_ROUTER, &callbacks);

  if(linkaddr_node_addr.u8[0] == 1 &&
     linkaddr_node_addr.u8[1] == 0) {
	printf("I am sink\n");
	collect_set_sink(&tc, 1);
  }

  static uint32_t  cpu, lpm, transmit, listen  ;
 
   energest_flush();

   cpu = energest_type_time(ENERGEST_TYPE_CPU);
   lpm = energest_type_time(ENERGEST_TYPE_LPM);
   transmit = energest_type_time(ENERGEST_TYPE_TRANSMIT);
   listen = energest_type_time(ENERGEST_TYPE_LISTEN);

   printf("Starting time: %lu; cpu: %lu, lpm: %lu, transmit: %lu, listen: %lu\n", clock_seconds(), cpu, lpm, transmit, listen);
   printf("RTIMER %u\n",  RTIMER_SECOND);

  /* Allow some time for the network to settle. */
 etimer_set(&start, CLOCK_SECOND * 60);
   printf("Etimer set for 60 seconds \n");

  while(1) {

    /* Send a packet every 30 seconds. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&start));
  	printf("Etimer EXPIRED \n");
	   	
	etimer_reset(&start);
	
	static uint32_t current_cpu, current_lpm, current_transmit, current_listen ;


    	energest_flush();


    	current_cpu = energest_type_time(ENERGEST_TYPE_CPU) - cpu;
    	current_lpm = energest_type_time(ENERGEST_TYPE_LPM) - lpm;
    	current_transmit = energest_type_time(ENERGEST_TYPE_TRANSMIT) - transmit;
    	current_listen = energest_type_time(ENERGEST_TYPE_LISTEN) - listen;
   
    	printf("energest at time: %lu; cpu: %lu, lpm: %lu, transmit: %lu, listen: %lu\n", clock_seconds(), current_cpu, current_lpm,     	 current_transmit, current_listen);	
 	
	etimer_set(&et, random_rand() % (CLOCK_SECOND * 30));
        printf("et SET \n");


       	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        printf("et EXPIRED \n");  


    
      static linkaddr_t oldparent;
      const linkaddr_t *parent;

      printf("Data Sending\n");
      packetbuf_clear();
	static int seq_id;
  	char buf[15];

 	seq_id++;
  
  	sprintf(buf,"Hello %d", seq_id);
      packetbuf_set_datalen(sprintf(packetbuf_dataptr(),"Hello %d", seq_id) + 1);
      collect_send(&tc, 15);

      parent = collect_parent(&tc);
      if(!linkaddr_cmp(parent, &oldparent)) {
        if(!linkaddr_cmp(&oldparent, &linkaddr_null)) {
          printf("#L %d 0\n", oldparent.u8[0]);
        }
        if(!linkaddr_cmp(parent, &linkaddr_null)) {
          printf("#L %d 1\n", parent->u8[0]);
        }
        linkaddr_copy(&oldparent, parent);
      }
    

  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
