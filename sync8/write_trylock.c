/********************************************************************************
* File Name:	write_trylock.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/spinlock.h> 
#include <linux/sched.h>
#include <linux/wait.h> 
#include <linux/module.h> 
MODULE_LICENSE("GPL"); 
static int __init write_trylock_init(void); 
static void __exit write_trylock_exit(void);

rwlock_t rwlock;

int __init write_trylock_init(void) 
{
	int ret;
	rwlock_init( &rwlock );     //读写自旋锁初始化
	read_lock( &rwlock );       //读者申请得到读写锁rwlock
	/* 输出读写自旋锁lock字段信息*/
    printk("[%s %d]\n", __func__, __LINE__); 
	ret = write_trylock( &rwlock );  //写者试图获得自旋锁
	if( ret == 1 )
	{
        printk("[%s %d] now unlock\n", __func__, __LINE__); 
		write_unlock( &rwlock );
	}
	else
	{
		printk("<0>write_trylock could't get the lock!\n");
	}
	
	read_unlock( &rwlock );    //读者释放读写锁rwlock
    printk("[%s %d] read_unlock\n", __func__, __LINE__); 

	return 0;
}

void __exit write_trylock_exit(void) 
{ 
	printk("<0>exit!\n");
}

module_init(write_trylock_init); 
module_exit(write_trylock_exit);
