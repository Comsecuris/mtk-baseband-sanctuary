
#include <linux/kernel.h>           
#include <linux/module.h>           //MODULE_DESCRIPTION, MODULE_LICENSE
#include <linux/init.h>             
#include <linux/proc_fs.h>          
#include <linux/seq_file.h>         
#include <asm/uaccess.h>            

#include <mach/hotplug.h>
#include <mach/mt_spm_cpu.h>
#include <mach/mt_spm_mtcmos.h>

#include <mach/mt_hotplug_strategy_internal.h>


#define PROC_FOPS_RO(name)                                                          \
    static int hps_ ## name ## _proc_open(struct inode *inode, struct file *file)   \
    {                                                                               \
        return single_open(file, hps_ ## name ## _proc_show, PDE_DATA(inode));      \
    }                                                                               \
    static const struct file_operations hps_ ## name ## _proc_fops = {              \
        .owner          = THIS_MODULE,                                              \
        .open           = hps_ ## name ## _proc_open,                               \
        .read           = seq_read,                                                 \
        .llseek         = seq_lseek,                                                \
        .release        = single_release,                                           \
    }

#define PROC_FOPS_RW(name)                                                          \
    static int hps_ ## name ## _proc_open(struct inode *inode, struct file *file)   \
    {                                                                               \
        return single_open(file, hps_ ## name ## _proc_show, PDE_DATA(inode));      \
    }                                                                               \
    static const struct file_operations hps_ ## name ## _proc_fops = {              \
        .owner          = THIS_MODULE,                                              \
        .open           = hps_ ## name ## _proc_open,                               \
        .read           = seq_read,                                                 \
        .llseek         = seq_lseek,                                                \
        .release        = single_release,                                           \
        .write          = hps_ ## name ## _proc_write,                              \
    }

#define PROC_ENTRY(name)    {__stringify(name), &hps_ ## name ## _proc_fops}

#define PROC_FOPS_RO_UNSIGNED_INT_FULL(name, var)                                   \
    static int hps_ ## name ## _proc_show(struct seq_file *m, void *v)              \
    {                                                                               \
        seq_printf(m, "%u\n", var);                                                 \
        return 0;                                                                   \
    }                                                                               \
    PROC_FOPS_RO(name)

#define PROC_FOPS_RW_UNSIGNED_INT_FULL(name, var)                                   \
    static int hps_ ## name ## _proc_show(struct seq_file *m, void *v)              \
    {                                                                               \
        seq_printf(m, "%u\n", var);                                                 \
        return 0;                                                                   \
    }                                                                               \
    static int hps_## name ## _proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)  \
    {                                                                               \
        int len = 0, name = 0;                                                      \
        char desc[32];                                                              \
                                                                                    \
        len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);            \
        if (copy_from_user(desc, buffer, len))                                      \
        {                                                                           \
            return 0;                                                               \
        }                                                                           \
        desc[len] = '\0';                                                           \
                                                                                    \
        if (sscanf(desc, "%u", &name) == 1)                                         \
        {                                                                           \
            var = name;                                                             \
            return count;                                                           \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            hps_warn("hps_ ## name ## _proc_write, bad argument\n");                \
        }                                                                           \
                                                                                    \
        return -EINVAL;                                                             \
    }                                                                               \
    PROC_FOPS_RW(name)

#define PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(name, var, func_before_w, func_after_w) \
    static int hps_ ## name ## _proc_show(struct seq_file *m, void *v)              \
    {                                                                               \
        seq_printf(m, "%u\n", var);                                                 \
        return 0;                                                                   \
    }                                                                               \
    static int hps_## name ## _proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)  \
    {                                                                               \
        int len = 0, name = 0;                                                      \
        char desc[32];                                                              \
                                                                                    \
        len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);            \
        if (copy_from_user(desc, buffer, len))                                      \
        {                                                                           \
            return 0;                                                               \
        }                                                                           \
        desc[len] = '\0';                                                           \
                                                                                    \
        if (sscanf(desc, "%u", &name) == 1)                                         \
        {                                                                           \
            func_before_w                                                           \
            var = name;                                                             \
            func_after_w                                                            \
            return count;                                                           \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            hps_warn("hps_ ## name ## _proc_write, bad argument\n");                \
        }                                                                           \
                                                                                    \
        return -EINVAL;                                                             \
    }                                                                               \
    PROC_FOPS_RW(name)




static void * g_memory_debug = NULL;

PROC_FOPS_RO_UNSIGNED_INT_FULL(init_state, hps_ctxt.init_state);
PROC_FOPS_RO_UNSIGNED_INT_FULL(state, hps_ctxt.state);

PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    enabled, 
    hps_ctxt.enabled, 
    mutex_lock(&hps_ctxt.lock);, 
    hps_ctxt_reset_stas_nolock(); mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    early_suspend_enabled, 
    hps_ctxt.early_suspend_enabled,
    mutex_lock(&hps_ctxt.lock);, 
    mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    suspend_enabled, 
    hps_ctxt.suspend_enabled,
    mutex_lock(&hps_ctxt.lock);, 
    mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    cur_dump_enabled, 
    hps_ctxt.cur_dump_enabled,
    mutex_lock(&hps_ctxt.lock);, 
    mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    stats_dump_enabled, 
    hps_ctxt.stats_dump_enabled,
    mutex_lock(&hps_ctxt.lock);, 
    mutex_unlock(&hps_ctxt.lock); );

PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    up_threshold, 
    hps_ctxt.up_threshold, 
    mutex_lock(&hps_ctxt.lock);, 
    hps_ctxt_reset_stas_nolock(); mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    up_times, 
    hps_ctxt.up_times, 
    mutex_lock(&hps_ctxt.lock);, 
    hps_ctxt_reset_stas_nolock(); mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    down_threshold, 
    hps_ctxt.down_threshold, 
    mutex_lock(&hps_ctxt.lock);, 
    hps_ctxt_reset_stas_nolock(); mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    down_times, 
    hps_ctxt.down_times, 
    mutex_lock(&hps_ctxt.lock);, 
    hps_ctxt_reset_stas_nolock(); mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    es_up_threshold, 
    hps_ctxt.es_up_threshold, 
    mutex_lock(&hps_ctxt.lock);, 
    hps_ctxt_reset_stas_nolock(); mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    es_up_times, 
    hps_ctxt.es_up_times, 
    mutex_lock(&hps_ctxt.lock);, 
    hps_ctxt_reset_stas_nolock(); mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    es_down_threshold, 
    hps_ctxt.es_down_threshold, 
    mutex_lock(&hps_ctxt.lock);, 
    hps_ctxt_reset_stas_nolock(); mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    es_down_times, 
    hps_ctxt.es_down_times, 
    mutex_lock(&hps_ctxt.lock);, 
    hps_ctxt_reset_stas_nolock(); mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    input_boost_enabled, 
    hps_ctxt.input_boost_enabled,
    mutex_lock(&hps_ctxt.lock);, 
    mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    input_boost_cpu_num, 
    hps_ctxt.input_boost_cpu_num,
    mutex_lock(&hps_ctxt.lock);, 
    mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    rush_boost_enabled, 
    hps_ctxt.rush_boost_enabled,
    mutex_lock(&hps_ctxt.lock);, 
    mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    rush_boost_threshold, 
    hps_ctxt.rush_boost_threshold, 
    mutex_lock(&hps_ctxt.lock);, 
    hps_ctxt_reset_stas_nolock(); mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    rush_boost_times, 
    hps_ctxt.rush_boost_times, 
    mutex_lock(&hps_ctxt.lock);, 
    hps_ctxt_reset_stas_nolock(); mutex_unlock(&hps_ctxt.lock); );
PROC_FOPS_RW_UNSIGNED_INT_FULL_FUNC(
    tlp_times, 
    hps_ctxt.tlp_times, 
    mutex_lock(&hps_ctxt.lock);, 
    hps_ctxt_reset_stas_nolock(); mutex_unlock(&hps_ctxt.lock); );

static int hps_num_base_perf_serv_proc_show(struct seq_file *m, void *v)
{
    if (hps_ctxt.is_hmp)
        seq_printf(m, "%u %u\n", hps_ctxt.little_num_base_perf_serv, hps_ctxt.big_num_base_perf_serv);
    else
        seq_printf(m, "%u\n", hps_ctxt.little_num_base_perf_serv);
    return 0;
}

