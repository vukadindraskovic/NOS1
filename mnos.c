#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

extern void depth_first_search(struct task_struc *task);

static int pid = 1;
module param(pid, int, 0);

static int __init mnos_init(void)
{
	printk("Loading mnos module...");
	struct task_struct *root_task = pid_task(find_vpid(pid), PIDTYPE_PID);
	if (root_task == NULL)
	{
		printk(KERN_ERR "MNOS -> Process with pid [%d] doesn't exist.\n", pid);
		return 1;
	}
	
	printk("MNOS -> Root process pid: [%d]", pid);
	depth_first_search(root_task);
	return 0;
}

static void __exit mnos_exit(void)
{
	printk("Unloading mnos module...");
}

module_init(mnos_init);
module_exit(mnos_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vukadin Draskovic");

