

#ifndef ___HVC_UI_H___
#define ___HVC_UI_H___

/******************************
 * define
 */

#define GRID_ORDER_PROFILE      0
#define GRID_ORDER_LEVEL        1
#define GRID_ORDER_TIER         2
#define GRID_ORDER_RESOLUTION   3
#define GRID_ORDER_FRAMERATE    4
#define GRID_ORDER_BITRATE      5

#define GRID_ORDER_BITDEPTH     6
#define GRID_ORDER_CHROMA       7
#define GRID_ORDER_PIX_FMT      8

#define GRID_ORDER_GOP          9
#define GRID_ORDER_GOP_SIZE     10
#define GRID_ORDER_IDR_INTERVAL 11
#define GRID_ORDER_BNUM         12

#define GRID_ORDER_OPEN         13
#define GRID_ORDER_ENCODE       14
#define GRID_ORDER_BAR          14


#define GET_PTS_IN_MS(eCh, frame_order)    ((frame_order) * 1000 / tApiHvcInitParam[eCh].eTargetFrameRate)


#define FMB_TIMESTAMP_FORMAT        "%H%M%S"
#define FMB_ES_FILE_NAME_FORMAT     "es_%s.265"


#define LOG(fmt, ...) \
    {   \
        fprintf(ui_logging, "LOG: ");              \
        fprintf(ui_logging, fmt, ##__VA_ARGS__);   \
        fflush(ui_logging);                        \
    }
    

typedef struct
{
    API_HVC_BOARD_E board_num;
    API_HVC_CHN_E   channel;
    uint32_t        total_frame;
    uint32_t        poped_frame;
} POP_ES_CALLBACK_PARAM_T;

typedef struct
{
    API_HVC_CHN_E eCh;
} ENCODE_CALLBACK_PARAM_T; 

typedef struct
{
    API_HVC_CHN_E eCh;
    GtkWidget *window;
} OPEN_CALLBACK_PARAM_T;


#endif

