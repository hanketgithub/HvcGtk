
/******************************
 * include
 */

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


#include "m31_hvc_api/HVC_types.h"
#include "m31_hvc_api/HVC_encoder.h"
#include "HvcGtk.h"



/******************************
 * local variable
 */

FILE *ui_logging;
char err_msg[FILENAME_MAX];

gchar *FilenameRawYUV[API_HVC_CHN_MAX];
int fd_raw[API_HVC_CHN_MAX];
int fd_es[API_HVC_CHN_MAX];


GtkWidget *window;
GtkNotebook *notebook;
GtkWidget *label0;
GtkWidget *label1;
GtkWidget *label2;
GtkGrid *gridBasic;
GtkGrid *gridInput;
GtkGrid *gridCoding;


GtkWidget *profileLabel;
GtkWidget *profileMainRadioButton;
GtkWidget *profileMain10RadioButton;
GtkWidget *profileBox;


GtkWidget *levelLabel;
GtkWidget *level40RadioButton;
GtkWidget *level41RadioButton;
GtkWidget *level50RadioButton;
GtkWidget *level51RadioButton;
GtkWidget *levelBox;

GtkWidget *tierLabel;
GtkWidget *tierMainRadioButton;
GtkWidget *tierHighRadioButton;
GtkWidget *tierBox;

GtkWidget *ResLabel;
GtkComboBoxText *ResCombo;

GtkWidget *bitdepthLabel;
GtkWidget *bitdepth8RadioButton;
GtkWidget *bitdepthP010RadioButton;
GtkWidget *bitdepthP10LERadioButton;
GtkWidget *bitdepthBox;

GtkWidget *chromaLabel;
GtkWidget *chroma420RadioButton;
GtkWidget *chroma422RadioButton;
GtkWidget *chromaBox;

GtkWidget *PixFmtLabel;
GtkWidget *PixFmtNV12RadioButton;
GtkWidget *PixFmt420PRadioButton;
GtkWidget *PixFmtBox;

GtkWidget *GopLabel;
GtkWidget *GopIbRadioButton;
GtkWidget *GopIpRadioButton;
GtkWidget *GopIpbRadioButton;
GtkWidget *GopIRadioButton;
GtkWidget *GopBox;

GtkWidget *gopSizeLabel;
GtkWidget *gopSizeEntry;

GtkWidget *idrIntervalLabel;
GtkWidget *idrIntervalEntry;

GtkWidget *bNumLabel;
GtkWidget *bNumScale;

GtkWidget *FramerateLabel;
GtkComboBoxText *FramerateCombo;

GtkWidget *bitrateLabel;
GtkWidget *bitrate;

GtkWidget *OpenButton[API_HVC_CHN_MAX];
GtkWidget *EncodeButton[API_HVC_CHN_MAX];
GtkWidget *ProgressBar[API_HVC_CHN_MAX];

API_HVC_IMG_T img;

API_HVC_INIT_PARAM_T tApiHvcInitParam =
{
    .eInputMode     = API_HVC_INPUT_MODE_DATA,
    .eProfile       = API_HVC_HEVC_MAIN_PROFILE,
    .eLevel         = API_HVC_HEVC_LEVEL_40,
    .eTier          = API_HVC_HEVC_MAIN_TIER,
    
    .eResolution    = API_HVC_RESOLUTION_3840x2160,
    .eChromaFmt     = API_HVC_CHROMA_FORMAT_420,
    .eBitDepth      = API_HVC_BIT_DEPTH_8,

    .eGopType       = API_HVC_GOP_IB,
    .eGopSize       = API_HVC_GOP_SIZE_64,
    .eBFrameNum     = API_HVC_B_FRAME_ONE,
    
    .eTargetFrameRate = API_HVC_FPS_24,
    .u32Bitrate     = 32000,
    
    .eDbgLevel = API_HVC_DBG_LEVEL_3,
};



static POP_ES_CALLBACK_PARAM_T tPopEsArgs[API_HVC_BOARD_MAX][API_HVC_CHN_MAX];
static ENCODE_CALLBACK_PARAM_T tEncodeParam[API_HVC_CHN_MAX];
static OPEN_CALLBACK_PARAM_T   tOpenParam[API_HVC_CHN_MAX];


extern FILE *__hvc_encoder_logging__;



/// Basic
static void callback_profile()
{    
    GSList *list; 
    GtkToggleButton *button = NULL;
    
    list = gtk_radio_button_get_group( GTK_RADIO_BUTTON(profileMainRadioButton) );
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const char *val = gtk_button_get_label( GTK_BUTTON(button) );
    
    if (strcmp(val, "Main") == 0)
    {
        tApiHvcInitParam.eProfile = API_HVC_HEVC_MAIN_PROFILE;
    }
    else if (strcmp(val, "Main10") == 0)
    {
        tApiHvcInitParam.eProfile = API_HVC_HEVC_MAIN10_PROFILE;
    }

    LOG("%s: %s selected\n", __FUNCTION__, val);
}

