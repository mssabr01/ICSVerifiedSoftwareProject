/* @TAG(DATA61_BSD) */
/*
 * CAmkES tutorial part 1: components with RPC. Client part.
 */

#include <stdio.h>

/* generated header for our component */
#include <camkes.h>

/* run the control thread */
int run(void) {
    printf("Starting the client\n");
    printf("-------------------\n");
    /* TODO: invoke the RPC function */
    /* hint 1: the name of the function to invoke is a composition of an interface name and a function name:
     * i.e.: <interface>_<function>
     * hint 2: the interfaces available are defined by the component, e.g. in components/Client/Client.camkes
     * hint 3: the function name is defined by the interface definition, e.g. in interfaces/HelloSimple.camkes
     * hint 4: so the function would be:  hello_say_hello()
     * hint 5: look at https://github.com/seL4/camkes-tool/blob/master/docs/index.md#creating-an-application
     */
    char *shello = "hello world";
    hello_say_hello(shello);

    printf("After the client\n");
    return 0;
}