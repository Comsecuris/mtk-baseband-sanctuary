
#include <linux/kernel.h>               
#include <linux/module.h>               //MODULE_DESCRIPTION, MODULE_LICENSE
#include <linux/init.h>                 
#include <linux/cpu.h>                  
#include <linux/kthread.h>              
#include <linux/wakelock.h>             
#include <asm-generic/bug.h>            

#include <mach/hotplug.h>
#include <mach/mt_spm_cpu.h>
#include <mach/mt_spm_mtcmos.h>

#include <mach/mt_hotplug_strategy_internal.h>


#define STATIC 






static int _hps_task_main(void *data)
{
    int cnt = 0;
    void (*algo_func_ptr)(void);

    hps_ctxt_print_basic(1);

    if (hps_ctxt.is_hmp)
        algo_func_ptr = hps_algo_hmp;
    else
        algo_func_ptr = hps_algo_smp;

    while (1)
    {
        
        
        
        
        

        (*algo_func_ptr)();

        
        if(hps_ctxt.state == STATE_EARLY_SUSPEND)
        	wait_event_timeout(hps_ctxt.wait_queue, atomic_read(&hps_ctxt.is_ondemand) != 0, msecs_to_jiffies(HPS_TIMER_INTERVAL_MS*4));
        else
          wait_event_timeout(hps_ctxt.wait_queue, atomic_read(&hps_ctxt.is_ondemand) != 0, msecs_to_jiffies(HPS_TIMER_INTERVAL_MS));

        

        if (kthread_should_stop())
            break;
    } 

    hps_warn("leave _hps_task_main, cnt:%08d\n", cnt++);
    return 0;
}

int hps_task_start(void)
{
    struct sched_param param = { .sched_priority = HPS_TASK_PRIORITY };
    const struct cpumask *mask = get_cpu_mask(0);

    if (hps_ctxt.tsk_struct_ptr == NULL)
    {
        hps_ctxt.tsk_struct_ptr = kthread_create(_hps_task_main, NULL, "hps_main");
        if (IS_ERR(hps_ctxt.tsk_struct_ptr))
            return PTR_ERR(hps_ctxt.tsk_struct_ptr);

        sched_setscheduler_nocheck(hps_ctxt.tsk_struct_ptr, SCHED_FIFO, &param);
        sched_setaffinity(hps_ctxt.tsk_struct_ptr->pid, mask);
        get_task_struct(hps_ctxt.tsk_struct_ptr);
        wake_up_process(hps_ctxt.tsk_struct_ptr);
        hps_warn("hps_task_start success, ptr: %p, pid: %d\n", hps_ctxt.tsk_struct_ptr, hps_ctxt.tsk_struct_ptr->pid);
    }
    else
    {
        hps_warn("hps task already exist, ptr: %p, pid: %d\n", hps_ctxt.tsk_struct_ptr, hps_ctxt.tsk_struct_ptr->pid);
    }

    return 0;
}

void hps_task_stop(void)
{
    if (hps_ctxt.tsk_struct_ptr)
    {
        kthread_stop(hps_ctxt.tsk_struct_ptr);
        put_task_struct(hps_ctxt.tsk_struct_ptr);
        hps_ctxt.tsk_struct_ptr = NULL;
    }
}

void hps_task_wakeup_nolock(void)
{
    if (hps_ctxt.tsk_struct_ptr)
    {
        atomic_set(&hps_ctxt.is_ondemand, 1);
        wake_up(&hps_ctxt.wait_queue);
    }
}

void hps_task_wakeup(void)
{
    mutex_lock(&hps_ctxt.lock);

    hps_task_wakeup_nolock();

    mutex_unlock(&hps_ctxt.lock);
}

int hps_core_init(void)
{
    int r = 0;

    hps_warn("hps_core_init\n");

    
    r = hps_task_start();
    if (r)
    {
        hps_error("hps_task_start fail(%d)\n", r);
        return r;
    }

    return r;
}

int hps_core_deinit(void)
{
    int r = 0;

    hps_warn("hps_core_deinit\n");

    hps_task_stop();

    return r;
}
