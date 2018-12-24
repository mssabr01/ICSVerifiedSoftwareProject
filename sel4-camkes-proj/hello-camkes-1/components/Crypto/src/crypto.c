/* crypto.c */

#include <camkes.h>

const char* SOURCE = "crypto";
const char* HMAC = "JOAWPIDKJWOPADKASDOVSDKRGVBRDGPOK";
void crypto_iface_sign(const char* text, const int id){
	signtx_iface_print_sign(text, SOURCE, id, 1, HMAC); 
}

void crypto_iface_verify(const char* text, const int id, const char* hmac){
	modtx_iface_print(text, SOURCE, id, 1);
}
