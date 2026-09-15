#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/smp.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Custom Kernel Engineer");
MODULE_DESCRIPTION("Hardware-Locked CPU MSR Frequency Override Module");
MODULE_VERSION("1.3");

#define IA32_PERF_CTL        0x199
#define IA32_MISC_ENABLE     0x1A0

static int target_ratio = 20;
module_param(target_ratio, int, 0644);
MODULE_PARM_DESC(target_ratio, "Target CPU ratio multiplier (e.g. 20 for 2.0GHz)");

static struct timer_list freq_timer;

static void set_cpu_frequency(void *info) {
    u64 msr_val;
    u64 misc_val;

    // 1. Изключване на Turbo Boost през IA32_MISC_ENABLE (Бит 38)
    rdmsrl(IA32_MISC_ENABLE, misc_val);
    misc_val |= (1ULL << 38); // 1 = Disable Turbo
    wrmsrl(IA32_MISC_ENABLE, misc_val);

    // 2. Налагане на искания target_ratio в IA32_PERF_CTL (0x199)
    rdmsrl(IA32_PERF_CTL, msr_val);
    msr_val &= ~(0xFF00ULL);
    msr_val |= ((u64)(target_ratio & 0xFF) << 8);
    wrmsrl(IA32_PERF_CTL, msr_val);
}

static void timer_callback(struct timer_list *t) {
    on_each_cpu(set_cpu_frequency, NULL, 0);
    mod_timer(&freq_timer, jiffies + msecs_to_jiffies(10)); // Намалено на 10ms интервал
}

static int __init custom_pstate_init(void) {
    pr_info("=== Custom CPU Control: Strict Hardware Lock to Ratio %d ===\n", target_ratio);

    timer_setup(&freq_timer, timer_callback, 0);
    mod_timer(&freq_timer, jiffies + msecs_to_jiffies(10));

    return 0;
}

static void __exit custom_pstate_exit(void) {
    u64 misc_val;
    
    // Възстановяване на Turbo Boost при премахване на модула
    rdmsrl(IA32_MISC_ENABLE, misc_val);
    misc_val &= ~(1ULL << 38);
    wrmsrl(IA32_MISC_ENABLE, misc_val);

    timer_shutdown_sync(&freq_timer);
    pr_info("=== Custom CPU Control: Strict Lock Released ===\n");
}

module_init(custom_pstate_init);
module_exit(custom_pstate_exit);
