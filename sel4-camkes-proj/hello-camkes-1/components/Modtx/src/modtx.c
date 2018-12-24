/*  modtx.c */

#include <camkes.h>
#include <stdio.h>

const char* SOURCE = "modtx";

int run(void){
	printf("Hello from modtx\n");
	const char* text = "hello world";
	//check the modbus
	modchk_iface_verify(text, SOURCE, 1);
	//sign the message
	crypto_iface_sign(text, 1);
	return 0;
}

void modtx_iface_print(const char* text, const char* source, int id, int isValid){

	printf("modtx from %s: %s\n", source, text);
}
