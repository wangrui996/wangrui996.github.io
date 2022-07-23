

#include <linux/module.h>



static int __init chrdevbase_init(void)
{
	
    return 0;
}

static void __exit chrdevbase_fini(void)
{

}



/*
 module入口和出口注册
 */
module_init(chrdevbase_init);  /*模块入口*/
module_exit(chrdevbase_fini);  /*模块出口*/