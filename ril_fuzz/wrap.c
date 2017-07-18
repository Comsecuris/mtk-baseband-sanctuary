#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/syscall.h>

#include "wrap.h" 

typedef void (*onATEvent)(RILChannelCtx *p_channel);

void onEvent(RILChannelCtx* p_channel)
{
    printf("[INFO] Wrapper event happened, passing\n");
}

int main(int argc, char** argv)
{
    RILChannelCtx channel;
    void (*at_on_timeout)(onATEvent);
    void (*at_on_close)(onATEvent);
    void * handle;
    char * error;
    void *libBase;
    void (*readerLoop)(void*);

    memset(&channel, 0, sizeof(channel));
    channel.fd = STDIN_FILENO;
    channel.ATBufferCur = channel.ATBuffer;
    channel.myName = "RIL_CMD_READER_1";
    channel.id = 1;

    printf("[INFO] Loading Shared lib\n");
    //open shared lib + get pointers
    handle  = dlopen("mtk-ril.so", RTLD_NOW);
    if (!handle) 
    {
        printf("[ERROR] Failed to load library: %s\n", dlerror());
        exit(0);
    }

    at_on_timeout = dlsym(handle, "at_set_on_timeout");
    if ((error = dlerror()) != NULL)
    {
        printf("[ERROR] Failed to load on_time: %s\n", dlerror());
        exit(0);

    }

    at_on_close = dlsym(handle, "at_set_on_reader_closed");
    if ((error = dlerror()) != NULL)
    {
        printf("[ERROR] Failed to load on_close: %s\n", dlerror());
        exit(0);

    }
    printf("[INFO] Calling event handler setup\n");
    // do set on_reader_closed
    (*at_on_close)(onEvent);
    // set on_timeout
    (*at_on_timeout)(onEvent);

    libBase = at_on_close - 0x0002fb1c;

    channel.unsolHandler = (libBase + 0x10AD0); //onUnsolicited
    channel.readerClosed = 0;
    channel.responsePrefix = NULL;
    channel.smsPDU = NULL;
    channel.p_response = NULL;
    channel.tid_reader = syscall(SYS_gettid);

    // call reader loop
    printf("[INFO] Starting the event handler\n");
    readerLoop = (libBase + 0x2f020);
    (*readerLoop)((void*)&channel);

}