static void gen_profile()
{
    // Profile field
    profileLabel = gtk_label_new ("Profile: ");
    profileMainRadioButton      = gtk_radio_button_new_with_label(NULL, "Main");
    profileMain10RadioButton    = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(profileMainRadioButton), "Main10");
    
    // connecto to signal
    g_signal_connect(profileMainRadioButton, "toggled", callback_profile, NULL);
    g_signal_connect(profileMain10RadioButton, "toggled", callback_profile, NULL);
    
    profileBox = gtk_box_new(FALSE, 5);
    gtk_box_pack_start( GTK_BOX(profileBox), profileMainRadioButton, FALSE, FALSE, 0);
    gtk_box_pack_start( GTK_BOX(profileBox), profileMain10RadioButton, FALSE, FALSE, 0);

    // Attatch profile
    gtk_grid_attach
    (
        gridBasic,
        profileLabel,
        0, GRID_ORDER_PROFILE, 1, 1
    );
    
    gtk_grid_attach
    (
        gridBasic,
        profileBox,
        1, GRID_ORDER_PROFILE, 1, 1
    );    
}

static void callback_level()
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    
    list = gtk_radio_button_get_group( GTK_RADIO_BUTTON(level40RadioButton) );
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const char *val = gtk_button_get_label( GTK_BUTTON(button) );
    
    if (strcmp(val, "4.0") == 0)
    {
        tApiHvcInitParam.eLevel = API_HVC_HEVC_LEVEL_40;
    }
    else if (strcmp(val, "4.1") == 0)
    {
        tApiHvcInitParam.eLevel = API_HVC_HEVC_LEVEL_41;
    }
    else if (strcmp(val, "5.0") == 0)
    {
        tApiHvcInitParam.eLevel = API_HVC_HEVC_LEVEL_50;
    }
    else if (strcmp(val, "5.1") == 0)
    {
        tApiHvcInitParam.eLevel = API_HVC_HEVC_LEVEL_51;
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

static void gen_level()
{
    // Level field
    levelLabel = gtk_label_new ("Level: ");
    level40RadioButton = gtk_radio_button_new_with_label(NULL, "4.0");
    level41RadioButton = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(level40RadioButton), "4.1");
    level50RadioButton = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(level40RadioButton), "5.0");
    level51RadioButton = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(level40RadioButton), "5.1");

    // connecto to signal
    g_signal_connect(level40RadioButton, "toggled", callback_level, NULL);
    g_signal_connect(level41RadioButton, "toggled", callback_level, NULL);
    g_signal_connect(level50RadioButton, "toggled", callback_level, NULL);
    g_signal_connect(level51RadioButton, "toggled", callback_level, NULL);
    
    levelBox = gtk_box_new(FALSE, 5);
    gtk_box_pack_start( GTK_BOX(levelBox), level40RadioButton, FALSE, FALSE, 0);
    gtk_box_pack_start( GTK_BOX(levelBox), level41RadioButton, FALSE, FALSE, 0);    
    gtk_box_pack_start( GTK_BOX(levelBox), level50RadioButton, FALSE, FALSE, 0);
    gtk_box_pack_start( GTK_BOX(levelBox), level51RadioButton, FALSE, FALSE, 0);

    // Attatch level
    gtk_grid_attach
    (
        gridBasic,
        levelLabel,
        0, GRID_ORDER_LEVEL, 1, 1
    );

    gtk_grid_attach
    (
        gridBasic,
        levelBox,
        1, GRID_ORDER_LEVEL, 1, 1
    );    
}

static void callback_tier()
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    
    list = gtk_radio_button_get_group( GTK_RADIO_BUTTON(tierMainRadioButton) );
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const char *val = gtk_button_get_label( GTK_BUTTON(button) );
    
    if (strcmp(val, "Main") == 0)
    {
        tApiHvcInitParam.eTier = API_HVC_HEVC_MAIN_TIER;
    }
    else if (strcmp(val, "High") == 0)
    {
        tApiHvcInitParam.eTier = API_HVC_HEVC_HIGH_TIER;
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

static void gen_tier()
{
    // Tier field
    tierLabel = gtk_label_new ("Tier: ");
    tierMainRadioButton = gtk_radio_button_new_with_label(NULL, "Main");
    tierHighRadioButton = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(tierMainRadioButton), "High");
    
    tierBox = gtk_box_new(FALSE, 5);
    gtk_box_pack_start( GTK_BOX(tierBox), tierMainRadioButton, FALSE, FALSE, 0);
    gtk_box_pack_start( GTK_BOX(tierBox), tierHighRadioButton, FALSE, FALSE, 0);
    
    // connect to signal
    g_signal_connect(tierMainRadioButton, "toggled", callback_tier, NULL);
    g_signal_connect(tierHighRadioButton, "toggled", callback_tier, NULL);

    // Attatch tier
    gtk_grid_attach
    (
        gridBasic,
        tierLabel,
        0, GRID_ORDER_TIER, 1, 1
    );

    gtk_grid_attach
    (
        gridBasic,
        tierBox,
        1, GRID_ORDER_TIER, 1, 1
    );    
}

