#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include <termios.h>
#include <pthread.h>
#include <string.h>

//#define REAL_TERMINAL_NAME "/dev/ttyC0Real"
//#define PROXY_TERMINAL_NAME "/dev/ttyC0" 

#define REAL_TERMINAL_NAME "/dev/ccci_fsReal"
#define PROXY_TERMINAL_NAME "/dev/ccci_fs" 
#define LOG_OUTPUT "/data/local/tmp/mitm_fs.log"
int realTerminalId;
FILE* readTrace = 0;

typedef struct mitm_param
{
	char marker[256];
	int threadId;
	int from;
	int to;
	
} mitm_param;

void* mitmThread(void *parameters)
{
	mitm_param* param;
	int to, from;
	char ps_buffer[1024];
	int ps_byteRead=0;
	
	param = (mitm_param*)parameters;
	to = param->to;
	from = param->from;
	
	printf("Hello, I'm Thread: %d.\n",param->threadId);
	sprintf(ps_buffer,"Thread %d started, reading from %d and writing in %d.\n",param->threadId,from,to);
	fwrite(ps_buffer, strlen(ps_buffer), 1, readTrace);
	
	while (1)
	{
		ps_byteRead = read(from, ps_buffer, sizeof(ps_buffer) );
		
		if (ps_byteRead <= 0)
			continue;
		
		fwrite(param->marker, strlen(param->marker), 1, readTrace);
		fwrite(ps_buffer, 1, ps_byteRead, readTrace);
		fwrite("\n",1,1,readTrace);
		fflush(readTrace);
		
		//Relay
		write(to, ps_buffer, ps_byteRead);
	}
	
	pthread_exit(NULL);
}


// Set the terminal to act as raw, also setup the speed.
void setupTerminalEnd(int terminalFDId,char* terminalName)
{
	struct termios  options;

	if (tcgetattr(terminalFDId, &options) == -1)
        printf("Error getting tty attributes %s's master - %s(%d).\n",terminalName, strerror(errno), errno);
	
	printf("Master input baud rate is %d\n", (int) cfgetispeed(&options));
    printf("Master output baud rate is %d\n", (int) cfgetospeed(&options));
	
	
	
	cfmakeraw(&options);
    options.c_cc[VMIN] = 1;
    options.c_cc[VTIME] = 10;
	
    // The baud rate, word length, and handshake options can be set as follows:
	
    //cfsetspeed(&options, B19200);    // Set 19200 baud
    cfsetspeed(&options, B115200);    // Set 115200 baud
    options.c_cflag |= (CS8);  // RTS flow control of input
	
	
    printf("Input baud rate changed to %d\n", (int) cfgetispeed(&options));
    printf("Output baud rate changed to %d\n", (int) cfgetospeed(&options));
	
    // Cause the new options to take effect immediately.
    if (tcsetattr(terminalFDId, TCSANOW, &options) == -1)
    {
        printf("Error setting tty attributes %s's master - %s(%d).\n", terminalName, strerror(errno), errno);
		
    }
}

int main(int argc, char** argv)
{
	char* pt_name;
	int pt_masterMITM;
	pthread_t threads[2];
	int threadError;
	int symlinkError;
    int renameError;
	
	mitm_param mitmWay1;
	mitm_param mitmWay2;

    //move the real terminal
    renameError = rename(PROXY_TERMINAL_NAME, REAL_TERMINAL_NAME);
    if (renameError < 0)
    {
        printf("Failed to move %s to %s: %s\n", PROXY_TERMINAL_NAME, REAL_TERMINAL_NAME, strerror(errno));
        return 0;
    }
    printf("Moved %s to %s\n", PROXY_TERMINAL_NAME, REAL_TERMINAL_NAME);
	
	realTerminalId = open(REAL_TERMINAL_NAME,O_RDWR );
	if (realTerminalId < 0)
	{
		printf("Unable to open %s: %s \n.",REAL_TERMINAL_NAME,strerror(errno ));
		return 0;
	}
	
	printf("Opened %s, fd=%d",REAL_TERMINAL_NAME,realTerminalId);
	
	pt_masterMITM = open("/dev/ptmx",O_RDWR);
	
	pt_name = ptsname(pt_masterMITM);
	printf("Slave end name is '%s'\n",pt_name);
	grantpt(pt_masterMITM);
	unlockpt(pt_masterMITM);
	
	
	printf("Softlinking %s to %s.\n",pt_name,PROXY_TERMINAL_NAME);
	symlinkError = symlink(pt_name, PROXY_TERMINAL_NAME);
	if (symlinkError < 0)
	{
		printf("Could not create symlink from %s to %s: %s\n",pt_name,PROXY_TERMINAL_NAME,strerror(symlinkError));
		return 0;
	}
	
	symlinkError = chmod(PROXY_TERMINAL_NAME, S_IRWXU | S_IRWXG | S_IRWXO);
	if (symlinkError < 0)
	{
		printf("Could not chmod 777 %s : %s\n",PROXY_TERMINAL_NAME,strerror(symlinkError));
		return 0;
	}
	
	
	//Important to make the pseudo-terminal raw.
	setupTerminalEnd(pt_masterMITM,"MITM master");
	
	
	
	// All android <--> baseband will be traced here.	
	readTrace = fopen(LOG_OUTPUT, "wt");
	
	// Thread multiple parameters are passed via a struct mitm_param
	mitmWay1.from = pt_masterMITM;
	mitmWay1.to = realTerminalId;	
	mitmWay1.threadId = 0;
	strcpy(mitmWay1.marker,"[Android send] :");
	printf("Creating thread 1.\n");
	threadError = pthread_create(&threads[0], NULL, mitmThread, (void *)&mitmWay1);
	if (threadError)
		printf("Could not create thread errorid=(%d): %s\n",threadError,strerror(threadError));
	
	// The other channel is not using a thread, we run it in the main process
	mitmWay2.from = realTerminalId;
	mitmWay2.to = pt_masterMITM;	
	mitmWay2.threadId =1;
	strcpy(mitmWay2.marker,"[Android recv] :");
	mitmThread(&mitmWay2);
	
	return 1;
}
