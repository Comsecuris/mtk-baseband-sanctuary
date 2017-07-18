
#include <linux/kernel.h>               
#include <linux/module.h>               //MODULE_DESCRIPTION, MODULE_LICENSE
#include <linux/init.h>                 
#include <linux/cpu.h>                  
#include <linux/kthread.h>              
#include <linux/wakelock.h>             
#include <linux/delay.h>                
#include <asm-generic/bug.h>            

#include <mach/hotplug.h>
#include <mach/mt_spm_cpu.h>
#include <mach/mt_spm_mtcmos.h>

#include <mach/mt_hotplug_strategy_internal.h>


#define STATIC 






    
void hps_algo_hmp(void)
{
    unsigned int cpu;
    unsigned int val;
    struct cpumask little_online_cpumask;
    struct cpumask big_online_cpumask;
    unsigned int little_num_base, little_num_limit, little_num_online;
    unsigned int big_num_base, big_num_limit, big_num_online;
    
    char str1[64];
    char str2[64];
    int i, j;
    char * str1_ptr = str1;
    char * str2_ptr = str2;

    if (!hps_ctxt.enabled)
    {
        atomic_set(&hps_ctxt.is_ondemand, 0);
        return;
    }

    hps_ctxt.cur_loads = 0;
    str1_ptr = str1;
    str2_ptr = str2;

    for_each_possible_cpu(cpu)
    {
        per_cpu(hps_percpu_ctxt, cpu).load = hps_cpu_get_percpu_load(cpu);
        hps_ctxt.cur_loads += per_cpu(hps_percpu_ctxt, cpu).load;

        if (hps_ctxt.cur_dump_enabled)
        {
            if (cpu_online(cpu))
                i = sprintf(str1_ptr, "%4u", 1);
            else
                i = sprintf(str1_ptr, "%4u", 0);
            str1_ptr += i;
            j = sprintf(str2_ptr, "%4u", per_cpu(hps_percpu_ctxt, cpu).load);
            str2_ptr += j;
        }
    }
    hps_ctxt.cur_nr_heavy_task = hps_cpu_get_nr_heavy_task();
    hps_cpu_get_tlp(&hps_ctxt.cur_tlp, &hps_ctxt.cur_iowait);

    mutex_lock(&hps_ctxt.lock);
    hps_ctxt.action = ACTION_NONE;
    atomic_set(&hps_ctxt.is_ondemand, 0);

    little_num_limit = min(hps_ctxt.little_num_limit_thermal, hps_ctxt.little_num_limit_low_battery);
    little_num_limit = min3(little_num_limit, hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.little_num_limit_power_serv);
    little_num_base = hps_ctxt.little_num_base_perf_serv;
#ifdef CONFIG_HTC_PNPMGR
    little_num_limit = min(little_num_limit, hps_ctxt.little_num_limit_pnpmgr);
    little_num_base = max(little_num_base, hps_ctxt.little_num_base_pnpmgr);
#endif
    cpumask_and(&little_online_cpumask, &hps_ctxt.little_cpumask, cpu_online_mask);
    little_num_online = cpumask_weight(&little_online_cpumask);
    
    big_num_limit = min(hps_ctxt.big_num_limit_thermal, hps_ctxt.big_num_limit_low_battery);
    big_num_limit = min3(big_num_limit, hps_ctxt.big_num_limit_ultra_power_saving, hps_ctxt.big_num_limit_power_serv);
    big_num_base = max(hps_ctxt.cur_nr_heavy_task, hps_ctxt.big_num_base_perf_serv);
#ifdef CONFIG_HTC_PNPMGR
    big_num_limit = min(big_num_limit, hps_ctxt.big_num_limit_pnpmgr);
    big_num_base = max(big_num_base, hps_ctxt.big_num_base_pnpmgr);
#endif
    cpumask_and(&big_online_cpumask, &hps_ctxt.big_cpumask, cpu_online_mask);
    big_num_online = cpumask_weight(&big_online_cpumask);
    if (hps_ctxt.cur_dump_enabled)
    {
        hps_debug(" CPU:%s\n", str1);
        hps_debug("LOAD:%s\n", str2);
#ifdef CONFIG_HTC_PNPMGR
        hps_debug("loads(%u), hvy_tsk(%u), tlp(%u), iowait(%u), limit_t(%u)(%u), limit_lb(%u)(%u), limit_ups(%u)(%u), limit_pos(%u)(%u), base_pes(%u)(%u), limit_pnp(%u)(%u), base_pnp(%u)(%u)\n",
            hps_ctxt.cur_loads, hps_ctxt.cur_nr_heavy_task, hps_ctxt.cur_tlp, hps_ctxt.cur_iowait,
            hps_ctxt.little_num_limit_thermal, hps_ctxt.big_num_limit_thermal,
            hps_ctxt.little_num_limit_low_battery, hps_ctxt.big_num_limit_low_battery,
            hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.big_num_limit_ultra_power_saving,
            hps_ctxt.little_num_limit_power_serv, hps_ctxt.big_num_limit_power_serv,
            hps_ctxt.little_num_base_perf_serv, hps_ctxt.big_num_base_perf_serv,
            hps_ctxt.little_num_limit_pnpmgr, hps_ctxt.big_num_limit_pnpmgr,
            hps_ctxt.little_num_base_pnpmgr, hps_ctxt.big_num_base_pnpmgr);
#else
        hps_debug("loads(%u), hvy_tsk(%u), tlp(%u), iowait(%u), limit_t(%u)(%u), limit_lb(%u)(%u), limit_ups(%u)(%u), limit_pos(%u)(%u), base_pes(%u)(%u)\n", 
            hps_ctxt.cur_loads, hps_ctxt.cur_nr_heavy_task, hps_ctxt.cur_tlp, hps_ctxt.cur_iowait,
            hps_ctxt.little_num_limit_thermal, hps_ctxt.big_num_limit_thermal,
            hps_ctxt.little_num_limit_low_battery, hps_ctxt.big_num_limit_low_battery,
            hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.big_num_limit_ultra_power_saving,
            hps_ctxt.little_num_limit_power_serv, hps_ctxt.big_num_limit_power_serv,
            hps_ctxt.little_num_base_perf_serv, hps_ctxt.big_num_base_perf_serv);
#endif
    }

    if (big_num_online > big_num_limit)
    {
        val =  big_num_online - big_num_limit;
        for (cpu = hps_ctxt.big_cpu_id_max; cpu >= hps_ctxt.big_cpu_id_min; --cpu)
        {
            if (cpumask_test_cpu(cpu, &big_online_cpumask))
            {
                cpu_down(cpu);
                cpumask_clear_cpu(cpu, &big_online_cpumask);
                --big_num_online;
                if (--val == 0)
                    break;
            }
        }
        BUG_ON(val);
        set_bit(ACTION_LIMIT_BIG, (unsigned long *)&hps_ctxt.action);
    }
    if (little_num_online > little_num_limit)
    {
        val =  little_num_online - little_num_limit;
        for (cpu = hps_ctxt.little_cpu_id_max; cpu > hps_ctxt.little_cpu_id_min; --cpu)
        {
            if (cpumask_test_cpu(cpu, &little_online_cpumask))
            {
                cpu_down(cpu);
                cpumask_clear_cpu(cpu, &little_online_cpumask);
                --little_num_online;
                if (--val == 0)
                    break;
            }
        }
        BUG_ON(val);
        set_bit(ACTION_LIMIT_LITTLE, (unsigned long *)&hps_ctxt.action);
    }
    if (hps_ctxt.action)
        goto ALGO_END_WITH_ACTION;

    BUG_ON(big_num_online > big_num_limit);
    BUG_ON(little_num_online > little_num_limit);
    if ((big_num_online < big_num_base) && (big_num_online < big_num_limit) && (hps_ctxt.state == STATE_LATE_RESUME))
    {
        val =  min(big_num_base, big_num_limit) - big_num_online;
        for (cpu = hps_ctxt.big_cpu_id_min; cpu <= hps_ctxt.big_cpu_id_max; ++cpu)
        {
            if (!cpumask_test_cpu(cpu, &big_online_cpumask))
            {
                cpu_up(cpu);
                cpumask_set_cpu(cpu, &big_online_cpumask);
                ++big_num_online;
                if (--val == 0)
                    break;
            }
        }
        BUG_ON(val);
        set_bit(ACTION_BASE_BIG, (unsigned long *)&hps_ctxt.action);
    }
#ifdef CONFIG_HTC_PNPMGR
    if ((little_num_online < little_num_base) && (little_num_online < little_num_limit) &&
        (little_num_online + big_num_online <
         min(little_num_base, little_num_limit) + max(hps_ctxt.big_num_base_perf_serv, hps_ctxt.big_num_base_pnpmgr)))
#else
    if ((little_num_online < little_num_base) && (little_num_online < little_num_limit) &&
        (little_num_online + big_num_online < hps_ctxt.little_num_base_perf_serv + hps_ctxt.big_num_base_perf_serv))
#endif
    {
        val =  min(little_num_base, little_num_limit) - little_num_online;
#ifdef CONFIG_HTC_PNPMGR
        if (big_num_online > max(hps_ctxt.big_num_base_perf_serv, hps_ctxt.big_num_base_pnpmgr))
            val -= big_num_online - max(hps_ctxt.big_num_base_perf_serv, hps_ctxt.big_num_base_pnpmgr);
#else
        if (big_num_online > hps_ctxt.big_num_base_perf_serv)
            val -= big_num_online - hps_ctxt.big_num_base_perf_serv;
#endif
        for (cpu = hps_ctxt.little_cpu_id_min; cpu <= hps_ctxt.little_cpu_id_max; ++cpu)
        {
            if (!cpumask_test_cpu(cpu, &little_online_cpumask))
            {
                cpu_up(cpu);
                cpumask_set_cpu(cpu, &little_online_cpumask);
                ++little_num_online;
                if (--val == 0)
                    break;
            }
        }
        BUG_ON(val);
        set_bit(ACTION_BASE_LITTLE, (unsigned long *)&hps_ctxt.action);
    }
    if (hps_ctxt.action)
        goto ALGO_END_WITH_ACTION;

    val = hps_ctxt.tlp_history[hps_ctxt.tlp_history_index];
    hps_ctxt.tlp_history[hps_ctxt.tlp_history_index] = hps_ctxt.cur_tlp;
    hps_ctxt.tlp_sum += hps_ctxt.cur_tlp;
    hps_ctxt.tlp_history_index = (hps_ctxt.tlp_history_index + 1 == hps_ctxt.tlp_times) ? 0 : hps_ctxt.tlp_history_index + 1;
    ++hps_ctxt.tlp_count;
    if (hps_ctxt.tlp_count > hps_ctxt.tlp_times)
    {
        BUG_ON(hps_ctxt.tlp_sum < val);
        hps_ctxt.tlp_sum -= val;
        hps_ctxt.tlp_avg = hps_ctxt.tlp_sum / hps_ctxt.tlp_times;
    }
    else
    {
        hps_ctxt.tlp_avg = hps_ctxt.tlp_sum / hps_ctxt.tlp_count;
    }
    if (hps_ctxt.stats_dump_enabled)
        hps_ctxt_print_algo_stats_tlp(0);

    if (hps_ctxt.rush_boost_enabled)
    {
        if (hps_ctxt.cur_loads > hps_ctxt.rush_boost_threshold * (little_num_online + big_num_online))
            ++hps_ctxt.rush_count;
        else
            hps_ctxt.rush_count = 0;

        if ((hps_ctxt.rush_count >= hps_ctxt.rush_boost_times) &&
            ((little_num_online + big_num_online) * 100 < hps_ctxt.tlp_avg))
        {
            val = hps_ctxt.tlp_avg / 100 + (hps_ctxt.tlp_avg % 100 ? 1 : 0);
            BUG_ON(!(val > little_num_online + big_num_online));
            if (val > num_possible_cpus())
                val = num_possible_cpus();

            val -= little_num_online + big_num_online;
            if ((val) && (little_num_online < little_num_limit))
            {
                for (cpu = hps_ctxt.little_cpu_id_min; cpu <= hps_ctxt.little_cpu_id_max; ++cpu)
                {
                    if (!cpumask_test_cpu(cpu, &little_online_cpumask))
                    {
                        cpu_up(cpu);
                        cpumask_set_cpu(cpu, &little_online_cpumask);
                        ++little_num_online;
                        if (--val == 0)
                            break;
                    }
                }
                set_bit(ACTION_RUSH_BOOST_LITTLE, (unsigned long *)&hps_ctxt.action);
            }
            else if ((val) && (big_num_online < big_num_limit) && (hps_ctxt.state == STATE_LATE_RESUME))
            {
                for (cpu = hps_ctxt.big_cpu_id_min; cpu <= hps_ctxt.big_cpu_id_max; ++cpu)
                {
                    if (!cpumask_test_cpu(cpu, &big_online_cpumask))
                    {
                        cpu_up(cpu);
                        cpumask_set_cpu(cpu, &big_online_cpumask);
                        ++big_num_online;
                        if (--val == 0)
                            break;
                    }
                }
                set_bit(ACTION_RUSH_BOOST_BIG, (unsigned long *)&hps_ctxt.action);
            }
        }
    } 
    if (hps_ctxt.action)
        goto ALGO_END_WITH_ACTION;

    if ((little_num_online + big_num_online) < num_possible_cpus())
    {
        val = hps_ctxt.up_loads_history[hps_ctxt.up_loads_history_index];
        hps_ctxt.up_loads_history[hps_ctxt.up_loads_history_index] = hps_ctxt.cur_loads;
        hps_ctxt.up_loads_sum += hps_ctxt.cur_loads;
        hps_ctxt.up_loads_history_index = (hps_ctxt.up_loads_history_index + 1 == hps_ctxt.up_times) ? 0 : hps_ctxt.up_loads_history_index + 1;
        ++hps_ctxt.up_loads_count;
        
        if (hps_ctxt.up_loads_count > hps_ctxt.up_times)
        {
            BUG_ON(hps_ctxt.up_loads_sum < val);
            hps_ctxt.up_loads_sum -= val;
        }
        if (hps_ctxt.stats_dump_enabled)
            hps_ctxt_print_algo_stats_up(0);

        if (hps_ctxt.up_loads_count >= hps_ctxt.up_times)
        {
            if (hps_ctxt.up_loads_sum > hps_ctxt.up_threshold * hps_ctxt.up_times * (little_num_online + big_num_online))
            {
                if (little_num_online < little_num_limit)
                {
                    for (cpu = hps_ctxt.little_cpu_id_min; cpu <= hps_ctxt.little_cpu_id_max; ++cpu)
                    {
                        if (!cpumask_test_cpu(cpu, &little_online_cpumask))
                        {
                            cpu_up(cpu);
                            cpumask_set_cpu(cpu, &little_online_cpumask);
                            ++little_num_online;
                            break;
                        }
                    }
                    set_bit(ACTION_UP_LITTLE, (unsigned long *)&hps_ctxt.action);
                }
                else if ((big_num_online < big_num_limit) && (hps_ctxt.state == STATE_LATE_RESUME))
                {
                    for (cpu = hps_ctxt.big_cpu_id_min; cpu <= hps_ctxt.big_cpu_id_max; ++cpu)
                    {
                        if (!cpumask_test_cpu(cpu, &big_online_cpumask))
                        {
                            cpu_up(cpu);
                            cpumask_set_cpu(cpu, &big_online_cpumask);
                            ++big_num_online;
                            break;
                        }
                    }
                    set_bit(ACTION_UP_BIG, (unsigned long *)&hps_ctxt.action);
                }
            }
        } 
    } 
    if (hps_ctxt.action)
        goto ALGO_END_WITH_ACTION;

    if (little_num_online + big_num_online > 1)
    {
        val = hps_ctxt.down_loads_history[hps_ctxt.down_loads_history_index];
        hps_ctxt.down_loads_history[hps_ctxt.down_loads_history_index] = hps_ctxt.cur_loads;
        hps_ctxt.down_loads_sum += hps_ctxt.cur_loads;
        hps_ctxt.down_loads_history_index = (hps_ctxt.down_loads_history_index + 1 == hps_ctxt.down_times) ? 0 : hps_ctxt.down_loads_history_index + 1;
        ++hps_ctxt.down_loads_count;
        
        if (hps_ctxt.down_loads_count > hps_ctxt.down_times)
        {
            BUG_ON(hps_ctxt.down_loads_sum < val);
            hps_ctxt.down_loads_sum -= val;
        }
        if (hps_ctxt.stats_dump_enabled)
            hps_ctxt_print_algo_stats_down(0);

        if (hps_ctxt.down_loads_count >= hps_ctxt.down_times)
        {
            unsigned int down_threshold = hps_ctxt.down_threshold * hps_ctxt.down_times;

            val = little_num_online + big_num_online;
            while (hps_ctxt.down_loads_sum < down_threshold * (val - 1))
                --val;
            val = little_num_online + big_num_online - val;

            if ((val) && (big_num_online > big_num_base))
            {
                for (cpu = hps_ctxt.big_cpu_id_max; cpu >= hps_ctxt.big_cpu_id_min; --cpu)
                {
                    if (cpumask_test_cpu(cpu, &big_online_cpumask))
                    {
                        cpu_down(cpu);
                        cpumask_clear_cpu(cpu, &big_online_cpumask);
                        --big_num_online;
                        if (--val == 0)
                            break;
                    }
                }
                set_bit(ACTION_DOWN_BIG, (unsigned long *)&hps_ctxt.action);
            }
            else if ((val) && (little_num_online > little_num_base))
            {
                for (cpu = hps_ctxt.little_cpu_id_max; cpu > hps_ctxt.little_cpu_id_min; --cpu)
                {
                    if (cpumask_test_cpu(cpu, &little_online_cpumask))
                    {
                        cpu_down(cpu);
                        cpumask_clear_cpu(cpu, &little_online_cpumask);
                        --little_num_online;
                        if (--val == 0)
                            break;
                    }
                }
                set_bit(ACTION_DOWN_LITTLE, (unsigned long *)&hps_ctxt.action);
            }
        } 
    } 
    if (hps_ctxt.action)
        goto ALGO_END_WITH_ACTION;

    if (hps_ctxt.down_loads_count >= hps_ctxt.down_times)
    {
        if ((little_num_online < little_num_limit) && (big_num_online > big_num_base))
        {
            
            for (val = hps_ctxt.big_cpu_id_max; val >= hps_ctxt.big_cpu_id_min; --val)
            {
                if (cpumask_test_cpu(val, &big_online_cpumask))
                    break;
            }
            BUG_ON(val < hps_ctxt.big_cpu_id_min);

            
            if (per_cpu(hps_percpu_ctxt, val).load * CPU_DMIPS_BIG_LITTLE_DIFF / 100 + 
                hps_ctxt.up_loads_sum / hps_ctxt.up_times <= hps_ctxt.up_threshold  * (little_num_online + big_num_online))
            {
                
                for (cpu = hps_ctxt.little_cpu_id_min; cpu <= hps_ctxt.little_cpu_id_max; ++cpu)
                {
                    if (!cpumask_test_cpu(cpu, &little_online_cpumask))
                    {
                        cpu_up(cpu);
                        cpumask_set_cpu(cpu, &little_online_cpumask);
                        ++little_num_online;
                        break;
                    }
                }

                
                cpu_down(val);
                cpumask_clear_cpu(cpu, &big_online_cpumask);
                --big_num_online;
                set_bit(ACTION_BIG_TO_LITTLE, (unsigned long *)&hps_ctxt.action);
            }
        } 
    } 
    if (!hps_ctxt.action)
        goto ALGO_END_WO_ACTION;

ALGO_END_WITH_ACTION:
#ifdef CONFIG_HTC_PNPMGR
    hps_warn("(%04lx)(%u)(%u)action end(%u)(%u)(%u)(%u) (%u)(%u)(%u)(%u)(%u)(%u)(%u)(%u)(%u)(%u) (%u)(%u)(%u)(%u) (%u)(%u)(%u) (%u)(%u)(%u) (%u)(%u)(%u)(%u)(%u)\n",
        hps_ctxt.action, little_num_online, big_num_online,
        hps_ctxt.cur_loads, hps_ctxt.cur_tlp, hps_ctxt.cur_iowait, hps_ctxt.cur_nr_heavy_task,
        hps_ctxt.little_num_limit_thermal, hps_ctxt.big_num_limit_thermal,
        hps_ctxt.little_num_limit_low_battery, hps_ctxt.big_num_limit_low_battery,
        hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.big_num_limit_ultra_power_saving,
        hps_ctxt.little_num_limit_power_serv, hps_ctxt.big_num_limit_power_serv,
        hps_ctxt.little_num_base_perf_serv, hps_ctxt.big_num_base_perf_serv,
        hps_ctxt.little_num_limit_pnpmgr, hps_ctxt.big_num_limit_pnpmgr, hps_ctxt.little_num_base_pnpmgr, hps_ctxt.big_num_base_pnpmgr,
        hps_ctxt.up_loads_sum, hps_ctxt.up_loads_count, hps_ctxt.up_loads_history_index,
        hps_ctxt.down_loads_sum, hps_ctxt.down_loads_count, hps_ctxt.down_loads_history_index,
        hps_ctxt.rush_count, hps_ctxt.tlp_sum, hps_ctxt.tlp_count, hps_ctxt.tlp_history_index, hps_ctxt.tlp_avg);
#else
    hps_warn("(%04lx)(%u)(%u)action end(%u)(%u)(%u)(%u) (%u)(%u)(%u)(%u)(%u)(%u)(%u)(%u)(%u)(%u) (%u)(%u)(%u) (%u)(%u)(%u) (%u)(%u)(%u)(%u)(%u)\n",
        hps_ctxt.action, little_num_online, big_num_online,
        hps_ctxt.cur_loads, hps_ctxt.cur_tlp, hps_ctxt.cur_iowait, hps_ctxt.cur_nr_heavy_task, 
        hps_ctxt.little_num_limit_thermal, hps_ctxt.big_num_limit_thermal,
        hps_ctxt.little_num_limit_low_battery, hps_ctxt.big_num_limit_low_battery,
        hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.big_num_limit_ultra_power_saving,
        hps_ctxt.little_num_limit_power_serv, hps_ctxt.big_num_limit_power_serv,
        hps_ctxt.little_num_base_perf_serv, hps_ctxt.big_num_base_perf_serv,
        hps_ctxt.up_loads_sum, hps_ctxt.up_loads_count, hps_ctxt.up_loads_history_index, 
        hps_ctxt.down_loads_sum, hps_ctxt.down_loads_count, hps_ctxt.down_loads_history_index, 
        hps_ctxt.rush_count, hps_ctxt.tlp_sum, hps_ctxt.tlp_count, hps_ctxt.tlp_history_index, hps_ctxt.tlp_avg);
#endif
    hps_ctxt_reset_stas_nolock();
ALGO_END_WO_ACTION:
    mutex_unlock(&hps_ctxt.lock);

    return;
}