static void callback_res()
{
    gchar *val = NULL;
    
    val = gtk_combo_box_text_get_active_text(ResCombo);

    if (strcmp(val, "3840x2160") == 0)
    {
        tApiHvcInitParam.eResolution = API_HVC_RESOLUTION_3840x2160;
    }
    else if (strcmp(val, "1920x1080") == 0)
    {
        tApiHvcInitParam.eResolution = API_HVC_RESOLUTION_1920x1080;
    }
    else if (strcmp(val, "1280x720") == 0)
    {
        tApiHvcInitParam.eResolution = API_HVC_RESOLUTION_1280x720;
    }
    else if (strcmp(val, "720x576") == 0)
    {
        tApiHvcInitParam.eResolution = API_HVC_RESOLUTION_720x576;
    }
    else if (strcmp(val, "720x480") == 0)
    {
        tApiHvcInitParam.eResolution = API_HVC_RESOLUTION_720x480;
    }
        
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

static void gen_res()
{
    // Resolution field
    ResLabel = gtk_label_new("Resolution: ");
    ResCombo = GTK_COMBO_BOX_TEXT(gtk_combo_box_text_new());
    
    gtk_combo_box_text_append_text
    (
        ResCombo,
        "3840x2160"
    );
    gtk_combo_box_text_append_text
    (
        ResCombo,
        "1920x1080"
    );
    gtk_combo_box_text_append_text
    (
        ResCombo,
        "1280x720"
    );    
    gtk_combo_box_text_append_text
    (
        ResCombo,
        "720x576"
    );   
    gtk_combo_box_text_append_text
    (
        ResCombo,
        "720x480"
    );  
    gtk_combo_box_set_active(GTK_COMBO_BOX(ResCombo), 0);
    
    // connect to signal    
    g_signal_connect(ResCombo, "changed", callback_res, NULL);

    // Attatch resolution
    gtk_grid_attach
    (
        gridBasic,
        ResLabel,
        0, GRID_ORDER_RESOLUTION, 1, 1
    );
    
    gtk_grid_attach
    (
        gridBasic,
        GTK_WIDGET(ResCombo),
        1, GRID_ORDER_RESOLUTION, 1, 1
    );    
}

static void callback_framerate()
{
    gchar *val = NULL;

    val = gtk_combo_box_text_get_active_text(FramerateCombo);
    
    if (strcmp(val, "24") == 0)
    {
        tApiHvcInitParam.eTargetFrameRate = API_HVC_FPS_24;
    }
    else if (strcmp(val, "25") == 0)
    {
        tApiHvcInitParam.eTargetFrameRate = API_HVC_FPS_25;
    }
    else if (strcmp(val, "29.97") == 0)
    {
        tApiHvcInitParam.eTargetFrameRate = API_HVC_FPS_29_97;
    }
    else if (strcmp(val, "30") == 0)
    {
        tApiHvcInitParam.eTargetFrameRate = API_HVC_FPS_30;
    }
    else if (strcmp(val, "50") == 0)
    {
        tApiHvcInitParam.eTargetFrameRate = API_HVC_FPS_50;
    }
    else if (strcmp(val, "59.94") == 0)
    {
        tApiHvcInitParam.eTargetFrameRate = API_HVC_FPS_59_94;
    }
    else if (strcmp(val, "60") == 0)
    {
        tApiHvcInitParam.eTargetFrameRate = API_HVC_FPS_60;
    }

    LOG("%s: %s selected\n", __FUNCTION__, val);
}

static void gen_framerate()
{
    FramerateLabel = gtk_label_new("Frame Rate: ");
    FramerateCombo = GTK_COMBO_BOX_TEXT(gtk_combo_box_text_new());

    gtk_combo_box_text_append_text
    (
        FramerateCombo,
        "24"
    );
    gtk_combo_box_text_append_text
    (
        FramerateCombo,
        "25"
    );
    gtk_combo_box_text_append_text
    (
        FramerateCombo,
        "29.97"
    );
    gtk_combo_box_text_append_text
    (
        FramerateCombo,
        "30"
    );
    gtk_combo_box_text_append_text
    (
        FramerateCombo,
        "50"
    );
    gtk_combo_box_text_append_text
    (
        FramerateCombo,
        "59.94"
    );
    gtk_combo_box_text_append_text
    (
        FramerateCombo,
        "60"
    );
    
    gtk_combo_box_set_active(GTK_COMBO_BOX(FramerateCombo), 0);
    
    g_signal_connect(FramerateCombo, "changed" , callback_framerate, NULL);
    
    // Attatch framerate
    gtk_grid_attach
    (
        gridBasic,
        FramerateLabel,
        0, GRID_ORDER_FRAMERATE, 1, 1
    );

    gtk_grid_attach
    (
        gridBasic,
        GTK_WIDGET(FramerateCombo),
        1, GRID_ORDER_FRAMERATE, 1, 1
    );
}

static void gen_bitrate()
{
    // bitrate field
    bitrateLabel    = gtk_label_new ("Bitrate (kbps): ");
    bitrate         = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1000.0, 32000.0, 1000.0);

    // Attach bitrate
    gtk_grid_attach
    (
        gridBasic,
        bitrateLabel,
        0, GRID_ORDER_BITRATE, 1, 1
    );

    gtk_grid_attach
    (
        gridBasic,
        bitrate,
        1, GRID_ORDER_BITRATE, 1, 1
    );
}

