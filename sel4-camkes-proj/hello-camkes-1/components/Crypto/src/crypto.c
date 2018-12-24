/* crypto.c */

#include <camkes.h>
#include <string.h>

const char* SOURCE = "crypto";
char* KEY = "Jad23@(TGJGJEJ(FS39pf&%";
void crypto_iface_sign(const char* text, const int id){
	char hmac[64];
	char text_[sizeof(text)];
	strncpy(text_, text, sizeof(text));
	HMAC2(KEY,sizeof(KEY), text_, sizeof(text_), hmac);
	printf("hmac: %s\n", hmac);
	signtx_iface_print_sign(text, SOURCE, id, 1, hmac); 
}

void crypto_iface_verify(const char* text, const int id, const char* hmac){
	modtx_iface_print(text, SOURCE, id, 1);
}
