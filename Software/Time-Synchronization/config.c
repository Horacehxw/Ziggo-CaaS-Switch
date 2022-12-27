#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#include "tsn_drivers/rtc.h"
#include "tsn_drivers/tsu.h"
#include "tsn_drivers/uio.h"
#include "tsn_drivers/gcl.h"

#include "config.h"

// definition for cpp part
extern void setup_topo();
extern void setup_gcl();

void set_gcl_ring3() {
	int get_gcl_status;

	// init all output queues
	for (int i = 0; i < 16; i++) {
		set_gcl(4, i, 2);
		set_gcl(3, i, 2);
		set_gcl(2, i, 2);
		set_gcl(1, i, 2);
	}
	// WARNING: set gcl port number is 1,2,3,4, there's no port 0!

	setup_gcl();
}

void set_switch_rule_ring3() {
	// output_port: 0 -> to Port 0
    //                 1 -> to Port 1
    //                 2 -> to Port 2
    //                 3 -> to Port 3
    //                 4 -> to PLC DMA
	void *ptr;
	ptr = switch_rule_uio_init();
	switch_rule_init(ptr); // clear all existing rules.

	// setup switch rules
	setup_topo();
}