/// Input
static void callback_bitdepth()
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    
    list = gtk_radio_button_get_group( GTK_RADIO_BUTTON(bitdepth8RadioButton) );
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const char *val = gtk_button_get_label( GTK_BUTTON(button) );
    
    if (strcmp(val, "8") == 0)
    {
        tApiHvcInitParam.eBitDepth = API_HVC_BIT_DEPTH_8;
    }
    else if (strcmp(val, "P010") == 0)
    {
        tApiHvcInitParam.eBitDepth = API_HVC_BIT_DEPTH_P010;
    }
    else if (strcmp(val, "P016") == 0)
    {
        tApiHvcInitParam.eBitDepth = API_HVC_BIT_DEPTH_P016;
    }
    else if (strcmp(val, "P10LE") == 0)
    {
        tApiHvcInitParam.eBitDepth = API_HVC_BIT_DEPTH_P10LE;
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

static void gen_bitdepth()
{
    // Bitdepth field
    bitdepthLabel = gtk_label_new ("Bitdepth: ");
    
    bitdepth8RadioButton = gtk_radio_button_new_with_label(NULL, "8");
    bitdepthP010RadioButton = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(bitdepth8RadioButton), "P010");
    bitdepthP10LERadioButton = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(bitdepth8RadioButton), "P10LE");
    
    // connect to signal
    g_signal_connect(bitdepth8RadioButton,    "toggled", callback_bitdepth, NULL);
    g_signal_connect(bitdepthP010RadioButton, "toggled", callback_bitdepth, NULL);
    g_signal_connect(bitdepthP10LERadioButton, "toggled", callback_bitdepth, NULL);
    
    bitdepthBox = gtk_box_new(FALSE, 5);
    gtk_box_pack_start( GTK_BOX(bitdepthBox), bitdepth8RadioButton, FALSE, FALSE, 0);
    gtk_box_pack_start( GTK_BOX(bitdepthBox), bitdepthP010RadioButton, FALSE, FALSE, 0);    
    gtk_box_pack_start( GTK_BOX(bitdepthBox), bitdepthP10LERadioButton, FALSE, FALSE, 0);     

    // Attatch bitdepth
    gtk_grid_attach
    (
        gridInput,
        bitdepthLabel,
        0, GRID_ORDER_BITDEPTH, 1, 1
    );
    
    gtk_grid_attach
    (
        gridInput,
        bitdepthBox,
        1, GRID_ORDER_BITDEPTH, 1, 1
    );     
}

static void callback_chroma()
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    
    list = gtk_radio_button_get_group( GTK_RADIO_BUTTON(chroma420RadioButton) );
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const char *val = gtk_button_get_label( GTK_BUTTON(button) );
    
    if (strcmp(val, "420") == 0)
    {
        tApiHvcInitParam.eChromaFmt = API_HVC_CHROMA_FORMAT_420;
    }
    else if (strcmp(val, "422") == 0)
    {
        tApiHvcInitParam.eChromaFmt = API_HVC_CHROMA_FORMAT_422;
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

static void gen_chroma()
{
    // Chroma field
    chromaLabel = gtk_label_new ("Chroma: ");
    chroma420RadioButton = gtk_radio_button_new_with_label(NULL, "420");
    chroma422RadioButton = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(chroma420RadioButton), "422");
    
    // connect to signal
    g_signal_connect(chroma420RadioButton, "toggled", callback_chroma, NULL);
    g_signal_connect(chroma420RadioButton, "toggled", callback_chroma, NULL);
    
    chromaBox = gtk_box_new(FALSE, 5);
    gtk_box_pack_start( GTK_BOX(chromaBox), chroma420RadioButton, FALSE, FALSE, 0);
    gtk_box_pack_start( GTK_BOX(chromaBox), chroma422RadioButton, FALSE, FALSE, 0);

    // Attatch chroma
    gtk_grid_attach
    (
        gridInput,
        chromaLabel,
        0, GRID_ORDER_CHROMA, 1, 1
    );

    gtk_grid_attach
    (
        gridInput,
        chromaBox,
        1, GRID_ORDER_CHROMA, 1, 1
    );
}

static void callback_pixfmt()
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    
    list = gtk_radio_button_get_group( GTK_RADIO_BUTTON(PixFmtNV12RadioButton) );
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const char *val = gtk_button_get_label( GTK_BUTTON(button) );
    
    if (strcmp(val, "NV12") == 0)
    {
        img.eFormat = API_HVC_IMAGE_FORMAT_NV12;
    }
    else if (strcmp(val, "420P") == 0)
    {
        img.eFormat = API_HVC_IMAGE_FORMAT_YUV420;
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

static void gen_pixfmt()
{
    // Pixel format field
    PixFmtLabel = gtk_label_new ("Pixel Fmt: ");
    PixFmtNV12RadioButton = gtk_radio_button_new_with_label(NULL, "NV12");
    PixFmt420PRadioButton = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(PixFmtNV12RadioButton), "420P");
    
    // connect to signal
    g_signal_connect(PixFmtNV12RadioButton, "toggled", callback_pixfmt, NULL);
    g_signal_connect(PixFmt420PRadioButton, "toggled", callback_pixfmt, NULL);
    
    PixFmtBox = gtk_box_new(FALSE, 5);
    gtk_box_pack_start( GTK_BOX(PixFmtBox), PixFmtNV12RadioButton, FALSE, FALSE, 0);
    gtk_box_pack_start( GTK_BOX(PixFmtBox), PixFmt420PRadioButton, FALSE, FALSE, 0);

    // Attatch chroma
    gtk_grid_attach
    (
        gridInput,
        PixFmtLabel,
        0, GRID_ORDER_PIX_FMT, 1, 1
    );

    gtk_grid_attach
    (
        gridInput,
        PixFmtBox,
        1, GRID_ORDER_PIX_FMT, 1, 1
    );
}

