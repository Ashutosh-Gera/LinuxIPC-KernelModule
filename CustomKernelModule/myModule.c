#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/fs.h> 
#include <linux/cdev.h>
#include <linux/proc_fs.h>
#include <linux/pid.h>
#include <linux/moduleparam.h>

#include <linux/pid_namespace.h>


//First struct pid *find_get_pid(pid_t nr) can be used to get pid structure then
//struct task_struct *pid_task(struct pid *pid, enum pid_type type) ~ function defined in kernel/pid.c to find task struct of a process
// pid : Pointer to the struct pid of the process. 
// pid_type:  PIDTYPE_PID,
//        PIDTYPE_PGID,
//           PIDTYPE_SID,
//           PIDTYPE_MAX
//-----------------------------------------------------------------
//proc - process information pseudo-filesystem

// The proc filesystem is a pseudo-filesystem which provides an
//        interface to kernel data structures.  It is commonly mounted at
//        /proc.  Typically, it is mounted automatically by the system, but
//        it can also be mounted manually using a command such as:

//            mount -t proc proc /proc

//        Most of the files in the proc filesystem are read-only, but some
//        files are writable, allowing kernel variables to be changed.

int pId; //process Id
struct pid* pId_struct;
struct task_struct *task; //retrieve task struct pointer in this var
int arg = 9;
module_param(arg, int, 0644);
// MODULE_PARM_DESC(arg, "command line argument to our module");
//convert pr_info to printk if not working
//insmod myModule.ko arg=10
//dmesg
//rmmod myModule
int proc_init(void) {

    pId_struct = find_get_pid(arg);
    task = pid_task(pId_struct, PIDTYPE_PID);

    pr_info("pid: %d\n", (int)task->pid);
    pr_info("user id: %d\n", (int)task->cred->uid.val);
    pr_info("pgid: %d\n", task->cred->gid.val);
    pr_info("command path: %s\n", (char*)task -> comm);

    return 0;
}

void proc_exit(void){
    pr_info("Exiting module\n");
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ashutosh Gera");
MODULE_DESCRIPTION("Required linux system module");