#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <linux/export.h>
#include <linux/cred.h>
#include <linux/sched/user.h>

void depth_first_search(struct task_struct *task)
{
	struct list_head *list;
	
	printk("\n");
	printk("pid: [%d]\n", task->pid);
	printk("parrent pid: [%d]\n", task->parent->pid);
	printk("nice value: %d\n", task->static_prio - 120);
	printk("priority: %d\n", task->rt_priority);
	printk("execution time: %llu\n", task->se.vruntime);
	printk("memory consumption: %lu\n", task->mm != NULL ? task->mm->total_vm * PAGE_SIZE : 0);
	printk("owner user id: %d", task->cred->user->uid.val);
	
	list_for_each(list, &task->children) {
		depth_first_search(list_entry(list, struct task_struct, sibling));
	}
}

EXPORT_SYMBOL(depth_first_search);

SYSCALL_DEFINE1(nos, pid_t, pid)
{
	struct task_struct *root_task = pid_task(find_vpid(pid), PIDTYPE_PID);
	if (root_task == NULL)
	{
		printk(KERN_ERR "Process with pid [%d] doesn't exist.\n", pid);
		return 1;
	}
	
	printk("Root process pid: [%d]", pid);
	depth_first_search(root_task);
	return 0;
}