/// Coding
static void callback_gop()
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    
    list = gtk_radio_button_get_group( GTK_RADIO_BUTTON(GopIbRadioButton) );
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const char *val = gtk_button_get_label( GTK_BUTTON(button) );

    if (strcmp(val, "IP") == 0)
    {
        tApiHvcInitParam.eGopType = API_HVC_GOP_IP;
        gtk_widget_set_sensitive( GTK_WIDGET(bNumScale), FALSE);
    }
    else if (strcmp(val, "IB") == 0)
    {
        tApiHvcInitParam.eGopType = API_HVC_GOP_IB;
        gtk_widget_set_sensitive( GTK_WIDGET(bNumScale), TRUE);
    }
    else if (strcmp(val, "IPB") == 0)
    {
        tApiHvcInitParam.eGopType = API_HVC_GOP_IPB;
        gtk_widget_set_sensitive( GTK_WIDGET(bNumScale), TRUE);
    }
    else if (strcmp(val, "I") == 0)
    {
        tApiHvcInitParam.eGopType       = API_HVC_GOP_I;
        tApiHvcInitParam.eGopSize       = API_HVC_GOP_SIZE_1;
        tApiHvcInitParam.eIDRFrameNum   = API_HVC_IDR_FRAME_ALL;
        tApiHvcInitParam.eBFrameNum     = API_HVC_B_FRAME_NONE;
        gtk_widget_set_sensitive( GTK_WIDGET(bNumScale), FALSE); 
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}


static void gen_gop()
{
    // GOP field
    GopLabel = gtk_label_new("GOP: ");
    GopIbRadioButton = gtk_radio_button_new_with_label(NULL, "IB");
    GopIpRadioButton = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(GopIbRadioButton), "IP");
    GopIpbRadioButton = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(GopIbRadioButton), "IPB");
    GopIRadioButton  = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON(GopIbRadioButton), "I");
    
    // connect to signal
    g_signal_connect(GopIbRadioButton, "toggled", callback_gop, NULL);
    g_signal_connect(GopIpRadioButton, "toggled", callback_gop, NULL);
    g_signal_connect(GopIpbRadioButton, "toggled", callback_gop, NULL);
    g_signal_connect(GopIRadioButton,  "toggled", callback_gop, NULL);
    
    GopBox = gtk_box_new(FALSE, 5);
    gtk_box_pack_start( GTK_BOX(GopBox), GopIbRadioButton, FALSE, FALSE, 0);
    gtk_box_pack_start( GTK_BOX(GopBox), GopIpRadioButton, FALSE, FALSE, 0);
    gtk_box_pack_start( GTK_BOX(GopBox), GopIpbRadioButton, FALSE, FALSE, 0);
    gtk_box_pack_start( GTK_BOX(GopBox), GopIRadioButton,  FALSE, FALSE, 0);
    
    // Attatch GOP
    gtk_grid_attach
    (
        gridCoding,
        GopLabel,
        0, GRID_ORDER_GOP, 1, 1
    );    

    gtk_grid_attach
    (
        gridCoding,
        GopBox,
        1, GRID_ORDER_GOP, 1, 1
    ); 
}


static void gen_gop_size()
{
    gopSizeLabel = gtk_label_new ("GOP Size: ");
    gopSizeEntry = gtk_entry_new();

    gtk_entry_set_text( GTK_ENTRY(gopSizeEntry), "64" );

    // Attatch GOP size
    gtk_grid_attach
    (
        gridCoding,
        gopSizeLabel,
        0, GRID_ORDER_GOP_SIZE, 1, 1
    );
    
    gtk_grid_attach
    (
        gridCoding,
        gopSizeEntry,
        1, GRID_ORDER_GOP_SIZE, 1, 1
    );     
}

static void gen_idr_interval()
{
    idrIntervalLabel = gtk_label_new ("IDR Interval: ");
    idrIntervalEntry = gtk_entry_new();

    gtk_entry_set_text( GTK_ENTRY(idrIntervalEntry), "0" );

    // Attatch GOP size
    gtk_grid_attach
    (
        gridCoding,
        idrIntervalLabel,
        0, GRID_ORDER_IDR_INTERVAL, 1, 1
    );
    
    gtk_grid_attach
    (
        gridCoding,
        idrIntervalEntry,
        1, GRID_ORDER_IDR_INTERVAL, 1, 1
    );     
}



