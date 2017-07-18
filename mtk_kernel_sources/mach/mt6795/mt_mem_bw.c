#include <linux/device.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include "mach/mt_emi_bm.h"
#include "mach/mt_dcm.h"
#include "mach/mt_mem_bw.h"
#include <asm/div64.h>  

unsigned long long last_time_ns;
unsigned long long LastWordAllCount=0;
unsigned long long get_mem_bw(void)
{
    unsigned long long throughput;
    unsigned long long WordAllCount;
    unsigned long long current_time_ns, time_period_ns;
    int count, value;
    int emi_dcm_disable = BM_GetEmiDcm();

#if DISABLE_FLIPPER_FUNC    
return 0;
#endif

    
    current_time_ns = sched_clock();
    time_period_ns = current_time_ns - last_time_ns;
    
    
    
    BM_SetEmiDcm(0xff); 
        
    BM_Pause();
    WordAllCount = BM_GetWordAllCount();
    if(WordAllCount == 0) 
        LastWordAllCount = 0;

    WordAllCount -= LastWordAllCount;
    throughput = (WordAllCount * 8 * 1000);
    do_div(throughput,time_period_ns);
    

    
    BM_Enable(0);
    
    value = BM_GetWordAllCount();
    count = 100;
    if((value != 0) && (value > 0xB0000000))
    {  
      do
      {
        if((value = BM_GetWordAllCount()) != 0)
        {
          count--;
          BM_Enable(1);
          BM_Enable(0);
        }
        else
        {
          break;
        }
      }while(count > 0);      
    }
    LastWordAllCount = value;
    
    
   
    
    BM_Enable(1);
    last_time_ns = sched_clock();
    
    
    BM_SetEmiDcm(emi_dcm_disable); 
    
    
    
    return throughput;
}

static int __init mon_kernel_init(void)
{
    
    BM_Init();
        	
    BM_SetReadWriteType(BM_BOTH_READ_WRITE);
    BM_SetMonitorCounter(1, BM_MASTER_MM1 | BM_MASTER_MM1, BM_TRANS_TYPE_4BEAT | BM_TRANS_TYPE_8Byte | BM_TRANS_TYPE_BURST_WRAP);
    BM_SetMonitorCounter(2, BM_MASTER_AP_MCU1 | BM_MASTER_AP_MCU2, BM_TRANS_TYPE_4BEAT | BM_TRANS_TYPE_8Byte | BM_TRANS_TYPE_BURST_WRAP);
    BM_SetMonitorCounter(3, BM_MASTER_MD_MCU | BM_MASTER_2G_3G_MDDMA, BM_TRANS_TYPE_4BEAT | BM_TRANS_TYPE_8Byte | BM_TRANS_TYPE_BURST_WRAP);
    BM_SetMonitorCounter(4, BM_MASTER_GPU1 | BM_MASTER_GPU1, BM_TRANS_TYPE_4BEAT | BM_TRANS_TYPE_8Byte | BM_TRANS_TYPE_BURST_WRAP);

    BM_SetLatencyCounter();

     
    BM_Enable(0);
     
    BM_Enable(1);
    last_time_ns = sched_clock();
      
    return 0;
}

static void __exit mon_kernel_exit(void)
{
    return;
}

module_init(mon_kernel_init);
module_exit(mon_kernel_exit);

