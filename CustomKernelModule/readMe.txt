To compile:
    sudo make
and check the functionality!

Modules are pieces of code that can be loaded and unloaded into the kernel upon demand. 
They extend the functionality of the kernel without the need to reboot the system. 
For example, one type of module is the device driver, which allows the kernel to access hardware connected to the system. 
Without modules, we would have to build monolithic kernels and add new functionality directly into the kernel image. 
Besides having larger kernels, this has the disadvantage of requiring us to rebuild and reboot the kernel every time we want new functionality.

Kernel modules must have at least two functions: a "start" (initialization) function called init_module() which is called when the module is insmod ed into the kernel,
and an "end" (cleanup) function called cleanup_module() which is called just before it is removed from the kernel. Actually, things have changed starting with kernel 
2.3.13. You can now use whatever name you like for the start and end functions of a module, and you will learn how to do this in Section 4.2. 
In fact, the new method is the preferred method. However, many people still use init_module() and cleanup_module() for their start and end functions.

Lastly, every kernel module needs to include <linux/module.h>. 

Resources used:
https://sysprog21.github.io/lkmpg/#system-calls
https://strace.io/
https://tuxthink.blogspot.com/2012/07/module-to-find-task-from-its-pid.html
https://stackoverflow.com/questions/8547332/efficient-way-to-find-task-struct-by-pid