static void gen_b_frame_num()
{
    // Ref frame number
    bNumLabel = gtk_label_new ("B frame #: ");
    bNumScale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1.0, 8.0, 1.0);
    
    // Attatch ref
    gtk_grid_attach
    (
        gridCoding,
        bNumLabel,
        0, GRID_ORDER_BNUM, 1, 1
    );
    
    gtk_grid_attach
    (
        gridCoding,
        bNumScale,
        1, GRID_ORDER_BNUM, 1, 1
    ); 
}

static size_t calculate_vraw_enqueue_data_size (API_HVC_INIT_PARAM_T *p_init_param)
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
        case API_HVC_BIT_DEPTH_P10LE:
        case API_HVC_BIT_DEPTH_P016:
        {
            bit_depth = 16;
            break;
        }
        case API_HVC_BIT_DEPTH_P010:
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


void make_timestamp(char * timestamp_p, size_t size)
{
	time_t now;
	struct tm *now_tm_p;

	now = time ( NULL );

	now_tm_p = localtime ( &now );

	strftime ( timestamp_p, size, FMB_TIMESTAMP_FORMAT, now_tm_p );
}


static void make_output_file_name
(
    const char *timestamp, char *es_file_name_p, size_t length
)
{
	int result;

	result = snprintf( es_file_name_p, ( length - 1 ), FMB_ES_FILE_NAME_FORMAT, timestamp);
}


static void ui_process_coded_frame(API_HVC_HEVC_CODED_PICT_T *p_coded_pict, void *args)
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

    p += sprintf(p, "%s: board=%d, ch=%d, pts=%d, type=%d ",
        __FUNCTION__,
        eBoard, eCh,
        p_coded_pict->u32pts,
        p_coded_pict->eFrameType);
        
    uint32_t i;
    for (i = 0; i < p_coded_pict->u32NalNum; i++)
    {
        p += sprintf(p, "[NAL%u addr=%p, len=%u, type=%u]", 
                        i,
                        p_coded_pict->tNalInfo[i].pu8Addr,
                        p_coded_pict->tNalInfo[i].u32Length,
                        p_coded_pict->tNalInfo[i].eNalType);
  
        if (fd_es[eCh])
        {
            write(fd_es[eCh], p_coded_pict->tNalInfo[i].pu8Addr, p_coded_pict->tNalInfo[i].u32Length);
        }
    }
    LOG("%s\n", msg);

    p_callback_param->poped_frame++;

    gdouble fraction;

    fraction = (double) p_callback_param->poped_frame / (double) p_callback_param->total_frame;

    //LOG("%f %d %d\n", fraction, poped_frame, total_frame);

    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ProgressBar[eCh]), fraction);
}