static int hps_num_base_perf_serv_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    int len = 0, little_num_base_perf_serv = 0, big_num_base_perf_serv = 0;
    char desc[32];
    unsigned int num_online;

    len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
    if (copy_from_user(desc, buffer, len))
    {
        return 0;
    }
    desc[len] = '\0';

    if (hps_ctxt.is_hmp && (sscanf(desc, "%u %u", &little_num_base_perf_serv, &big_num_base_perf_serv) == 2))
    {
        if (little_num_base_perf_serv > num_possible_little_cpus()
            || little_num_base_perf_serv < 1)
        {
            hps_warn("hps_num_base_perf_serv_proc_write, bad argument(%u, %u)\n", little_num_base_perf_serv, big_num_base_perf_serv);
            return -EINVAL;
        }

        if (big_num_base_perf_serv > num_possible_big_cpus())
        {
            hps_warn("hps_num_base_perf_serv_proc_write, bad argument(%u, %u)\n", little_num_base_perf_serv, big_num_base_perf_serv);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_base_perf_serv = little_num_base_perf_serv;
        hps_ctxt.big_num_base_perf_serv = big_num_base_perf_serv;
        num_online = num_online_big_cpus();
        if ((num_online < big_num_base_perf_serv) &&
#ifdef CONFIG_HTC_PNPMGR
            (num_online < hps_ctxt.big_num_limit_pnpmgr) &&
#endif
            (num_online < min(hps_ctxt.big_num_limit_thermal, hps_ctxt.big_num_limit_low_battery)) &&
            (num_online < min(hps_ctxt.big_num_limit_ultra_power_saving, hps_ctxt.big_num_limit_power_serv)))
        {
            hps_task_wakeup_nolock();
        }
        else
        {
            num_online = num_online_little_cpus();
            if ((num_online < little_num_base_perf_serv) &&
#ifdef CONFIG_HTC_PNPMGR
                (num_online < hps_ctxt.little_num_limit_pnpmgr) &&
#endif
                (num_online < min(hps_ctxt.little_num_limit_thermal, hps_ctxt.little_num_limit_low_battery)) &&
                (num_online < min(hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.little_num_limit_power_serv)) &&
                (num_online_cpus() < (little_num_base_perf_serv + big_num_base_perf_serv)))
                hps_task_wakeup_nolock();
        }

        
        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else if (!hps_ctxt.is_hmp && (sscanf(desc, "%u", &little_num_base_perf_serv) == 1))
    {
        if (little_num_base_perf_serv > num_possible_little_cpus()
            || little_num_base_perf_serv < 1)
        {
            hps_warn("hps_num_base_perf_serv_proc_write, bad argument(%u)\n", little_num_base_perf_serv);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_base_perf_serv = little_num_base_perf_serv;
        num_online = num_online_little_cpus();
        if ((num_online < little_num_base_perf_serv) &&
#ifdef CONFIG_HTC_PNPMGR
            (num_online < hps_ctxt.little_num_limit_pnpmgr) &&
#endif
            (num_online < min(hps_ctxt.little_num_limit_thermal, hps_ctxt.little_num_limit_low_battery)) &&
            (num_online < min(hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.little_num_limit_power_serv)))
        {
            hps_task_wakeup_nolock();
        }

        
        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else
    {
        hps_warn("hps_num_base_perf_serv_proc_write, bad argument\n");
    }

    return -EINVAL;
}

PROC_FOPS_RW(num_base_perf_serv);

static int hps_num_limit_thermal_proc_show(struct seq_file *m, void *v)
{
    if (hps_ctxt.is_hmp)
        seq_printf(m, "%u %u\n", hps_ctxt.little_num_limit_thermal, hps_ctxt.big_num_limit_thermal);
    else
        seq_printf(m, "%u\n", hps_ctxt.little_num_limit_thermal);
    return 0;
}

static int hps_num_limit_thermal_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    int len = 0, little_num_limit_thermal = 0, big_num_limit_thermal = 0;
    char desc[32];

    len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
    if (copy_from_user(desc, buffer, len))
    {
        return 0;
    }
    desc[len] = '\0';

    if (hps_ctxt.is_hmp && (sscanf(desc, "%u %u", &little_num_limit_thermal, &big_num_limit_thermal) == 2))
    {
        if (little_num_limit_thermal > num_possible_little_cpus()
            || little_num_limit_thermal < 1)
        {
            hps_warn("hps_num_limit_thermal_proc_write, bad argument(%u, %u)\n", little_num_limit_thermal, big_num_limit_thermal);
            return -EINVAL;
        }

        if (big_num_limit_thermal > num_possible_big_cpus())
        {
            hps_warn("hps_num_limit_thermal_proc_write, bad argument(%u, %u)\n", little_num_limit_thermal, big_num_limit_thermal);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_limit_thermal = little_num_limit_thermal;
        hps_ctxt.big_num_limit_thermal = big_num_limit_thermal;
        if (num_online_big_cpus() > big_num_limit_thermal)
            hps_task_wakeup_nolock();
        else if (num_online_little_cpus() > little_num_limit_thermal)
            hps_task_wakeup_nolock();

        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else if (!hps_ctxt.is_hmp && (sscanf(desc, "%u", &little_num_limit_thermal) == 1))
    {
        if (little_num_limit_thermal > num_possible_little_cpus()
            || little_num_limit_thermal < 1)
        {
            hps_warn("hps_num_limit_thermal_proc_write, bad argument(%u)\n", little_num_limit_thermal);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_limit_thermal = little_num_limit_thermal;
        if (num_online_little_cpus() > little_num_limit_thermal)
            hps_task_wakeup_nolock();

        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else
    {
        hps_warn("hps_num_limit_thermal_proc_write, bad argument\n");
    }

    return -EINVAL;
}

PROC_FOPS_RW(num_limit_thermal);

static int hps_num_limit_low_battery_proc_show(struct seq_file *m, void *v)
{
    if (hps_ctxt.is_hmp)
        seq_printf(m, "%u %u\n", hps_ctxt.little_num_limit_low_battery, hps_ctxt.big_num_limit_low_battery);
    else
        seq_printf(m, "%u\n", hps_ctxt.little_num_limit_low_battery);
    return 0;
}

static int hps_num_limit_low_battery_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    int len = 0, little_num_limit_low_battery = 0, big_num_limit_low_battery = 0;
    char desc[32];

    len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
    if (copy_from_user(desc, buffer, len))
    {
        return 0;
    }
    desc[len] = '\0';

    if (hps_ctxt.is_hmp && (sscanf(desc, "%u %u", &little_num_limit_low_battery, &big_num_limit_low_battery) == 2))
    {
        if (little_num_limit_low_battery > num_possible_little_cpus()
            || little_num_limit_low_battery < 1)
        {
            hps_warn("hps_num_limit_low_battery_proc_write, bad argument(%u, %u)\n", little_num_limit_low_battery, big_num_limit_low_battery);
            return -EINVAL;
        }

        if (big_num_limit_low_battery > num_possible_big_cpus())
        {
            hps_warn("hps_num_limit_low_battery_proc_write, bad argument(%u, %u)\n", little_num_limit_low_battery, big_num_limit_low_battery);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_limit_low_battery = little_num_limit_low_battery;
        hps_ctxt.big_num_limit_low_battery = big_num_limit_low_battery;
        if (num_online_big_cpus() > big_num_limit_low_battery)
            hps_task_wakeup_nolock();
        else if (num_online_little_cpus() > little_num_limit_low_battery)
            hps_task_wakeup_nolock();

        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else if (!hps_ctxt.is_hmp && (sscanf(desc, "%u", &little_num_limit_low_battery) == 1))
    {
        if (little_num_limit_low_battery > num_possible_little_cpus()
            || little_num_limit_low_battery < 1)
        {
            hps_warn("hps_num_limit_low_battery_proc_write, bad argument(%u)\n", little_num_limit_low_battery);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_limit_low_battery = little_num_limit_low_battery;
        if (num_online_little_cpus() > little_num_limit_low_battery)
            hps_task_wakeup_nolock();

        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else
    {
        hps_warn("hps_num_limit_low_battery_proc_write, bad argument\n");
    }

    return -EINVAL;
}

PROC_FOPS_RW(num_limit_low_battery);

static int hps_num_limit_ultra_power_saving_proc_show(struct seq_file *m, void *v)
{
    if (hps_ctxt.is_hmp)
        seq_printf(m, "%u %u\n", hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.big_num_limit_ultra_power_saving);
    else
        seq_printf(m, "%u\n", hps_ctxt.little_num_limit_ultra_power_saving);
    return 0;
}

static int hps_num_limit_ultra_power_saving_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    int len = 0, little_num_limit_ultra_power_saving = 0, big_num_limit_ultra_power_saving = 0;
    char desc[32];

    len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
    if (copy_from_user(desc, buffer, len))
    {
        return 0;
    }
    desc[len] = '\0';

    if (hps_ctxt.is_hmp && (sscanf(desc, "%u %u", &little_num_limit_ultra_power_saving, &big_num_limit_ultra_power_saving) == 2))
    {
        if (little_num_limit_ultra_power_saving > num_possible_little_cpus()
            || little_num_limit_ultra_power_saving < 1)
        {
            hps_warn("hps_num_limit_ultra_power_saving_proc_write, bad argument(%u, %u)\n", little_num_limit_ultra_power_saving, big_num_limit_ultra_power_saving);
            return -EINVAL;
        }

        if (big_num_limit_ultra_power_saving > num_possible_big_cpus())
        {
            hps_warn("hps_num_limit_ultra_power_saving_proc_write, bad argument(%u, %u)\n", little_num_limit_ultra_power_saving, big_num_limit_ultra_power_saving);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_limit_ultra_power_saving = little_num_limit_ultra_power_saving;
        hps_ctxt.big_num_limit_ultra_power_saving = big_num_limit_ultra_power_saving;
        if (num_online_big_cpus() > big_num_limit_ultra_power_saving)
            hps_task_wakeup_nolock();
        else if (num_online_little_cpus() > little_num_limit_ultra_power_saving)
            hps_task_wakeup_nolock();

        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else if (!hps_ctxt.is_hmp && (sscanf(desc, "%u", &little_num_limit_ultra_power_saving) == 1))
    {
        if (little_num_limit_ultra_power_saving > num_possible_little_cpus()
            || little_num_limit_ultra_power_saving < 1)
        {
            hps_warn("hps_num_limit_ultra_power_saving_proc_write, bad argument(%u)\n", little_num_limit_ultra_power_saving);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_limit_ultra_power_saving = little_num_limit_ultra_power_saving;
        if (num_online_little_cpus() > little_num_limit_ultra_power_saving)
            hps_task_wakeup_nolock();

        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else
    {
        hps_warn("hps_num_limit_ultra_power_saving_proc_write, bad argument\n");
    }

    return -EINVAL;
}

PROC_FOPS_RW(num_limit_ultra_power_saving);

static int hps_num_limit_power_serv_proc_show(struct seq_file *m, void *v)
{
    if (hps_ctxt.is_hmp)
        seq_printf(m, "%u %u\n", hps_ctxt.little_num_limit_power_serv, hps_ctxt.big_num_limit_power_serv);
    else
        seq_printf(m, "%u\n", hps_ctxt.little_num_limit_power_serv);
    return 0;
}

static int hps_num_limit_power_serv_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    int len = 0, little_num_limit_power_serv = 0, big_num_limit_power_serv = 0;
    char desc[32];

    len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
    if (copy_from_user(desc, buffer, len))
    {
        return 0;
    }
    desc[len] = '\0';

    if (hps_ctxt.is_hmp && (sscanf(desc, "%u %u", &little_num_limit_power_serv, &big_num_limit_power_serv) == 2))
    {
        if (little_num_limit_power_serv > num_possible_little_cpus()
            || little_num_limit_power_serv < 1)
        {
            hps_warn("hps_num_limit_power_serv_proc_write, bad argument(%u, %u)\n", little_num_limit_power_serv, big_num_limit_power_serv);
            return -EINVAL;
        }

        if (big_num_limit_power_serv > num_possible_big_cpus())
        {
            hps_warn("hps_num_limit_power_serv_proc_write, bad argument(%u, %u)\n", little_num_limit_power_serv, big_num_limit_power_serv);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_limit_power_serv = little_num_limit_power_serv;
        hps_ctxt.big_num_limit_power_serv = big_num_limit_power_serv;
        if (num_online_big_cpus() > big_num_limit_power_serv)
            hps_task_wakeup_nolock();
        else if (num_online_little_cpus() > little_num_limit_power_serv)
            hps_task_wakeup_nolock();

        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else if (!hps_ctxt.is_hmp && (sscanf(desc, "%u", &little_num_limit_power_serv) == 1))
    {
        if (little_num_limit_power_serv > num_possible_little_cpus()
            || little_num_limit_power_serv < 1)
        {
            hps_warn("hps_num_limit_power_serv_proc_write, bad argument(%u)\n", little_num_limit_power_serv);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_limit_power_serv = little_num_limit_power_serv;
        if (num_online_little_cpus() > little_num_limit_power_serv)
            hps_task_wakeup_nolock();

        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else
    {
        hps_warn("hps_num_limit_power_serv_proc_write, bad argument\n");
    }

    return -EINVAL;
}

PROC_FOPS_RW(num_limit_power_serv);


#ifdef CONFIG_HTC_PNPMGR
static int hps_num_base_pnpmgr_proc_show(struct seq_file *m, void *v)
{
    if (hps_ctxt.is_hmp)
        seq_printf(m, "%u %u\n", hps_ctxt.little_num_base_pnpmgr, hps_ctxt.big_num_base_pnpmgr);
    else
        seq_printf(m, "%u\n", hps_ctxt.little_num_base_pnpmgr);
    return 0;
}

static int hps_num_base_pnpmgr_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    int len = 0, little_num_base_pnpmgr = 0, big_num_base_pnpmgr = 0;
    char desc[32];
    unsigned int num_online;

    len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
    if (copy_from_user(desc, buffer, len))
    {
        return 0;
    }
    desc[len] = '\0';

    if (hps_ctxt.is_hmp && (sscanf(desc, "%u %u", &little_num_base_pnpmgr, &big_num_base_pnpmgr) == 2))
    {
        if (little_num_base_pnpmgr > num_possible_little_cpus()
            || little_num_base_pnpmgr < 1)
        {
            hps_warn("hps_num_base_pnpmgr_proc_write, bad argument(%u, %u)\n", little_num_base_pnpmgr, big_num_base_pnpmgr);
            return -EINVAL;
        }

        if (big_num_base_pnpmgr > num_possible_big_cpus())
        {
            hps_warn("hps_num_base_pnpmgr_proc_write, bad argument(%u, %u)\n", little_num_base_pnpmgr, big_num_base_pnpmgr);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_base_pnpmgr = little_num_base_pnpmgr;
        hps_ctxt.big_num_base_pnpmgr = big_num_base_pnpmgr;
        num_online = num_online_big_cpus();
        if ((num_online < big_num_base_pnpmgr) &&
            (num_online < hps_ctxt.big_num_limit_pnpmgr) &&
            (num_online < min(hps_ctxt.big_num_limit_thermal, hps_ctxt.big_num_limit_low_battery)) &&
            (num_online < min(hps_ctxt.big_num_limit_ultra_power_saving, hps_ctxt.big_num_limit_power_serv)))
        {
            hps_task_wakeup_nolock();
        }
        else
        {
            num_online = num_online_little_cpus();
            if ((num_online < little_num_base_pnpmgr) &&
                (num_online < hps_ctxt.little_num_limit_pnpmgr) &&
                (num_online < min(hps_ctxt.little_num_limit_thermal, hps_ctxt.little_num_limit_low_battery)) &&
                (num_online < min(hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.little_num_limit_power_serv)) &&
                (num_online_cpus() < (little_num_base_pnpmgr + big_num_base_pnpmgr)))
                hps_task_wakeup_nolock();
        }

        
        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else if (!hps_ctxt.is_hmp && (sscanf(desc, "%u", &little_num_base_pnpmgr) == 1))
    {
        if (little_num_base_pnpmgr > num_possible_little_cpus()
            || little_num_base_pnpmgr < 1)
        {
            hps_warn("hps_num_base_pnpmgr_proc_write, bad argument(%u)\n", little_num_base_pnpmgr);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_base_pnpmgr = little_num_base_pnpmgr;
        num_online = num_online_little_cpus();
        if ((num_online < little_num_base_pnpmgr) &&
            (num_online < hps_ctxt.little_num_limit_pnpmgr) &&
            (num_online < min(hps_ctxt.little_num_limit_thermal, hps_ctxt.little_num_limit_low_battery)) &&
            (num_online < min(hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.little_num_limit_power_serv)))
        {
            hps_task_wakeup_nolock();
        }

        
        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else
    {
        hps_warn("hps_num_base_pnpmgr_proc_write, bad argument\n");
    }

    return -EINVAL;
}

PROC_FOPS_RW(num_base_pnpmgr);

static int hps_num_limit_pnpmgr_proc_show(struct seq_file *m, void *v)
{
    if (hps_ctxt.is_hmp)
        seq_printf(m, "%u %u\n", hps_ctxt.little_num_limit_pnpmgr, hps_ctxt.big_num_limit_pnpmgr);
    else
        seq_printf(m, "%u\n", hps_ctxt.little_num_limit_pnpmgr);
    return 0;
}

static int hps_num_limit_pnpmgr_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    int len = 0, little_num_limit_pnpmgr = 0, big_num_limit_pnpmgr = 0;
    char desc[32];

    len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
    if (copy_from_user(desc, buffer, len))
    {
        return 0;
    }
    desc[len] = '\0';

    if (hps_ctxt.is_hmp && (sscanf(desc, "%u %u", &little_num_limit_pnpmgr, &big_num_limit_pnpmgr) == 2))
    {
        if (little_num_limit_pnpmgr > num_possible_little_cpus()
            || little_num_limit_pnpmgr < 1)
        {
            hps_warn("hps_num_limit_pnpmgr_proc_write, bad argument(%u, %u)\n", little_num_limit_pnpmgr, big_num_limit_pnpmgr);
            return -EINVAL;
        }

        if (big_num_limit_pnpmgr > num_possible_big_cpus())
        {
            hps_warn("hps_num_limit_pnpmgr_proc_write, bad argument(%u, %u)\n", little_num_limit_pnpmgr, big_num_limit_pnpmgr);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_limit_pnpmgr = little_num_limit_pnpmgr;
        hps_ctxt.big_num_limit_pnpmgr = big_num_limit_pnpmgr;
        if (num_online_big_cpus() > big_num_limit_pnpmgr)
            hps_task_wakeup_nolock();
        else if (num_online_little_cpus() > little_num_limit_pnpmgr)
            hps_task_wakeup_nolock();

        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else if (!hps_ctxt.is_hmp && (sscanf(desc, "%u", &little_num_limit_pnpmgr) == 1))
    {
        int nr_cpus = num_possible_little_cpus();

        if (little_num_limit_pnpmgr > nr_cpus) {
            little_num_limit_pnpmgr = nr_cpus;
        }

        if (little_num_limit_pnpmgr < 1)
        {
            hps_warn("hps_num_limit_pnpmgr_proc_write, bad argument(%u)\n", little_num_limit_pnpmgr);
            return -EINVAL;
        }

        mutex_lock(&hps_ctxt.lock);

        hps_ctxt.little_num_limit_pnpmgr = little_num_limit_pnpmgr;
        if (num_online_little_cpus() > little_num_limit_pnpmgr)
            hps_task_wakeup_nolock();

        mutex_unlock(&hps_ctxt.lock);

        return count;
    }
    else
    {
        hps_warn("hps_num_limit_pnpmgr_proc_write, bad argument\n");
    }

    return -EINVAL;
}

PROC_FOPS_RW(num_limit_pnpmgr);
#endif 


static int hps_test0_proc_show(struct seq_file *m, void *v)
{
    seq_printf(m, "%u\n", hps_ctxt.test0);

    
    on_each_cpu((smp_call_func_t)dump_stack, NULL, 1);


    return 0;
}

static int hps_test0_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    int len = 0, test0 = 0;
    char desc[32];

    len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
    if (copy_from_user(desc, buffer, len))
    {
        return 0;
    }
    desc[len] = '\0';

    if (sscanf(desc, "%u", &test0) == 1)
    {
        hps_ctxt.test0 = test0;

        switch (test0)
        {
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                
                hps_warn("SPM_CA7_CPU0_PWR_CON: 0x%08x\n", REG_READ(SPM_CA7_CPU0_PWR_CON));
                hps_warn("SPM_CA7_CPU1_PWR_CON: 0x%08x\n", REG_READ(SPM_CA7_CPU1_PWR_CON));
                hps_warn("SPM_CA7_CPU2_PWR_CON: 0x%08x\n", REG_READ(SPM_CA7_CPU2_PWR_CON));
                hps_warn("SPM_CA7_CPU3_PWR_CON: 0x%08x\n", REG_READ(SPM_CA7_CPU3_PWR_CON));
                hps_warn("SPM_CA7_DBG_PWR_CON: 0x%08x\n", REG_READ(SPM_CA7_DBG_PWR_CON));
                hps_warn("SPM_CA7_CPUTOP_PWR_CON: 0x%08x\n", REG_READ(SPM_CA7_CPUTOP_PWR_CON));
                hps_warn("SPM_CA7_CPU0_L1_PDN: 0x%08x\n", REG_READ(SPM_CA7_CPU0_L1_PDN));
                hps_warn("SPM_CA7_CPU1_L1_PDN: 0x%08x\n", REG_READ(SPM_CA7_CPU1_L1_PDN));
                hps_warn("SPM_CA7_CPU2_L1_PDN: 0x%08x\n", REG_READ(SPM_CA7_CPU2_L1_PDN));
                hps_warn("SPM_CA7_CPU3_L1_PDN: 0x%08x\n", REG_READ(SPM_CA7_CPU3_L1_PDN));
                hps_warn("SPM_CA7_CPUTOP_L2_PDN: 0x%08x\n", REG_READ(SPM_CA7_CPUTOP_L2_PDN));
                hps_warn("SPM_CA15_CPU0_PWR_CON: 0x%08x\n", REG_READ(SPM_CA15_CPU0_PWR_CON));
                hps_warn("SPM_CA15_CPU1_PWR_CON: 0x%08x\n", REG_READ(SPM_CA15_CPU1_PWR_CON));
                hps_warn("SPM_CA15_CPU2_PWR_CON: 0x%08x\n", REG_READ(SPM_CA15_CPU2_PWR_CON));
                hps_warn("SPM_CA15_CPU3_PWR_CON: 0x%08x\n", REG_READ(SPM_CA15_CPU3_PWR_CON));
                hps_warn("SPM_CA15_CPUTOP_PWR_CON: 0x%08x\n", REG_READ(SPM_CA15_CPUTOP_PWR_CON));
                hps_warn("SPM_CA15_L1_PWR_CON: 0x%08x\n", REG_READ(SPM_CA15_L1_PWR_CON));
                hps_warn("SPM_CA15_L2_PWR_CON: 0x%08x\n", REG_READ(SPM_CA15_L2_PWR_CON));
                break;
            case 4:
                
                break;
        }

        return count;
    }
    else
    {
        hps_warn("hps_test0_proc_write, bad argument\n");
    }

    return -EINVAL;
}

PROC_FOPS_RW(test0);

static int hps_test1_proc_show(struct seq_file *m, void *v)
{
    seq_printf(m, "%u\n", hps_ctxt.test1);

    return 0;
}

static int hps_test1_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    int len = 0, test1 = 0;
    char desc[32];

    len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
    if (copy_from_user(desc, buffer, len))
    {
        return 0;
    }
    desc[len] = '\0';

    if (sscanf(desc, "%u", &test1) == 1)
    {
        hps_ctxt.test1 = test1;

        switch (test1)
        {
            case 1:
                hps_core_init();
                break;
            case 2:
                hps_core_deinit();
                break;
            case 3:
                hps_task_start();
                break;
            case 4:
                hps_task_stop();
                break;
            case 5:
                hps_task_wakeup();
                break;
            case 6:
                hps_ctxt_print_basic(1);
                break;
            case 7:
                hps_ctxt_print_algo_config(1);
                break;
            case 8:
                hps_ctxt_print_algo_bound(1);
                break;
            case 9:
                hps_ctxt_print_algo_stats_cur(1);
                break;
        }

        return count;
    }
    else
    {
        hps_warn("hps_test1_proc_write, bad argument\n");
    }

    return -EINVAL;
}

PROC_FOPS_RW(test1);

static int hps_memory_debug_proc_show(struct seq_file *m, void *v)
{
    seq_printf(m, "SPM_BASE ==> 0x%p\n", SPM_BASE);
    seq_printf(m, "[0x%p]=0x%08x\n", g_memory_debug, REG_READ(g_memory_debug));
    hps_warn("SPM_BASE ==> 0x%p\n", SPM_BASE);
    hps_warn("[0x%p]=0x%08x\n", g_memory_debug, REG_READ(g_memory_debug));

    return 0;
}

static int hps_memory_debug_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    int len = 0;
    char desc[32];
    char cmd1[16];
    long cmd2;
    int cmd3;
    
    len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
    if (copy_from_user(desc, buffer, len))
    {
        return 0;
    }
    desc[len] = '\0';
    
    if (sscanf(desc, "%s %lx %x", cmd1, &cmd2, &cmd3) == 3)
    {
        if (strcmp(cmd1, "w") == 0)
        {
            hps_warn("write [0x%lx] to 0x%08x\n", cmd2, cmd3);
            REG_WRITE(cmd2, cmd3);
        }
        return count;
    }
    else if (sscanf(desc, "%s %lx", cmd1, &cmd2) == 2)
    {
        if (strcmp(cmd1, "r") == 0)
        {
            hps_warn("read [0x%lx] as 0x%08x\n", cmd2, REG_READ(cmd2));
            g_memory_debug = (void *)cmd2;
        }
        return count;
    }
    else
    {
        hps_warn("hps_memory_debug_proc_write, bad argument\n");
    }
    
    return -EINVAL;
}

PROC_FOPS_RW(memory_debug);

int hps_procfs_init()
{
    
    struct proc_dir_entry *hps_dir = NULL;
    int r = 0;
    int i;

    struct pentry {
        const char *name;
        const struct file_operations *fops;
    };

    const struct pentry entries[] = {
        PROC_ENTRY(init_state),
        PROC_ENTRY(state),
        PROC_ENTRY(enabled),
        PROC_ENTRY(early_suspend_enabled),
        PROC_ENTRY(suspend_enabled),
        PROC_ENTRY(cur_dump_enabled),
        PROC_ENTRY(stats_dump_enabled),
        PROC_ENTRY(up_threshold),
        PROC_ENTRY(up_times),
        PROC_ENTRY(down_threshold),
        PROC_ENTRY(down_times),
        PROC_ENTRY(es_up_threshold),
        PROC_ENTRY(es_up_times),
        PROC_ENTRY(es_down_threshold),
        PROC_ENTRY(es_down_times),
        PROC_ENTRY(input_boost_enabled),
        PROC_ENTRY(input_boost_cpu_num),
        PROC_ENTRY(rush_boost_enabled),
        PROC_ENTRY(rush_boost_threshold),
        PROC_ENTRY(rush_boost_times),
        PROC_ENTRY(tlp_times),
        PROC_ENTRY(num_base_perf_serv),
        PROC_ENTRY(num_limit_thermal),
        PROC_ENTRY(num_limit_low_battery),
        PROC_ENTRY(num_limit_ultra_power_saving),
        PROC_ENTRY(num_limit_power_serv),
#ifdef CONFIG_HTC_PNPMGR
        PROC_ENTRY(num_base_pnpmgr),
        PROC_ENTRY(num_limit_pnpmgr),
#endif
        PROC_ENTRY(test0),
        PROC_ENTRY(test1),
        PROC_ENTRY(memory_debug),
    };

    hps_warn("hps_procfs_init\n");

    hps_dir = proc_mkdir("hps", NULL);
    if (hps_dir == NULL)
    {
        hps_emerg("mkdir /proc/hps fail\n");
        return -1;
    }
    else
    {
        for (i = 0; i < ARRAY_SIZE(entries); i++)
        {
            if (!proc_create(entries[i].name, S_IRUGO | S_IWUSR | S_IWGRP, hps_dir, entries[i].fops))
                hps_emerg("create /proc/cpufreq/%s failed\n", entries[i].name);
        }
    }

    g_memory_debug = SPM_CA15_CPUTOP_PWR_CON;

    return r;
}
