#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x32feeafc, "mod_timer" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xb5c51982, "__cpu_online_mask" },
	{ 0x467e9822, "on_each_cpu_cond_mask" },
	{ 0x024101ca, "pv_ops" },
	{ 0xd272d446, "BUG_func" },
	{ 0x2352b148, "timer_shutdown_sync" },
	{ 0x5a2322a3, "param_ops_int" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0x02f9bbf0, "timer_init_key" },
	{ 0x058c185a, "jiffies" },
	{ 0xe9196a28, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x32feeafc,
	0xd272d446,
	0xb5c51982,
	0x467e9822,
	0x024101ca,
	0xd272d446,
	0x2352b148,
	0x5a2322a3,
	0xd272d446,
	0xe8213e80,
	0x02f9bbf0,
	0x058c185a,
	0xe9196a28,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"mod_timer\0"
	"__x86_return_thunk\0"
	"__cpu_online_mask\0"
	"on_each_cpu_cond_mask\0"
	"pv_ops\0"
	"BUG_func\0"
	"timer_shutdown_sync\0"
	"param_ops_int\0"
	"__fentry__\0"
	"_printk\0"
	"timer_init_key\0"
	"jiffies\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "FF2423A61F779E909DE6953");
