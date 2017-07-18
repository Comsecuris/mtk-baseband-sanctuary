#ifndef AFL_WRAPPER_HEADER
#define AFL_WRAPPER_HEADER

#define MAX_AT_RESPONSE (8 * 1024)
typedef void (*ATUnsolHandler)(const char *s, const char *sms_pdu, void* p_channel);

typedef enum {
    NO_RESULT,   /* no intermediate response expected */
    NUMERIC,     /* a single intermediate response starting with a 0-9 */
    SINGLELINE,  /* a single intermediate response starting with a prefix */
    MULTILINE,    /* multiple line intermediate response
                    starting with a prefix */
    /* atci start */
    RAW
    /* atci end */
} ATCommandType;

typedef enum {
    RIL_URC,
    RIL_CMD_1,
    RIL_CMD_2,
    RIL_CMD_3,
    RIL_CMD_4, /* ALPS00324111 split data and nw command channel */
    RIL_PPPDATA = RIL_CMD_4,
    RIL_ATCI,
    RIL_SUPPORT_CHANNELS
} RILChannelId;

/** a singly-lined list of intermediate responses */
typedef struct ATLine  {
    struct ATLine *p_next;
    char *line;
} ATLine;

/** Free this with at_response_free() */
typedef struct {
    int success;              /* true if final response indicates
                                    success (eg "OK") */
    char *finalResponse;      /* eg OK, ERROR */
    ATLine  *p_intermediates; /* any intermediate responses */
} ATResponse;


typedef struct RILChannelCtx {
    const char* myName;
    RILChannelId id;
    pthread_t tid_reader;
    pthread_t tid_myProxy;
    int fd;
    ATUnsolHandler unsolHandler;
    int readCount;
    
    pthread_mutex_t commandmutex;
    pthread_cond_t commandcond;
    
    ATCommandType type;
    const char *responsePrefix;
    const char *smsPDU;
    ATResponse *p_response;
    
    int readerClosed;
    
    char *ATBufferCur;
    char ATBuffer[MAX_AT_RESPONSE+1];
    int pendingRequest;
} RILChannelCtx;
#endif
