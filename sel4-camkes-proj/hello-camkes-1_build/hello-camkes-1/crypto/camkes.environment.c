

#include <camkes.h>
#include <camkes/init.h>

int component_control_main() {
    
    int _camkes__12;

    
        if (pre_init) {
            pre_init();
        }
    

    /* we call pre_init_interface_sync in all circumstances, even if we do not support
     * init, as the implementation already has an internal guard for init support and
     * so the function will just do nothing without init support. Always calling it
     * provides a bit more flexibility in the future, and is consistent with the
     * post_init version which *does* do something even if we do not support init
     */
    _camkes__12 = pre_init_interface_sync();
    if (_camkes__12) {
        return _camkes__12;
    }

    
        if (post_init) {
            post_init();
        }
    

    _camkes__12 = post_init_interface_sync();
    if (_camkes__12) {
        return _camkes__12;
    }

    
        return 0;
    
}
