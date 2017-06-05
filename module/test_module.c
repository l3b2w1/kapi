#include <linux/module.h>
#include <linux/kernel.h>

int symbol_A(void)
{
    return 1;
}
EXPORT_SYMBOL(symbol_A);

int symbol_B(void)
{
    return 1;
}
EXPORT_SYMBOL(symbol_B);

static int symbol_1 = 1;
int symbol_2 = 2;
int symbol_3 = 3;

EXPORT_SYMBOL(symbol_3);

int __init test_module_init(void)
{
    printk("test_module hello world\n");
    return 0;
}

void __exit test_module_exit(void)
{
    printk("test_module exit\n");
}

module_init(test_module_init);
module_exit(test_module_exit);