static void *encode_thr_fn(void *data)
{
    ENCODE_CALLBACK_PARAM_T *param = (ENCODE_CALLBACK_PARAM_T *) data;
    char *str_profile = (tApiHvcInitParam.eProfile == API_HVC_HEVC_MAIN_PROFILE) ? "Main" : "Main10";
    
    LOG("Profile: %s\n", str_profile);
    
    char *str_level;
    
    struct timeval tv1, tv2, res;
    
    switch (tApiHvcInitParam.eLevel)
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

    
    char *str_tier = (tApiHvcInitParam.eTier == API_HVC_HEVC_MAIN_TIER) ? "Main Tier" : "High Tier";
    
    LOG("Tier: %s\n", str_tier);
    

    char *str_res = "Unknown";
    
    switch (tApiHvcInitParam.eResolution)
    {
        case API_HVC_RESOLUTION_3840x2160:
        {
            str_res = "3840x2160";

            tApiHvcInitParam.tCrop.u32CropLeft      = 0;
            tApiHvcInitParam.tCrop.u32CropLeft      = 0;
            tApiHvcInitParam.tCrop.u32CropTop       = 0;
            tApiHvcInitParam.tCrop.u32CropBottom    = 0;
            
            break;
        }        
        case API_HVC_RESOLUTION_1920x1080:
        {
            str_res = "1920x1080";

            tApiHvcInitParam.tCrop.u32CropLeft      = 0;
            tApiHvcInitParam.tCrop.u32CropLeft      = 0;
            tApiHvcInitParam.tCrop.u32CropTop       = 0;
            tApiHvcInitParam.tCrop.u32CropBottom    = 8;
            
            break;
        }        
        case API_HVC_RESOLUTION_1280x720:
        {
            str_res = "1280x720";

            tApiHvcInitParam.tCrop.u32CropLeft      = 0;
            tApiHvcInitParam.tCrop.u32CropLeft      = 0;
            tApiHvcInitParam.tCrop.u32CropTop       = 0;
            tApiHvcInitParam.tCrop.u32CropBottom    = 0;
            
            break;
        }        
        case API_HVC_RESOLUTION_720x576:
        {
            str_res = "720x576";
            
            tApiHvcInitParam.eAspectRatioIdc = API_HVC_HEVC_ASPECT_RATIO_IDC_4;

            tApiHvcInitParam.tCrop.u32CropLeft      = 0;
            tApiHvcInitParam.tCrop.u32CropLeft      = 0;
            tApiHvcInitParam.tCrop.u32CropTop       = 0;
            tApiHvcInitParam.tCrop.u32CropBottom    = 0;
            
            break;
        }   
        case API_HVC_RESOLUTION_720x480:
        {
            str_res = "720x480";

            tApiHvcInitParam.eAspectRatioIdc = API_HVC_HEVC_ASPECT_RATIO_IDC_5;
            
            tApiHvcInitParam.tCrop.u32CropLeft      = 0;
            tApiHvcInitParam.tCrop.u32CropLeft      = 0;
            tApiHvcInitParam.tCrop.u32CropTop       = 0;
            tApiHvcInitParam.tCrop.u32CropBottom    = 0;
            
            break;
        }  
        default:
        {
            break;
        }
    }
    
    LOG("Resolution: %s\n", str_res);

    char *str_framerate = "Unknown";
    
    switch (tApiHvcInitParam.eTargetFrameRate)
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

    bitrate_val = gtk_range_get_value( GTK_RANGE(bitrate) );
    
    LOG("Bitrate %d kbps\n", bitrate_val);
    
    tApiHvcInitParam.u32Bitrate = bitrate_val;


    char *str_bitdepth = "Unknown";
    
    switch (tApiHvcInitParam.eBitDepth)
    {
        case API_HVC_BIT_DEPTH_8:
        {
            str_bitdepth = "8";
            break;
        }        
        case API_HVC_BIT_DEPTH_P10LE:
        {
            str_bitdepth = "P10LE";
            break;
        }   
        case API_HVC_BIT_DEPTH_P016:
        {
            str_bitdepth = "P016";
            break;
        }        
        case API_HVC_BIT_DEPTH_P010:
        {
            str_bitdepth = "P010";
            break;
        }        
        default:
        {
            break;
        }
    }
    
    LOG("bit depth: %s\n", str_bitdepth);
    
    
    char *str_chroma = (tApiHvcInitParam.eChromaFmt == API_HVC_CHROMA_FORMAT_420) ? "420" : "422";
    
    LOG("Chroma: %s\n", str_chroma);

    
    char *str_gop = "Unknown";

    switch (tApiHvcInitParam.eGopType)
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

    if (tApiHvcInitParam.eGopType != API_HVC_GOP_I)
    {
        tApiHvcInitParam.eGopSize = atoi(gtk_entry_get_text( GTK_ENTRY(gopSizeEntry) ));
    }

    LOG("GOP size=%d\n", tApiHvcInitParam.eGopSize);

    if (tApiHvcInitParam.eGopType != API_HVC_GOP_I)
    {
        tApiHvcInitParam.eIDRFrameNum = atoi(gtk_entry_get_text( GTK_ENTRY(idrIntervalEntry) ));
    }

    LOG("IDR interval=%d\n", tApiHvcInitParam.eIDRFrameNum);
    

    if ((tApiHvcInitParam.eGopType == API_HVC_GOP_IB)
       || (tApiHvcInitParam.eGopType == API_HVC_GOP_IPB))
    {
        guint refnum;
    
        refnum = gtk_range_get_value( GTK_RANGE(bNumScale) );
        
        tApiHvcInitParam.eBFrameNum = (API_HVC_B_FRAME_NUM_E) refnum;

        LOG("B ref#=%u\n", refnum);
    }

    tApiHvcInitParam.tCoding.bDisableAMP = true;
    

    API_HVC_BOARD_E eBoard = API_HVC_BOARD_1;
    API_HVC_CHN_E eCh;

    eCh = param->eCh;
    
    gettimeofday(&tv1, NULL);
    if (HVC_ENC_Init(eBoard, eCh, &tApiHvcInitParam))
    {
        sprintf(err_msg, "%s line %d failed!", __FILE__, __LINE__);
            
        goto callback_encode_ret;
    }  
    LOG("HVC_ENC_Init success!\n");


    tPopEsArgs[eBoard][eCh].board_num = eBoard;
    tPopEsArgs[eBoard][eCh].channel   = eCh;
    if (
        HVC_ENC_RegisterCallback
        (
            eBoard,
            eCh,
            ui_process_coded_frame,
            (void *) &tPopEsArgs[eBoard][eCh]
        )
       )
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
    make_output_file_name(timestamp, es_file_name, FILENAME_MAX);

    fd_raw[eCh]  = open(FilenameRawYUV[eCh], O_RDONLY);
    fd_es[eCh]   = open(es_file_name, 
                    O_WRONLY | O_CREAT,
                    S_IRWXU);
                 
    uint8_t *vraw_data_buf_p = NULL;
    uint32_t frame_sz = 0;
    struct stat file_stat;
    int remain_frame = 0;

    fstat(fd_raw[eCh], &file_stat);

    frame_sz = calculate_vraw_enqueue_data_size(&tApiHvcInitParam);
    remain_frame = ((uint64_t) file_stat.st_size / frame_sz);
    tPopEsArgs[eBoard][eCh].total_frame = remain_frame;
    tPopEsArgs[eBoard][eCh].poped_frame = 0;
    
    vraw_data_buf_p = malloc(frame_sz);;

    while (remain_frame > 0)
    {        
        read(fd_raw[eCh], vraw_data_buf_p, frame_sz);

        remain_frame--;

        img.pu8Addr     = vraw_data_buf_p;
        img.u32Size     = frame_sz;
        img.u32Pts      = GET_PTS_IN_MS(tPopEsArgs[eBoard][eCh].total_frame - remain_frame);
        img.bLastFrame  = (remain_frame == 0) ? true : false;

        if (HVC_ENC_PushImage(eBoard, eCh, &img))
        {
            sprintf(err_msg, "Error: %s PushImage failed!\n", __FILE__);

            goto callback_encode_ret;
        }
    }

    LOG("Encode done...\n");

    // try stop
    while (HVC_ENC_Stop(eBoard, eCh))
    {
        sleep(1);
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

    close(fd_es[eCh]);

callback_encode_ret:
    LOG("%s\n", err_msg);
}

static void callback_encode(GtkWidget *button, ENCODE_CALLBACK_PARAM_T *param)
{
    pthread_t tid;
    pthread_create
    (
        &tid,
        NULL,
        encode_thr_fn,
        param
    );
}


static void gen_encode()
{
    int i;

    for (i = 0; i < sizeof(EncodeButton) / sizeof(EncodeButton[0]); i++)
    {    
        EncodeButton[i] = gtk_button_new_with_label("Encode");

        tEncodeParam[i].eCh = i;
        g_signal_connect(EncodeButton[i], "clicked", G_CALLBACK(callback_encode), &tEncodeParam[i]);

        // Attach encode
        gtk_grid_attach
        (
            gridBasic,
            EncodeButton[i],
            0, GRID_ORDER_ENCODE + i * 2, 1, 1
        );
    }
}


static void callback_open(GtkWidget *button, OPEN_CALLBACK_PARAM_T *param)    
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
    gint result = gtk_dialog_run (GTK_DIALOG (dialog));

    if (result == GTK_RESPONSE_ACCEPT)
    {
        FilenameRawYUV[param->eCh] = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));

        gtk_button_set_label(GTK_BUTTON(button), FilenameRawYUV[param->eCh]);
    }

    gtk_widget_destroy (dialog);
}

