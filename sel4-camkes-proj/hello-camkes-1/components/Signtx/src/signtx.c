/*  modtx.c */

#include <camkes.h>
#include <stdio.h>

const char* SOURCE = "signtx";
const char* static_HMAC = "JAWOD3dif9103d!)ID!091209id12diawpd";
const char* static_text = "hello world from the untrusted network!";

const char* extract_text(const char* message);
const char* extract_hmac(const char* message);

int run(void){
	printf("hello from signtx\n");
	const char* message = "this is the message";
	const char* text = extract_text(message);
	const char* hmac = extract_hmac(message);
	//check the modbus
	modchk_iface_verify(text, SOURCE, 2);
	//verify the signature
	crypto_iface_verify(text, 2, hmac);
	return 0;
}

const char* extract_text(const char* message){
	return static_text;
}

const char* extract_hmac(const char* message){
	return static_HMAC;
}

void signtx_iface_print_sign(const char* text, const char* source, int id, int isValid, const char* hmac){

	printf("signtx from %s: %s\n", source, text);
}
void signtx_iface_print_mod(const char* text, const char* source, int id, int isValid){
	printf("signtx from %s: %s\n", source, text);
}
