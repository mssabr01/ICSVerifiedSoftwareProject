/* modchk.c */

#include <camkes.h>
#include <string.h>

const char* MODTX = "modtx";
const char* SIGNTX = "signtx";
const char* SOURCE = "modchk";

void modchk_iface_verify(const char* text, const char* source, const int id){
	//if the message came from the signtx component, forward it to the modtx component
	if(strcmp(SIGNTX, source) == 0){
		modtx_iface_print(text, SOURCE, id, 1);
	}
	else{
		signtx_iface_print_sign(text, SOURCE, id, 1, "oiwajdwad");
	}
}