static void gen_open(GtkWidget *window)
{
    int i;
    
    for (i = 0; i < sizeof(OpenButton) / sizeof(OpenButton[0]); i++)
    {
        OpenButton[i] = gtk_button_new_with_label("Open ...");

        tOpenParam[i].eCh = i;
        tOpenParam[i].window = window;
        
        g_signal_connect(OpenButton[i], "clicked", G_CALLBACK(callback_open), &tOpenParam[i]);

        // Attach open
        gtk_grid_attach
        (
            gridBasic,
            OpenButton[i],
            0, GRID_ORDER_OPEN + i * 2, 2, 1
        );
    }
}

static void gen_bar()
{    
    int i;

    for (i = 0; i < sizeof(ProgressBar) / sizeof(ProgressBar[0]); i++)
    {
        ProgressBar[i] = gtk_progress_bar_new();

        // Attach open
        gtk_grid_attach
        (
            gridBasic,
            ProgressBar[i],
            1, GRID_ORDER_BAR + i * 2, 2, 1
        );
    }
}


int main(int argc, char *argv[])
{
    ui_logging = fopen("log_ui.txt", "w");
    __hvc_encoder_logging__ = fopen("log_api.txt", "w");
    
    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW (window), "HVC-8700");
    gtk_container_set_border_width(GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request(window, 150, 100);

    notebook = GTK_NOTEBOOK(gtk_notebook_new());

    label0  = gtk_label_new("Basic");
    label1  = gtk_label_new("Input");
    label2  = gtk_label_new("Coding");

    gridBasic   = GTK_GRID(gtk_grid_new());
    gridInput   = GTK_GRID(gtk_grid_new());
    gridCoding  = GTK_GRID(gtk_grid_new());

    // basic
    gen_profile();
    gen_level();
    gen_tier();
    gen_res();
    gen_framerate();
    gen_bitrate();

    // input
    gen_bitdepth();
    gen_chroma();
    gen_pixfmt();

    // coding
    gen_gop();
    gen_gop_size();
    gen_idr_interval();
    gen_b_frame_num();

    gen_encode();
    gen_open(window);

    gen_bar();


    /* Append to pages to the notebook container. */
    gtk_notebook_append_page(notebook, GTK_WIDGET(gridBasic), label0);
    gtk_notebook_append_page(notebook, GTK_WIDGET(gridInput), label1);
    gtk_notebook_append_page(notebook, GTK_WIDGET(gridCoding), label2);


    /* Add five pixels of spacing between every row and every column. */
    gtk_grid_set_row_spacing(gridBasic, 5);
    gtk_grid_set_row_spacing(gridInput, 5);
    gtk_grid_set_row_spacing(gridCoding, 5);

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(notebook));
    gtk_widget_show_all(window);
    
    gtk_main();
    
    fclose(ui_logging);
    fclose(__hvc_encoder_logging__);
    
    return 0;
}

