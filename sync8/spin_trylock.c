/********************************************************************************
* File Name:	spin_trylock.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/spinlock.h> 
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/wait.h> 
#include <linux/delay.h>
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init spin_trylock_init(void); 
static void __exit spin_trylock_exit(void);

//子进程函数定义
spinlock_t lock;// = SPIN_LOCK_UNLOCKED;
int ret;

struct task_struct *thread_st;

int my_function(void * argc)
{
	printk("<1>in child, the current pid is:%d\n",current->pid);      //显示子进程PID
	ret = spin_trylock( &lock );	
	if( ret == 1 )
	{
		spin_unlock( &lock );
        printk("[%s %d] ret == 1\n", __func__, __LINE__); 
	}
	else
	{
		printk("<1>spin_trylock could't get the lock!\n");
		printk("<1>need the parent to unlock.\n\n");
	}
	return 0;
}

int __init spin_trylock_init(void) 
{
    #define CLONE_KERNEL (CLONE_FS|CLONE_FILES|CLONE_SIGHAND)

	printk("<0>in parent, the current pid is:%d\n",current->pid);   //显示父进程PID

	spin_lock_init( &lock );  //初始化自旋锁
	spin_lock( &lock );       //获取自旋锁

	thread_st = kthread_run(my_function,NULL, "mythread");	
    if (thread_st)
        printk("[%s %d] Thread create successfully\n", __func__, __LINE__); 
    else
        printk("[%s %d] Thread create failed\n", __func__, __LINE__); 
	
    mdelay(100);
	spin_unlock( &lock );    //释放自旋锁
	printk("<0>parent unlock!\n");

	return 0;
}

void __exit spin_trylock_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(spin_trylock_init); 
module_exit(spin_trylock_exit);
