/********************************************************************************
* File Name:	write_lock.c
* Description:	第8章实例训练          
* Reference book:《Linux内核API完全参考手册》邱铁，周玉，邓莹莹 ，机械工业出版社.2010.9  
* E_mail:openlinux2100@gmail.com			                
*
********************************************************************************/

#include <linux/spinlock.h> 
#include <linux/init.h> 
#include <linux/module.h> 

MODULE_LICENSE("<0>GPL"); 
static int __init write_lock_init(void); 
static void __exit write_lock_exit(void);

rwlock_t rwlock;

int __init write_lock_init(void) 
{	 
    printk("[%s %d] write_lock_init \n", __func__, __LINE__); 
	rwlock_init( &rwlock );      //读写自旋锁初始化

	write_lock( &rwlock );      //写者申请得到读写锁rwlock

	write_unlock( &rwlock );    //写者释放读写锁rwlock

	return 0;
}

void __exit write_lock_exit(void) 
{ 
    printk("[%s %d] write_lock_exit \n", __func__, __LINE__); 
}

module_init(write_lock_init); 
module_exit(write_lock_exit);