void hps_algo_smp(void)
{
    unsigned int cpu;
    unsigned int val;
    struct cpumask little_online_cpumask;
    unsigned int little_num_base, little_num_limit, little_num_online;
    
    char str1[64];
    char str2[64];
    int i, j;
    char * str1_ptr = str1;
    char * str2_ptr = str2;

    if (!hps_ctxt.enabled)
    {
        atomic_set(&hps_ctxt.is_ondemand, 0);
        return;
    }

    hps_ctxt.cur_loads = 0;
    str1_ptr = str1;
    str2_ptr = str2;

    for_each_possible_cpu(cpu)
    {
        per_cpu(hps_percpu_ctxt, cpu).load = hps_cpu_get_percpu_load(cpu);
        hps_ctxt.cur_loads += per_cpu(hps_percpu_ctxt, cpu).load;

        if (hps_ctxt.cur_dump_enabled)
        {
            if (cpu_online(cpu))
                i = sprintf(str1_ptr, "%4u", 1);
            else
                i = sprintf(str1_ptr, "%4u", 0);
            str1_ptr += i;
            j = sprintf(str2_ptr, "%4u", per_cpu(hps_percpu_ctxt, cpu).load);
            str2_ptr += j;
        }
    }
    hps_ctxt.cur_nr_heavy_task = hps_cpu_get_nr_heavy_task();
    hps_cpu_get_tlp(&hps_ctxt.cur_tlp, &hps_ctxt.cur_iowait);

    mutex_lock(&hps_ctxt.lock);
    hps_ctxt.action = ACTION_NONE;
    atomic_set(&hps_ctxt.is_ondemand, 0);

    little_num_limit = min(hps_ctxt.little_num_limit_thermal, hps_ctxt.little_num_limit_low_battery);
    little_num_limit = min3(little_num_limit, hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.little_num_limit_power_serv);
    little_num_base = hps_ctxt.little_num_base_perf_serv;
#ifdef CONFIG_HTC_PNPMGR
    little_num_limit = min(little_num_limit, hps_ctxt.little_num_limit_pnpmgr);
    little_num_base = max(little_num_base, hps_ctxt.little_num_base_pnpmgr);
#endif
    cpumask_and(&little_online_cpumask, &hps_ctxt.little_cpumask, cpu_online_mask);
    little_num_online = cpumask_weight(&little_online_cpumask);
    if (hps_ctxt.cur_dump_enabled)
    {
        hps_debug(" CPU:%s\n", str1);
        hps_debug("LOAD:%s\n", str2);
#ifdef CONFIG_HTC_PNPMGR
        hps_debug("loads(%u), hvy_tsk(%u), tlp(%u), iowait(%u), limit_t(%u), limit_lb(%u), limit_ups(%u), limit_pos(%u), base_pes(%u), limit_pnp(%u), base_pnp(%u)\n",
            hps_ctxt.cur_loads, hps_ctxt.cur_nr_heavy_task, hps_ctxt.cur_tlp, hps_ctxt.cur_iowait,
            hps_ctxt.little_num_limit_thermal,
            hps_ctxt.little_num_limit_low_battery,
            hps_ctxt.little_num_limit_ultra_power_saving,
            hps_ctxt.little_num_limit_power_serv,
            hps_ctxt.little_num_base_perf_serv,
            hps_ctxt.little_num_limit_pnpmgr,
            hps_ctxt.little_num_base_pnpmgr);
#else
        hps_debug("loads(%u), hvy_tsk(%u), tlp(%u), iowait(%u), limit_t(%u), limit_lb(%u), limit_ups(%u), limit_pos(%u), base_pes(%u)\n", 
            hps_ctxt.cur_loads, hps_ctxt.cur_nr_heavy_task, hps_ctxt.cur_tlp, hps_ctxt.cur_iowait,
            hps_ctxt.little_num_limit_thermal,
            hps_ctxt.little_num_limit_low_battery,
            hps_ctxt.little_num_limit_ultra_power_saving,
            hps_ctxt.little_num_limit_power_serv,
            hps_ctxt.little_num_base_perf_serv);
#endif
    }

    if (little_num_online > little_num_limit)
    {
        val =  little_num_online - little_num_limit;
        for (cpu = hps_ctxt.little_cpu_id_max; cpu > hps_ctxt.little_cpu_id_min; --cpu)
        {
            if (cpumask_test_cpu(cpu, &little_online_cpumask))
            {
                cpu_down(cpu);
                cpumask_clear_cpu(cpu, &little_online_cpumask);
                --little_num_online;
                if (--val == 0)
                    break;
            }
        }
        BUG_ON(val);
        set_bit(ACTION_LIMIT_LITTLE, (unsigned long *)&hps_ctxt.action);
    }
    if (hps_ctxt.action)
        goto ALGO_END_WITH_ACTION;

    BUG_ON(little_num_online > little_num_limit);
    if ((little_num_online < little_num_base) && (little_num_online < little_num_limit))
    {
        val =  min(little_num_base, little_num_limit) - little_num_online;
        for (cpu = hps_ctxt.little_cpu_id_min; cpu <= hps_ctxt.little_cpu_id_max; ++cpu)
        {
            if (!cpumask_test_cpu(cpu, &little_online_cpumask))
            {
                cpu_up(cpu);
                cpumask_set_cpu(cpu, &little_online_cpumask);
                ++little_num_online;
                if (--val == 0)
                    break;
            }
        }
        BUG_ON(val);
        set_bit(ACTION_BASE_LITTLE, (unsigned long *)&hps_ctxt.action);
    }
    if (hps_ctxt.action)
        goto ALGO_END_WITH_ACTION;

    val = hps_ctxt.tlp_history[hps_ctxt.tlp_history_index];
    hps_ctxt.tlp_history[hps_ctxt.tlp_history_index] = hps_ctxt.cur_tlp;
    hps_ctxt.tlp_sum += hps_ctxt.cur_tlp;
    hps_ctxt.tlp_history_index = (hps_ctxt.tlp_history_index + 1 == hps_ctxt.tlp_times) ? 0 : hps_ctxt.tlp_history_index + 1;
    ++hps_ctxt.tlp_count;
    if (hps_ctxt.tlp_count > hps_ctxt.tlp_times)
    {
        BUG_ON(hps_ctxt.tlp_sum < val);
        hps_ctxt.tlp_sum -= val;
        hps_ctxt.tlp_avg = hps_ctxt.tlp_sum / hps_ctxt.tlp_times;
    }
    else
    {
        hps_ctxt.tlp_avg = hps_ctxt.tlp_sum / hps_ctxt.tlp_count;
    }
    if (hps_ctxt.stats_dump_enabled)
        hps_ctxt_print_algo_stats_tlp(0);

    if (hps_ctxt.rush_boost_enabled)
    {
        if (hps_ctxt.cur_loads > hps_ctxt.rush_boost_threshold * little_num_online)
            ++hps_ctxt.rush_count;
        else
            hps_ctxt.rush_count = 0;

        if ((hps_ctxt.rush_count >= hps_ctxt.rush_boost_times) &&
            (little_num_online * 100 < hps_ctxt.tlp_avg))
        {
            val = hps_ctxt.tlp_avg / 100 + (hps_ctxt.tlp_avg % 100 ? 1 : 0);
            BUG_ON(!(val > little_num_online));
            if (val > num_possible_cpus())
                val = num_possible_cpus();

            val -= little_num_online;
            if ((val) && (little_num_online < little_num_limit))
            {
                for (cpu = hps_ctxt.little_cpu_id_min; cpu <= hps_ctxt.little_cpu_id_max; ++cpu)
                {
                    if (!cpumask_test_cpu(cpu, &little_online_cpumask))
                    {
                        cpu_up(cpu);
                        cpumask_set_cpu(cpu, &little_online_cpumask);
                        ++little_num_online;
                        if (--val == 0 || (little_num_online >= little_num_limit))
                            break;
                    }
                }
                set_bit(ACTION_RUSH_BOOST_LITTLE, (unsigned long *)&hps_ctxt.action);
            }
        }
    } 
    if (hps_ctxt.action)
        goto ALGO_END_WITH_ACTION;

    if (little_num_online < num_possible_cpus())
    {
        val = hps_ctxt.up_loads_history[hps_ctxt.up_loads_history_index];
        hps_ctxt.up_loads_history[hps_ctxt.up_loads_history_index] = hps_ctxt.cur_loads;
        hps_ctxt.up_loads_sum += hps_ctxt.cur_loads;
        hps_ctxt.up_loads_history_index = (hps_ctxt.up_loads_history_index + 1 == hps_ctxt.up_times) ? 0 : hps_ctxt.up_loads_history_index + 1;
        ++hps_ctxt.up_loads_count;
        
        if (hps_ctxt.up_loads_count > hps_ctxt.up_times)
        {
            BUG_ON(hps_ctxt.up_loads_sum < val);
            hps_ctxt.up_loads_sum -= val;
        }
        if (hps_ctxt.stats_dump_enabled)
            hps_ctxt_print_algo_stats_up(0);

        if (hps_ctxt.up_loads_count >= hps_ctxt.up_times)
        {
            if (hps_ctxt.up_loads_sum > hps_ctxt.up_threshold * hps_ctxt.up_times * little_num_online)
            {
                if (little_num_online < little_num_limit)
                {
                    for (cpu = hps_ctxt.little_cpu_id_min; cpu <= hps_ctxt.little_cpu_id_max; ++cpu)
                    {
                        if (!cpumask_test_cpu(cpu, &little_online_cpumask))
                        {
                            cpu_up(cpu);
                            cpumask_set_cpu(cpu, &little_online_cpumask);
                            ++little_num_online;
                            break;
                        }
                    }
                    set_bit(ACTION_UP_LITTLE, (unsigned long *)&hps_ctxt.action);
                }
            }
        } 
    } 
    if (hps_ctxt.action)
        goto ALGO_END_WITH_ACTION;

    if (little_num_online > 1)
    {
        val = hps_ctxt.down_loads_history[hps_ctxt.down_loads_history_index];
        hps_ctxt.down_loads_history[hps_ctxt.down_loads_history_index] = hps_ctxt.cur_loads;
        hps_ctxt.down_loads_sum += hps_ctxt.cur_loads;
        hps_ctxt.down_loads_history_index = (hps_ctxt.down_loads_history_index + 1 == hps_ctxt.down_times) ? 0 : hps_ctxt.down_loads_history_index + 1;
        ++hps_ctxt.down_loads_count;
        
        if (hps_ctxt.down_loads_count > hps_ctxt.down_times)
        {
            BUG_ON(hps_ctxt.down_loads_sum < val);
            hps_ctxt.down_loads_sum -= val;
        }
        if (hps_ctxt.stats_dump_enabled)
            hps_ctxt_print_algo_stats_down(0);

        if (hps_ctxt.down_loads_count >= hps_ctxt.down_times)
        {
            unsigned int down_threshold = hps_ctxt.down_threshold * hps_ctxt.down_times;

            val = little_num_online;
            while (hps_ctxt.down_loads_sum < down_threshold * (val - 1))
                --val;
            if(val < little_num_base)
            	val = little_num_base;
            val = little_num_online - val;

            if ((val) && (little_num_online > little_num_base))
            {
                for (cpu = hps_ctxt.little_cpu_id_max; cpu > hps_ctxt.little_cpu_id_min; --cpu)
                {
                    if (cpumask_test_cpu(cpu, &little_online_cpumask))
                    {
                        cpu_down(cpu);
                        cpumask_clear_cpu(cpu, &little_online_cpumask);
                        --little_num_online;
                        if (--val == 0 || (little_num_online <= little_num_base))
                            break;
                    }
                }
                set_bit(ACTION_DOWN_LITTLE, (unsigned long *)&hps_ctxt.action);
            }
        } 
    } 
    if (!hps_ctxt.action)
        goto ALGO_END_WO_ACTION;

ALGO_END_WITH_ACTION:
#ifdef CONFIG_HTC_PNPMGR
    hps_warn("(%04lx)(%u)action end(%u)(%u)(%u)(%u) (%u)(%u)(%u)(%u)(%u) (%u)(%u) (%u)(%u)(%u) (%u)(%u)(%u) (%u)(%u)(%u)(%u)(%u)\n",
        hps_ctxt.action, little_num_online,
        hps_ctxt.cur_loads, hps_ctxt.cur_tlp, hps_ctxt.cur_iowait, hps_ctxt.cur_nr_heavy_task,
        hps_ctxt.little_num_limit_thermal, hps_ctxt.little_num_limit_low_battery, hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.little_num_limit_power_serv, hps_ctxt.little_num_base_perf_serv,
        hps_ctxt.little_num_limit_pnpmgr, hps_ctxt.little_num_base_pnpmgr,
        hps_ctxt.up_loads_sum, hps_ctxt.up_loads_count, hps_ctxt.up_loads_history_index,
        hps_ctxt.down_loads_sum, hps_ctxt.down_loads_count, hps_ctxt.down_loads_history_index,
        hps_ctxt.rush_count, hps_ctxt.tlp_sum, hps_ctxt.tlp_count, hps_ctxt.tlp_history_index, hps_ctxt.tlp_avg);
#else
    hps_warn("(%04lx)(%u)action end(%u)(%u)(%u)(%u) (%u)(%u)(%u)(%u)(%u) (%u)(%u)(%u) (%u)(%u)(%u) (%u)(%u)(%u)(%u)(%u)\n",
        hps_ctxt.action, little_num_online,
        hps_ctxt.cur_loads, hps_ctxt.cur_tlp, hps_ctxt.cur_iowait, hps_ctxt.cur_nr_heavy_task, 
        hps_ctxt.little_num_limit_thermal, hps_ctxt.little_num_limit_low_battery, hps_ctxt.little_num_limit_ultra_power_saving, hps_ctxt.little_num_limit_power_serv, hps_ctxt.little_num_base_perf_serv, 
        hps_ctxt.up_loads_sum, hps_ctxt.up_loads_count, hps_ctxt.up_loads_history_index, 
        hps_ctxt.down_loads_sum, hps_ctxt.down_loads_count, hps_ctxt.down_loads_history_index, 
        hps_ctxt.rush_count, hps_ctxt.tlp_sum, hps_ctxt.tlp_count, hps_ctxt.tlp_history_index, hps_ctxt.tlp_avg);
#endif
    hps_ctxt_reset_stas_nolock();
ALGO_END_WO_ACTION:
    mutex_unlock(&hps_ctxt.lock);

    return;
}
