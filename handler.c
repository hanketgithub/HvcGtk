#include <gtk/gtk.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <libgen.h>

#include "libhvc_venc/inc/HVC_types.h"
#include "HvcGtk.h"

static API_HVC_IMG_T img[API_HVC_CHN_MAX];

void handler_profile(GtkWidget *widget, gpointer *data)
{    
    GSList *list; 
    GtkToggleButton *button = NULL;
    API_HVC_CHN_E eCh = (API_HVC_CHN_E) *data;
    
    list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(ProfileMainRadioButton[eCh]));
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const gchar *val = gtk_button_get_label(GTK_BUTTON(button));
    
    if (strcmp(val, PROFILE_MAIN_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eProfile = API_HVC_HEVC_MAIN_PROFILE;
    }
    else if (strcmp(val, PROFILE_MAIN10_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eProfile = API_HVC_HEVC_MAIN10_PROFILE;
    }

    LOG("%s: %s selected\n", __FUNCTION__, val);
}

void handler_level(GtkWidget *widget, gpointer *data)
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    API_HVC_CHN_E eCh = (API_HVC_CHN_E) *data;
    
    list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(Lv40RadioButton[eCh]));
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const gchar *val = gtk_button_get_label(GTK_BUTTON(button));
    
    if (strcmp(val, LV_40_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eLevel = API_HVC_HEVC_LEVEL_40;
    }
    else if (strcmp(val, LV_41_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eLevel = API_HVC_HEVC_LEVEL_41;
    }
    else if (strcmp(val, LV_50_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eLevel = API_HVC_HEVC_LEVEL_50;
    }
    else if (strcmp(val, LV_51_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eLevel = API_HVC_HEVC_LEVEL_51;
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

void handler_tier(GtkWidget *widget, gpointer *data)
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    API_HVC_CHN_E eCh = (API_HVC_CHN_E) *data;
    
    list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(TierMainRadioButton[eCh]));
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const gchar *val = gtk_button_get_label(GTK_BUTTON(button));
    
    if (strcmp(val, TIER_MAIN_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eTier = API_HVC_HEVC_MAIN_TIER;
    }
    else if (strcmp(val, TIER_HIGH_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eTier = API_HVC_HEVC_HIGH_TIER;
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

void handler_res(GtkWidget *widget, gpointer *data)
{
    gchar *val = NULL;
    API_HVC_CHN_E eCh = (API_HVC_CHN_E) *data;
    
    val = gtk_combo_box_text_get_active_text(ResCombo[eCh]);

    if (strcmp(val, RESOLUTION_DCI_4K_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eResolution = API_HVC_RESOLUTION_4096x2160;
        tApiHvcInitParam[eCh].eMemoryAllocMode = API_HVC_MEMORY_ALLOC_MODE_1CH_4K2K;
    }
    else if (strcmp(val, RESOLUTION_4K_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eResolution = API_HVC_RESOLUTION_3840x2160;
        tApiHvcInitParam[eCh].eMemoryAllocMode = API_HVC_MEMORY_ALLOC_MODE_1CH_4K2K;
    }
    else if (strcmp(val, RESOLUTION_2K_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eResolution = API_HVC_RESOLUTION_1920x1080;
        tApiHvcInitParam[eCh].eMemoryAllocMode = API_HVC_MEMORY_ALLOC_MODE_4CH_1080P;
    }
    else if (strcmp(val, RESOLUTION_HD_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eResolution = API_HVC_RESOLUTION_1280x720;
        tApiHvcInitParam[eCh].eMemoryAllocMode = API_HVC_MEMORY_ALLOC_MODE_8CH_720P;
    }
    else if (strcmp(val, RESOLUTION_SD_576_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eResolution = API_HVC_RESOLUTION_720x576;
        tApiHvcInitParam[eCh].eMemoryAllocMode = API_HVC_MEMORY_ALLOC_MODE_16CH_SD;
    }
    else if (strcmp(val, RESOLUTION_SD_480_TEXT) == 0)
    {
        tApiHvcInitParam[eCh].eResolution = API_HVC_RESOLUTION_720x480;
        tApiHvcInitParam[eCh].eMemoryAllocMode = API_HVC_MEMORY_ALLOC_MODE_16CH_SD;
    }
    else
    {
        LOG("%s: Invalid resolution!\n", __FUNCTION__);
    }
        
    LOG("%s: %s selected\n", __FUNCTION__, val);
}


void handler_framerate(GtkWidget *widget, gpointer *data)
{
    gchar *val = NULL;
    API_HVC_CHN_E eCh = (API_HVC_CHN_E) *data;

    val = gtk_combo_box_text_get_active_text(FpsCombo[eCh]);
    
    if (strcmp(val, "24") == 0)
    {
        tApiHvcInitParam[eCh].eTargetFrameRate = API_HVC_FPS_24;
    }
    else if (strcmp(val, "25") == 0)
    {
        tApiHvcInitParam[eCh].eTargetFrameRate = API_HVC_FPS_25;
    }
    else if (strcmp(val, "29.97") == 0)
    {
        tApiHvcInitParam[eCh].eTargetFrameRate = API_HVC_FPS_29_97;
    }
    else if (strcmp(val, "30") == 0)
    {
        tApiHvcInitParam[eCh].eTargetFrameRate = API_HVC_FPS_30;
    }
    else if (strcmp(val, "50") == 0)
    {
        tApiHvcInitParam[eCh].eTargetFrameRate = API_HVC_FPS_50;
    }
    else if (strcmp(val, "59.94") == 0)
    {
        tApiHvcInitParam[eCh].eTargetFrameRate = API_HVC_FPS_59_94;
    }
    else if (strcmp(val, "60") == 0)
    {
        tApiHvcInitParam[eCh].eTargetFrameRate = API_HVC_FPS_60;
    }

    LOG("%s: %s selected\n", __FUNCTION__, val);
}

void handler_bitdepth(GtkWidget *widget, gpointer *data)
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    API_HVC_CHN_E eCh = (API_HVC_CHN_E) *data;
    
    list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(Bitdepth8RadioButton[eCh]));
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const gchar *val = gtk_button_get_label(GTK_BUTTON(button));
    
    if (strcmp(val, "8") == 0)
    {
        tApiHvcInitParam[eCh].eBitDepth = API_HVC_BIT_DEPTH_8;
    }
    else if (strcmp(val, "10") == 0)
    {
        tApiHvcInitParam[eCh].eBitDepth = API_HVC_BIT_DEPTH_10;
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

void handler_chroma(GtkWidget *widget, gpointer *data)
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    API_HVC_CHN_E eCh = (API_HVC_CHN_E) *data;
    
    list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(Chroma420RadioButton[eCh]));
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const gchar *val = gtk_button_get_label(GTK_BUTTON(button));
    
    if (strcmp(val, "420") == 0)
    {
        tApiHvcInitParam[eCh].eChromaFmt = API_HVC_CHROMA_FORMAT_420;
    }
    else if (strcmp(val, "422") == 0)
    {
        tApiHvcInitParam[eCh].eChromaFmt = API_HVC_CHROMA_FORMAT_422;
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

void handler_pixfmt(GtkWidget *widget, gpointer *data)
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    API_HVC_CHN_E eCh = (API_HVC_CHN_E) *data;
    API_HVC_IMG_T *pImg = &img[eCh];
    
    list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(PixFmtIntRadioButton[eCh]));
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const gchar *val = gtk_button_get_label(GTK_BUTTON(button));
    
    if (strcmp(val, PIXEL_FMT_INTERLEAVE_TEXT) == 0)
    {
        switch (tApiHvcInitParam[eCh].eChromaFmt)
        {
        case API_HVC_CHROMA_FORMAT_420:
        {
            pImg->eFormat = API_HVC_IMAGE_FORMAT_NV12;
            break;
        }
        case API_HVC_CHROMA_FORMAT_422:
        {
            pImg->eFormat = API_HVC_IMAGE_FORMAT_NV16;
            break;
        }
        }
    }
    else if (strcmp(val, PIXEL_FMT_PLANAR_TEXT) == 0)
    {
        pImg->eFormat = API_HVC_IMAGE_FORMAT_YUV420;
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

void ui_process_coded_frame(API_HVC_HEVC_CODED_PICT_T *p_coded_pict, void *args)
{
    POP_ES_CALLBACK_PARAM_T *p_callback_param;
    API_HVC_BOARD_E eBoard;
    API_HVC_CHN_E eCh;

    p_callback_param = (POP_ES_CALLBACK_PARAM_T *) args;

    eBoard = p_callback_param->board_num;
    eCh = p_callback_param->channel;
    
    char msg[512];
    char *p;

    p = msg;

    p += sprintf(p, "%s: board=%d, ch=%d, pts=%lu, type=%d ",
        __FUNCTION__,
        eBoard, eCh,
        p_coded_pict->pts,
        p_coded_pict->eFrameType);
        
    uint32_t i;
    for (i = 0; i < p_coded_pict->u32NalNum; i++)
    {
        p += sprintf(p, "[NAL%u len=%u, type=%u]", 
                        i,
                        p_coded_pict->tNalInfo[i].u32Length,
                        p_coded_pict->tNalInfo[i].eNalType);
  
        if (fd_w[eCh])
        {
            write(fd_w[eCh], p_coded_pict->tNalInfo[i].pu8Addr, p_coded_pict->tNalInfo[i].u32Length);
        }
    }
    LOG("%s\n", msg);

    p_callback_param->poped_frame++;

    gdouble fraction;

    fraction = (double) p_callback_param->poped_frame / (double) p_callback_param->total_frame;

    //LOG("%f %d %d\n", fraction, poped_frame, total_frame);

    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ProgressBar[eCh]), fraction);
}


void handler_gop(GtkWidget *widget, gpointer *data)
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    API_HVC_CHN_E eCh = (API_HVC_CHN_E) *data;
    
    list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(GopIbRadioButton[eCh]));
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const gchar *val = gtk_button_get_label(GTK_BUTTON(button));

    if (strcmp(val, "IP") == 0)
    {
        tApiHvcInitParam[eCh].eGopType = API_HVC_GOP_IP;
        gtk_widget_set_sensitive(GTK_WIDGET(BNumScale[eCh]), FALSE);
    }
    else if (strcmp(val, "IB") == 0)
    {
        tApiHvcInitParam[eCh].eGopType = API_HVC_GOP_IB;
        gtk_widget_set_sensitive(GTK_WIDGET(BNumScale[eCh]), TRUE);
    }
    else if (strcmp(val, "IPB") == 0)
    {
        tApiHvcInitParam[eCh].eGopType = API_HVC_GOP_IPB;
        gtk_widget_set_sensitive(GTK_WIDGET(BNumScale[eCh]), TRUE);
    }
    else if (strcmp(val, "I") == 0)
    {
        tApiHvcInitParam[eCh].eGopType       = API_HVC_GOP_I;
        tApiHvcInitParam[eCh].eGopSize       = API_HVC_GOP_SIZE_1;
        tApiHvcInitParam[eCh].eIDRFrameNum   = API_HVC_IDR_FRAME_ALL;
        tApiHvcInitParam[eCh].eBFrameNum     = API_HVC_B_FRAME_NONE;
        gtk_widget_set_sensitive(GTK_WIDGET(BNumScale[eCh]), FALSE); 
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

static size_t calculate_vraw_enqueue_data_size(API_HVC_INIT_PARAM_T *p_init_param)
{
    uint32_t hsize_va;
    uint32_t vsize_va;
    uint32_t bit_depth;
    uint32_t y_data_size;
    uint32_t c_data_size;
    uint8_t c_pixel_per_sample;
    
    // set bit-depth factor
    switch (p_init_param->eBitDepth)
    {
        case API_HVC_BIT_DEPTH_8:
        {
            bit_depth = 8;
            break;
        }
        case API_HVC_BIT_DEPTH_10:
        {
            bit_depth = 10;
            break;
        }
        default:
        {
            bit_depth = 8;
            break;
        }
    }

    // set chrom factor
    switch (p_init_param->eChromaFmt)
    {
        case API_HVC_CHROMA_FORMAT_420:
        {
            c_pixel_per_sample = 4;
            break;
        }
        case API_HVC_CHROMA_FORMAT_422:
        {
            c_pixel_per_sample = 2;
            break;
        }
        default:
        {
            c_pixel_per_sample = 4;
            break;
        }
    }

    switch (p_init_param->eResolution)
    {
        case API_HVC_RESOLUTION_720x480:
        {
            hsize_va = 720;
            vsize_va = 480;
            break;
        }
        case API_HVC_RESOLUTION_720x576:
        {
            hsize_va = 720;
            vsize_va = 576;
            break;
        }
        case API_HVC_RESOLUTION_1280x720:
        {
            hsize_va = 1280;
            vsize_va = 720;
            break;
        }
        case API_HVC_RESOLUTION_1920x1080:
        {
            hsize_va = 1920;
            vsize_va = 1080;
            break;
        }
        case API_HVC_RESOLUTION_3840x2160:
        {
            hsize_va = 3840;
            vsize_va = 2160;
            break;
        }
        case API_HVC_RESOLUTION_4096x2160:
        {
            hsize_va = 4096;
            vsize_va = 2160;
            break;
        }
        default:
        {
            hsize_va = 3840;
            vsize_va = 2160;            
            break;
        }
    }

    y_data_size = ( ( hsize_va * vsize_va ) * bit_depth ) / 8;

    c_data_size = y_data_size / c_pixel_per_sample;

    return y_data_size + c_data_size + c_data_size;
}


static void make_timestamp(char * timestamp_p, size_t size)
{
    time_t now;
    struct tm *now_tm_p;

    now = time ( NULL );

    now_tm_p = localtime ( &now );

    strftime ( timestamp_p, size, FMB_TIMESTAMP_FORMAT, now_tm_p );
}


static void make_output_file_name
(
    const char *timestamp,
    char *es_file_name_p,
    size_t length,
    char *path
)
{
    char *bname = basename(path);
    char *cp = strchr(bname, '.');
    char output[255];

    memset(output, 0, sizeof(output));
    strncpy(output, bname, cp - bname);

    snprintf(es_file_name_p, (length - 1), GTK_ES_FILE_NAME_FORMAT, output, timestamp);
}


static void *encode_thr_fn(void *data)
{
    ENCODE_CALLBACK_PARAM_T *param = (ENCODE_CALLBACK_PARAM_T *) data;
    API_HVC_CHN_E eCh = param->eCh;
    char *str_profile = (tApiHvcInitParam[eCh].eProfile == API_HVC_HEVC_MAIN_PROFILE) ? "Main" : "Main10";

    LOG("%p Channel: %d\n", param, eCh);
    LOG("Profile: %s\n", str_profile);
    
    char *str_level;
    
    struct timeval tv1, tv2, res;
    
    switch (tApiHvcInitParam[eCh].eLevel)
    {
        case API_HVC_HEVC_LEVEL_40:
        {
            str_level = "L4.0";
            break;
        }       
        case API_HVC_HEVC_LEVEL_41:
        {
            str_level = "L4.1";
            break;
        }        
        case API_HVC_HEVC_LEVEL_50:
        {
            str_level = "L5.0";
            break;
        }        
        case API_HVC_HEVC_LEVEL_51:
        {
            str_level = "L5.1";
            break;
        }        
        default:
        {
            break;
        }
    }
    
    LOG("Level: %s\n", str_level);

    
    char *str_tier = (tApiHvcInitParam[eCh].eTier == API_HVC_HEVC_MAIN_TIER) ? "Main Tier" : "High Tier";
    
    LOG("Tier: %s\n", str_tier);
    

    char *str_res = "Unknown";
    
    switch (tApiHvcInitParam[eCh].eResolution)
    {
        case API_HVC_RESOLUTION_4096x2160:
        {
            str_res = RESOLUTION_DCI_4K_TEXT;

            tApiHvcInitParam[eCh].tCrop.u32CropLeft      = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropLeft      = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropTop       = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropBottom    = 0;
            
            break;
        }
        case API_HVC_RESOLUTION_3840x2160:
        {
            str_res = RESOLUTION_4K_TEXT;

            tApiHvcInitParam[eCh].tCrop.u32CropLeft      = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropLeft      = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropTop       = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropBottom    = 0;
            
            break;
        }        
        case API_HVC_RESOLUTION_1920x1080:
        {
            str_res = RESOLUTION_2K_TEXT;

            tApiHvcInitParam[eCh].tCrop.u32CropLeft      = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropLeft      = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropTop       = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropBottom    = 8;
            
            break;
        }        
        case API_HVC_RESOLUTION_1280x720:
        {
            str_res = RESOLUTION_HD_TEXT;

            tApiHvcInitParam[eCh].tCrop.u32CropLeft      = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropLeft      = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropTop       = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropBottom    = 0;
            
            break;
        }        
        case API_HVC_RESOLUTION_720x576:
        {
            str_res = RESOLUTION_SD_576_TEXT;
            
            tApiHvcInitParam[eCh].eAspectRatioIdc = API_HVC_HEVC_ASPECT_RATIO_IDC_4;

            tApiHvcInitParam[eCh].tCrop.u32CropLeft      = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropLeft      = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropTop       = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropBottom    = 0;
            
            break;
        }   
        case API_HVC_RESOLUTION_720x480:
        {
            str_res = RESOLUTION_SD_480_TEXT;

            tApiHvcInitParam[eCh].eAspectRatioIdc = API_HVC_HEVC_ASPECT_RATIO_IDC_5;
            
            tApiHvcInitParam[eCh].tCrop.u32CropLeft      = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropLeft      = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropTop       = 0;
            tApiHvcInitParam[eCh].tCrop.u32CropBottom    = 0;
            
            break;
        }  
        default:
        {
            break;
        }
    }
    
    LOG("Resolution: %s\n", str_res);

    char *str_framerate = "Unknown";
    
    switch (tApiHvcInitParam[eCh].eTargetFrameRate)
    {
        case API_HVC_FPS_24:
        {
            str_framerate = "24p";
            break;
        }        
        case API_HVC_FPS_25:
        {
            str_framerate = "25p";
            break;
        } 
        case API_HVC_FPS_29_97:
        {
            str_framerate = "29.97p";
            break;
        } 
        case API_HVC_FPS_30:
        {
            str_framerate = "30p";
            break;
        }
        case API_HVC_FPS_50:
        {
            str_framerate = "50p";
            break;
        }        
        case API_HVC_FPS_59_94:
        {
            str_framerate = "59.94p";
            break;
        }
        case API_HVC_FPS_60:
        {
            str_framerate = "60p";
            break;
        }        
        default:
        {
            break;
        }
    }
    
    LOG("Framerate: %s\n", str_framerate);
    
    
    guint bitrate_val;

    bitrate_val = gtk_range_get_value(GTK_RANGE(Bitrate[eCh]));
    
    LOG("Bitrate %d kbps\n", bitrate_val);
    
    tApiHvcInitParam[eCh].u32Bitrate = bitrate_val;


    char *str_bitdepth = "Unknown";
    
    switch (tApiHvcInitParam[eCh].eBitDepth)
    {
        case API_HVC_BIT_DEPTH_8:
        {
            str_bitdepth = "8";
            break;
        }        
        case API_HVC_BIT_DEPTH_10:
        {
            str_bitdepth = "10";
            break;
        }
        default:
        {
            break;
        }
    }
    
    LOG("bit depth: %s\n", str_bitdepth);
    
    
    char *str_chroma = (tApiHvcInitParam[eCh].eChromaFmt == API_HVC_CHROMA_FORMAT_420) ? "420" : "422";
    
    LOG("Chroma: %s\n", str_chroma);

    {
        GSList *list; 
        GtkToggleButton *button = NULL;
        API_HVC_IMG_T *pImg = &img[eCh];
        
        list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(PixFmtIntRadioButton[eCh]));
        
        while (list) // As long as we didn't reach the end of the group.
        {
            button = list->data;    // Get one of the buttons in the group.
            list = list->next;      // Next time we're going to check this one.

            if (gtk_toggle_button_get_active(button))
            {
                break;
            }
        }
        
        const gchar *val = gtk_button_get_label(GTK_BUTTON(button));
        
        if (strcmp(val, PIXEL_FMT_INTERLEAVE_TEXT) == 0)
        {
            switch (tApiHvcInitParam[eCh].eChromaFmt)
            {
                case API_HVC_CHROMA_FORMAT_422:
                {
                    pImg->eFormat = API_HVC_IMAGE_FORMAT_NV16;
                    break;
                }
                case API_HVC_CHROMA_FORMAT_420:
                default:
                {
                    pImg->eFormat = API_HVC_IMAGE_FORMAT_NV12;
                    break;
                }
            }
        }
        else if (strcmp(val, PIXEL_FMT_PLANAR_TEXT) == 0)
        {
            pImg->eFormat = API_HVC_IMAGE_FORMAT_YUV420;
        }
        
        LOG("%s: %s selected\n", __FUNCTION__, val);
    }
    
    char *str_gop = "Unknown";

    switch (tApiHvcInitParam[eCh].eGopType)
    {
        case API_HVC_GOP_I:
        {
            str_gop = "I";
            break;
        }
        case API_HVC_GOP_IP:
        {
            str_gop = "IP";
            break;
        }
        case API_HVC_GOP_IB:
        {
            str_gop = "IB";
            break;
        }
        case API_HVC_GOP_IPB:
        {
            str_gop = "IPB";
            break;
        }
        default:
        {
            break;
        }
    }
    
    LOG("GOP: %s\n", str_gop);

    if (tApiHvcInitParam[eCh].eGopType != API_HVC_GOP_I)
    {
        tApiHvcInitParam[eCh].eGopSize = atoi(gtk_entry_get_text(GTK_ENTRY(GopSizeEntry[eCh])));
    }

    LOG("GOP size=%d\n", tApiHvcInitParam[eCh].eGopSize);

    if (tApiHvcInitParam[eCh].eGopType != API_HVC_GOP_I)
    {
        tApiHvcInitParam[eCh].eIDRFrameNum = atoi(gtk_entry_get_text(GTK_ENTRY(IdrIntervalEntry[eCh])));
    }

    LOG("IDR interval=%d\n", tApiHvcInitParam[eCh].eIDRFrameNum);
    

    if ((tApiHvcInitParam[eCh].eGopType == API_HVC_GOP_IB)
       || (tApiHvcInitParam[eCh].eGopType == API_HVC_GOP_IPB))
    {
        guint refnum;
    
        refnum = gtk_range_get_value(GTK_RANGE(BNumScale[eCh]));
        
        tApiHvcInitParam[eCh].eBFrameNum = (API_HVC_B_FRAME_NUM_E) refnum;

        LOG("B ref#=%u\n", refnum);
    }

    tApiHvcInitParam[eCh].tCoding.bDisableAMP = true;
    

    API_HVC_BOARD_E eBoard = API_HVC_BOARD_1;

    eCh = param->eCh;
    
    gettimeofday(&tv1, NULL);
    if (HVC_ENC_Init(eBoard, eCh, &tApiHvcInitParam[eCh]))
    {
        sprintf(err_msg, "%s line %d failed!", __FILE__, __LINE__);

        goto callback_encode_ret;
    }  
    LOG("HVC_ENC_Init success!\n");


    tPopEsArgs[eBoard][eCh].board_num = eBoard;
    tPopEsArgs[eBoard][eCh].channel   = eCh;
    if (HVC_ENC_RegisterCallback
        (
            eBoard,
            eCh,
            ui_process_coded_frame,
            (void *) &tPopEsArgs[eBoard][eCh]
       ))
    {
        sprintf(err_msg, "%s line %d failed!", __FILE__, __LINE__);

        goto callback_encode_ret;
    }


    if (HVC_ENC_Start(eBoard, eCh))
    {
        sprintf(err_msg, "%s line %d failed!", __FILE__, __LINE__);

        goto callback_encode_ret;
    }

    LOG("HVC_ENC_Start success!\n");

    char es_file_name[FILENAME_MAX];
    char timestamp[15];

    make_timestamp(timestamp, sizeof(timestamp));
    make_output_file_name(timestamp, es_file_name, FILENAME_MAX, FilenameRawYUV[eCh]);

    fd_r[eCh]  = open(FilenameRawYUV[eCh], O_RDONLY);
    fd_w[eCh]  = open(es_file_name, 
                    O_WRONLY | O_CREAT,
                    S_IRWXU);
                 
    uint8_t *vraw_data_buf_p = NULL;
    uint32_t frame_sz = 0;
    struct stat file_stat;
    int remain_frame = 0;

    fstat(fd_r[eCh], &file_stat);

    frame_sz = calculate_vraw_enqueue_data_size(&tApiHvcInitParam[eCh]);
    remain_frame = ((uint64_t) file_stat.st_size / frame_sz);
    tPopEsArgs[eBoard][eCh].total_frame = remain_frame;
    tPopEsArgs[eBoard][eCh].poped_frame = 0;
    
    vraw_data_buf_p = malloc(frame_sz);

    API_HVC_IMG_T *pImg = &img[eCh];

    while (remain_frame > 0)
    {        
        read(fd_r[eCh], vraw_data_buf_p, frame_sz);

        remain_frame--;

        pImg->pu8Addr     = vraw_data_buf_p;
        pImg->u32Size     = frame_sz;
        pImg->pts         = GET_PTS_IN_MS(eCh, tPopEsArgs[eBoard][eCh].total_frame - remain_frame);
        pImg->bLastFrame  = (remain_frame == 0) ? true : false;

        if (HVC_ENC_PushImage(eBoard, eCh, pImg))
        {
            sprintf(err_msg, "Error: %s PushImage failed!\n", __FILE__);

            goto callback_encode_ret;
        }
    }

    LOG("Encode done...\n");

    // try stop
    while (HVC_ENC_Stop(eBoard, eCh))
    {
        usleep(1);
    }
    LOG("\n stop complete!\n");

    if (HVC_ENC_Exit(eBoard, eCh))
    {
        LOG(err_msg, "%s line %d failed!", __FILE__, __LINE__);

        goto callback_encode_ret;
    }
    LOG("\n Encoder exit!\n");
    gettimeofday(&tv2, NULL);
    timersub(&tv2, &tv1, &res);
    LOG("%lu sec %lu usec\n", res.tv_sec, res.tv_usec); 
    
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ProgressBar[eCh]), 0.0);

    close(fd_w[eCh]);

callback_encode_ret:
    LOG("%s\n", err_msg);
}

void handler_run(GtkWidget *button, ENCODE_CALLBACK_PARAM_T *param)
{
    if (FilenameRawYUV[param->eCh] == NULL)
    {
        GtkWidget *dialog;

        dialog = gtk_message_dialog_new
                 (
                      GTK_WINDOW(param->window),
                      GTK_DIALOG_DESTROY_WITH_PARENT,
                      GTK_MESSAGE_ERROR,
                      GTK_BUTTONS_OK,
                      "Error opening file"
                 );

        gtk_window_set_title(GTK_WINDOW(dialog), "Error");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    pthread_t tid;
    pthread_create
    (
        &tid,
        NULL,
        encode_thr_fn,
        param
    );
}

void handler_open(GtkWidget *button, OPEN_CALLBACK_PARAM_T *param)    
{
    GtkWidget *dialog;

    dialog = gtk_file_chooser_dialog_new
            (
                "Select raw image ...",
                GTK_WINDOW(param->window),
                GTK_FILE_CHOOSER_ACTION_SAVE,
                "_Cancel", GTK_RESPONSE_CANCEL,
                "_Open", GTK_RESPONSE_ACCEPT,
                NULL
            );
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_ACCEPT)
    {
        FilenameRawYUV[param->eCh] = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        gtk_button_set_label(GTK_BUTTON(button), basename(FilenameRawYUV[param->eCh]));
    }

    gtk_widget_destroy(dialog);
}

