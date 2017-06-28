/********************************************************************************
* File Name:	down_interruptible.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/semaphore.h> 
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("GPL"); 
static int __init down_interruptible_init(void); 
static void __exit down_interruptible_exit(void);

struct semaphore sema;

int __init down_interruptible_init(void) 
{
	int ret = 0;
	sema_init( &sema, 5 );   //信号量初始化
	/* 输出初始化后信号量的信息 */
	printk("<0>after sema_init, sema.count: %d\n",sema.count);
	
	printk("<0>\n");
	ret = down_interruptible(&sema);        //获取信号量
    if (ret) {
        printk("[%s %d] are we here 0\n", __func__, __LINE__); 
        return -ERESTARTSYS;
    }
	/* 输出down_interruptible操作后信号量的信息 */
	printk("<0>first down_interruptible, ret = %d\n", ret);
	printk("<0>first down_interruptible, sema.count: %d\n",sema.count);
    up(&sema);
	printk("<0>first up, sema.count: %d\n",sema.count);

#if 0
	sema_init( &sema, 0 );
#endif
	printk("<0>\n");
	ret = down_interruptible( &sema);            
    if (ret) {
        printk("[%s %d] are we here 1\n", __func__, __LINE__); 
        return -ERESTARTSYS;
    }
	
	printk("<0>second down_interruptible, ret = %d\n", ret);
	printk("<0>second down_interruptible, sema.count: %d\n",sema.count);
    up(&sema);
	printk("<0>second up, sema.count: %d\n",sema.count);
    printk("[%s %d] out down_interruptible_init \n", __func__, __LINE__); 

	return 0;
}

void __exit down_interruptible_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(down_interruptible_init); 
module_exit(down_interruptible_exit);
