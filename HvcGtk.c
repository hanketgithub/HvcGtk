
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


#include "apiVENC_types.h"
#include "apiVENC.h"
#include "HvcGtk.h"
#include "handler.h"


/******************************
 * local variable
 */

FILE *ui_logging;
char err_msg[FILENAME_MAX];

gchar *FilenameRawYUV[API_VENC_CHN_MAX];
int fd_r[API_VENC_CHN_MAX];
int fd_w[API_VENC_CHN_MAX];


GtkWidget *window;
GtkNotebook *notebook;
GtkWidget *Label1;
GtkWidget *Label2;
GtkWidget *Label3;
GtkGrid   *GridCh[API_VENC_CHN_MAX];
GtkGrid   *GridAbout;

GtkWidget *ProfileLabel[API_VENC_CHN_MAX];
GtkWidget *ProfileMainRadioButton[API_VENC_CHN_MAX];
GtkWidget *ProfileMain10RadioButton[API_VENC_CHN_MAX];
GtkWidget *ProfileBox[API_VENC_CHN_MAX];

GtkWidget *LvLabel[API_VENC_CHN_MAX];
GtkWidget *Lv40RadioButton[API_VENC_CHN_MAX];
GtkWidget *Lv41RadioButton[API_VENC_CHN_MAX];
GtkWidget *Lv50RadioButton[API_VENC_CHN_MAX];
GtkWidget *Lv51RadioButton[API_VENC_CHN_MAX];
GtkWidget *LvBox[API_VENC_CHN_MAX];

GtkWidget *TierLabel[API_VENC_CHN_MAX];
GtkWidget *TierMainRadioButton[API_VENC_CHN_MAX];
GtkWidget *TierHighRadioButton[API_VENC_CHN_MAX];
GtkWidget *TierBox[API_VENC_CHN_MAX];

GtkWidget *ResLabel[API_VENC_CHN_MAX];
GtkComboBoxText *ResCombo[API_VENC_CHN_MAX];

GtkWidget *FpsLabel[API_VENC_CHN_MAX];
GtkComboBoxText *FpsCombo[API_VENC_CHN_MAX];

GtkWidget *BitrateLabel[API_VENC_CHN_MAX];
GtkWidget *Bitrate[API_VENC_CHN_MAX];

GtkWidget *BitdepthLabel[API_VENC_CHN_MAX];
GtkWidget *Bitdepth8RadioButton[API_VENC_CHN_MAX];
GtkWidget *Bitdepth10RadioButton[API_VENC_CHN_MAX];
GtkWidget *BitdepthBox[API_VENC_CHN_MAX];

GtkWidget *ChromaLabel[API_VENC_CHN_MAX];
GtkWidget *Chroma420RadioButton[API_VENC_CHN_MAX];
GtkWidget *Chroma422RadioButton[API_VENC_CHN_MAX];
GtkWidget *ChromaBox[API_VENC_CHN_MAX];

GtkWidget *PixFmtLabel[API_VENC_CHN_MAX];
GtkWidget *PixFmtIntRadioButton[API_VENC_CHN_MAX];
GtkWidget *PixFmtPlaRadioButton[API_VENC_CHN_MAX];
GtkWidget *PixFmtBox[API_VENC_CHN_MAX];

GtkWidget *GopLabel[API_VENC_CHN_MAX];
GtkWidget *GopIbRadioButton[API_VENC_CHN_MAX];
GtkWidget *GopIpRadioButton[API_VENC_CHN_MAX];
GtkWidget *GopIpbRadioButton[API_VENC_CHN_MAX];
GtkWidget *GopIRadioButton[API_VENC_CHN_MAX];
GtkWidget *GopBox[API_VENC_CHN_MAX];

GtkWidget *GopSizeLabel[API_VENC_CHN_MAX];
GtkWidget *GopSizeEntry[API_VENC_CHN_MAX];

GtkWidget *IdrIntervalLabel[API_VENC_CHN_MAX];
GtkWidget *IdrIntervalEntry[API_VENC_CHN_MAX];

GtkWidget *BNumLabel[API_VENC_CHN_MAX];
GtkWidget *BNumScale[API_VENC_CHN_MAX];


GtkWidget *OpenButton[API_VENC_CHN_MAX];
GtkWidget *EncodeButton[API_VENC_CHN_MAX];
GtkWidget *ProgressBar[API_VENC_CHN_MAX];

GtkWidget *CopyRight;
GtkWidget *ApiLabel;
GtkWidget *ApiVersion;
GtkWidget *DrvLabel;
GtkWidget *DrvVersion;
GtkWidget *SysFwLabel;
GtkWidget *SysFwVersion;
GtkWidget *McpuLabel;
GtkWidget *McpuVersion;
GtkWidget *FwSingleLabel;
GtkWidget *FwSingleVersion;
GtkWidget *FwMultiLabel;
GtkWidget *FwMultiVersion;


POP_ES_CALLBACK_PARAM_T tPopEsArgs[API_VENC_BOARD_MAX][API_VENC_CHN_MAX];
static ENCODE_CALLBACK_PARAM_T tEncodeParam[API_VENC_CHN_MAX];
static OPEN_CALLBACK_PARAM_T   tOpenParam[API_VENC_CHN_MAX];


static API_VENC_CHN_E eCh1 = API_VENC_CHN_1;
static API_VENC_CHN_E eCh2 = API_VENC_CHN_2;
static API_VENC_CHN_E eCh3 = API_VENC_CHN_3;
static API_VENC_CHN_E eCh4 = API_VENC_CHN_4;

API_VENC_INIT_PARAM_T tApiInitParam[API_VENC_CHN_MAX] =
{
    {
        .eInputMode     = API_VENC_INPUT_MODE_DATA,
        .eProfile       = API_VENC_HEVC_MAIN_PROFILE,
        .eLevel         = API_VENC_HEVC_LEVEL_40,
        .eTier          = API_VENC_HEVC_MAIN_TIER,
        
        .eResolution    = API_VENC_RESOLUTION_4096x2160,
        .eChromaFmt     = API_VENC_CHROMA_FORMAT_420,
        .eBitDepth      = API_VENC_BIT_DEPTH_8,

        .eGopType       = API_VENC_GOP_IB,
        .eGopSize       = API_VENC_GOP_SIZE_64,
        .eBFrameNum     = API_VENC_B_FRAME_ONE,
        
        .eTargetFrameRate = API_VENC_FPS_24,
        .u32Bitrate     = 32000,
        
        .eDbgLevel = API_VENC_DBG_LEVEL_0,
    },
    {
        .eInputMode     = API_VENC_INPUT_MODE_DATA,
        .eProfile       = API_VENC_HEVC_MAIN_PROFILE,
        .eLevel         = API_VENC_HEVC_LEVEL_40,
        .eTier          = API_VENC_HEVC_MAIN_TIER,
        
        .eResolution    = API_VENC_RESOLUTION_1920x1080,
        .eChromaFmt     = API_VENC_CHROMA_FORMAT_420,
        .eBitDepth      = API_VENC_BIT_DEPTH_8,

        .eGopType       = API_VENC_GOP_IB,
        .eGopSize       = API_VENC_GOP_SIZE_64,
        .eBFrameNum     = API_VENC_B_FRAME_ONE,
        
        .eTargetFrameRate = API_VENC_FPS_24,
        .u32Bitrate     = 32000,
        
        .eDbgLevel = API_VENC_DBG_LEVEL_0,
    },
};

/// Function Prototype
static void draw_profile(API_VENC_CHN_E *);
static void draw_level(API_VENC_CHN_E *);
static void draw_tier(API_VENC_CHN_E *);
static void draw_res(API_VENC_CHN_E *);
static void draw_framerate(API_VENC_CHN_E *);
static void draw_bitrate(API_VENC_CHN_E *);
static void draw_bitdepth();
static void draw_chroma();
static void draw_pixfmt();
static void draw_gop();
static void draw_gop_size();
static void draw_idr_interval();
static void draw_b_frame_num();


static void draw_profile(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    // Profile field
    ProfileLabel[eCh]               = gtk_label_new("Profile: ");
    ProfileMainRadioButton[eCh]     = gtk_radio_button_new_with_label(NULL, PROFILE_MAIN_TEXT);
    ProfileMain10RadioButton[eCh]   = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(ProfileMainRadioButton[eCh]), PROFILE_MAIN10_TEXT);
    
    // connecto to signal
    g_signal_connect(ProfileMainRadioButton[eCh],   "toggled", G_CALLBACK(handler_profile), pCh);
    g_signal_connect(ProfileMain10RadioButton[eCh], "toggled", G_CALLBACK(handler_profile), pCh);
    
    ProfileBox[eCh] = gtk_box_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(ProfileBox[eCh]), ProfileMainRadioButton[eCh], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(ProfileBox[eCh]), ProfileMain10RadioButton[eCh], FALSE, FALSE, 0);

    // Attatch profile
    gtk_grid_attach
    (
        GridCh[eCh],
        ProfileLabel[eCh],
        0, GRID_ORDER_PROFILE, 1, 1
    );
    
    gtk_grid_attach
    (
        GridCh[eCh],
        ProfileBox[eCh],
        1, GRID_ORDER_PROFILE, 1, 1
    );    
}


static void draw_level(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    // Level field
    LvLabel[eCh] = gtk_label_new("Level: ");
    Lv40RadioButton[eCh] = gtk_radio_button_new_with_label(NULL, LV_40_TEXT);
    Lv41RadioButton[eCh] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(Lv40RadioButton[eCh]), LV_41_TEXT);
    Lv50RadioButton[eCh] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(Lv40RadioButton[eCh]), LV_50_TEXT);
    Lv51RadioButton[eCh] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(Lv40RadioButton[eCh]), LV_51_TEXT);

    // connecto to signal
    g_signal_connect(Lv40RadioButton[eCh], "toggled", G_CALLBACK(handler_level), pCh);
    g_signal_connect(Lv41RadioButton[eCh], "toggled", G_CALLBACK(handler_level), pCh);
    g_signal_connect(Lv50RadioButton[eCh], "toggled", G_CALLBACK(handler_level), pCh);
    g_signal_connect(Lv51RadioButton[eCh], "toggled", G_CALLBACK(handler_level), pCh);
    
    LvBox[eCh] = gtk_box_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(LvBox[eCh]), Lv40RadioButton[eCh], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(LvBox[eCh]), Lv41RadioButton[eCh], FALSE, FALSE, 0);    
    gtk_box_pack_start(GTK_BOX(LvBox[eCh]), Lv50RadioButton[eCh], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(LvBox[eCh]), Lv51RadioButton[eCh], FALSE, FALSE, 0);

    // Attatch level
    gtk_grid_attach
    (
        GridCh[eCh],
        LvLabel[eCh],
        0, GRID_ORDER_LEVEL, 1, 1
    );

    gtk_grid_attach
    (
        GridCh[eCh],
        LvBox[eCh],
        1, GRID_ORDER_LEVEL, 1, 1
    );    
}


static void draw_tier(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    // Tier field
    TierLabel[eCh] = gtk_label_new ("Tier: ");
    TierMainRadioButton[eCh] = gtk_radio_button_new_with_label(NULL, TIER_MAIN_TEXT);
    TierHighRadioButton[eCh] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(TierMainRadioButton[eCh]), TIER_HIGH_TEXT);
    
    TierBox[eCh] = gtk_box_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(TierBox[eCh]), TierMainRadioButton[eCh], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(TierBox[eCh]), TierHighRadioButton[eCh], FALSE, FALSE, 0);
    
    // connect to signal
    g_signal_connect(TierMainRadioButton[eCh], "toggled", G_CALLBACK(handler_tier), pCh);
    g_signal_connect(TierHighRadioButton[eCh], "toggled", G_CALLBACK(handler_tier), pCh);

    // Attatch tier
    gtk_grid_attach
    (
        GridCh[eCh],
        TierLabel[eCh],
        0, GRID_ORDER_TIER, 1, 1
    );

    gtk_grid_attach
    (
        GridCh[eCh],
        TierBox[eCh],
        1, GRID_ORDER_TIER, 1, 1
    );    
}

static void draw_res(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    // Resolution field
    ResLabel[eCh] = gtk_label_new("Resolution: ");
    ResCombo[eCh] = GTK_COMBO_BOX_TEXT(gtk_combo_box_text_new());

    if (eCh == API_VENC_CHN_1)
    {
        gtk_combo_box_text_append_text
        (
            ResCombo[eCh],
            RESOLUTION_DCI_4K_TEXT
        );    
        gtk_combo_box_text_append_text
        (
            ResCombo[eCh],
            RESOLUTION_4K_TEXT
        );
    }
    gtk_combo_box_text_append_text
    (
        ResCombo[eCh],
        RESOLUTION_2K_TEXT
    );
    gtk_combo_box_text_append_text
    (
        ResCombo[eCh],
        RESOLUTION_HD_TEXT
    );    
    gtk_combo_box_text_append_text
    (
        ResCombo[eCh],
        RESOLUTION_SD_576_TEXT
    );   
    gtk_combo_box_text_append_text
    (
        ResCombo[eCh],
        RESOLUTION_SD_480_TEXT
    );  
    gtk_combo_box_set_active(GTK_COMBO_BOX(ResCombo[eCh]), 0);
    
    // connect to signal    
    g_signal_connect(ResCombo[eCh], "changed", G_CALLBACK(handler_res), pCh);

    // Attatch resolution
    gtk_grid_attach
    (
        GridCh[eCh],
        ResLabel[eCh],
        0, GRID_ORDER_RESOLUTION, 1, 1
    );
    
    gtk_grid_attach
    (
        GridCh[eCh],
        GTK_WIDGET(ResCombo[eCh]),
        1, GRID_ORDER_RESOLUTION, 1, 1
    );    
}

static void draw_framerate(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    FpsLabel[eCh] = gtk_label_new("Frame Rate: ");
    FpsCombo[eCh] = GTK_COMBO_BOX_TEXT(gtk_combo_box_text_new());

    gtk_combo_box_text_append_text
    (
        FpsCombo[eCh],
        "24"
    );
    gtk_combo_box_text_append_text
    (
        FpsCombo[eCh],
        "25"
    );
    gtk_combo_box_text_append_text
    (
        FpsCombo[eCh],
        "29.97"
    );
    gtk_combo_box_text_append_text
    (
        FpsCombo[eCh],
        "30"
    );
    gtk_combo_box_text_append_text
    (
        FpsCombo[eCh],
        "50"
    );
    gtk_combo_box_text_append_text
    (
        FpsCombo[eCh],
        "59.94"
    );
    gtk_combo_box_text_append_text
    (
        FpsCombo[eCh],
        "60"
    );
    
    gtk_combo_box_set_active(GTK_COMBO_BOX(FpsCombo[eCh]), 0);
    
    g_signal_connect(FpsCombo[eCh], "changed" , G_CALLBACK(handler_framerate), pCh);
    
    // Attatch framerate
    gtk_grid_attach
    (
        GridCh[eCh],
        FpsLabel[eCh],
        0, GRID_ORDER_FRAMERATE, 1, 1
    );

    gtk_grid_attach
    (
        GridCh[eCh],
        GTK_WIDGET(FpsCombo[eCh]),
        1, GRID_ORDER_FRAMERATE, 1, 1
    );
}

static void draw_bitrate(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    // Bitrate field
    BitrateLabel[eCh] = gtk_label_new("Bitrate (kbps): ");
    Bitrate[eCh]      = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1000.0, 32000.0, 1000.0);

    // Attach Bitrate
    gtk_grid_attach
    (
        GridCh[eCh],
        BitrateLabel[eCh],
        0, GRID_ORDER_BITRATE, 1, 1
    );

    gtk_grid_attach
    (
        GridCh[eCh],
        Bitrate[eCh],
        1, GRID_ORDER_BITRATE, 1, 1
    );
}

static void draw_bitdepth(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    // Bitdepth field
    BitdepthLabel[eCh] = gtk_label_new ("Bitdepth: ");
    Bitdepth8RadioButton[eCh] = gtk_radio_button_new_with_label(NULL, "8");
    Bitdepth10RadioButton[eCh] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(Bitdepth8RadioButton[eCh]), "10");
    
    // connect to signal
    g_signal_connect(Bitdepth8RadioButton[eCh],  "toggled", G_CALLBACK(handler_bitdepth), pCh);
    g_signal_connect(Bitdepth10RadioButton[eCh], "toggled", G_CALLBACK(handler_bitdepth), pCh);
    
    BitdepthBox[eCh] = gtk_box_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(BitdepthBox[eCh]), Bitdepth8RadioButton[eCh], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(BitdepthBox[eCh]), Bitdepth10RadioButton[eCh], FALSE, FALSE, 0);    

    // Attatch bitdepth
    gtk_grid_attach
    (
        GridCh[eCh],
        BitdepthLabel[eCh],
        0, GRID_ORDER_BITDEPTH, 1, 1
    );
    
    gtk_grid_attach
    (
        GridCh[eCh],
        BitdepthBox[eCh],
        1, GRID_ORDER_BITDEPTH, 1, 1
    );     
}

static void draw_chroma(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    // Chroma field
    ChromaLabel[eCh] = gtk_label_new("Chroma: ");
    Chroma420RadioButton[eCh] = gtk_radio_button_new_with_label(NULL, "420");
    Chroma422RadioButton[eCh] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(Chroma420RadioButton[eCh]), "422");
    
    // connect to signal
    g_signal_connect(Chroma420RadioButton[eCh], "toggled", G_CALLBACK(handler_chroma), pCh);
    g_signal_connect(Chroma420RadioButton[eCh], "toggled", G_CALLBACK(handler_chroma), pCh);
    
    ChromaBox[eCh] = gtk_box_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(ChromaBox[eCh]), Chroma420RadioButton[eCh], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(ChromaBox[eCh]), Chroma422RadioButton[eCh], FALSE, FALSE, 0);

    // Attatch chroma
    gtk_grid_attach
    (
        GridCh[eCh],
        ChromaLabel[eCh],
        0, GRID_ORDER_CHROMA, 1, 1
    );

    gtk_grid_attach
    (
        GridCh[eCh],
        ChromaBox[eCh],
        1, GRID_ORDER_CHROMA, 1, 1
    );
}

static void draw_pixfmt(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    // Pixel format field
    PixFmtLabel[eCh] = gtk_label_new("Pixel Fmt: ");
    PixFmtIntRadioButton[eCh] = gtk_radio_button_new_with_label(NULL, PIXEL_FMT_INTERLEAVE_TEXT);
    PixFmtPlaRadioButton[eCh] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(PixFmtIntRadioButton[eCh]), PIXEL_FMT_PLANAR_TEXT);
    
    // connect to signal
    //g_signal_connect(PixFmtIntRadioButton[eCh], "toggled", G_CALLBACK(handler_pixfmt), pCh);
    //g_signal_connect(PixFmtPlaRadioButton[eCh], "toggled", G_CALLBACK(handler_pixfmt), pCh);
    
    PixFmtBox[eCh] = gtk_box_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(PixFmtBox[eCh]), PixFmtIntRadioButton[eCh], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(PixFmtBox[eCh]), PixFmtPlaRadioButton[eCh], FALSE, FALSE, 0);

    // Attatch chroma
    gtk_grid_attach
    (
        GridCh[eCh],
        PixFmtLabel[eCh],
        0, GRID_ORDER_PIX_FMT, 1, 1
    );

    gtk_grid_attach
    (
        GridCh[eCh],
        PixFmtBox[eCh],
        1, GRID_ORDER_PIX_FMT, 1, 1
    );
}

static void draw_gop(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    // GOP field
    GopLabel[eCh] = gtk_label_new("GOP: ");
    GopIbRadioButton[eCh]   = gtk_radio_button_new_with_label(NULL, "IB");
    GopIpRadioButton[eCh]   = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(GopIbRadioButton[eCh]), "IP");
    GopIpbRadioButton[eCh]  = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(GopIbRadioButton[eCh]), "IPB");
    GopIRadioButton[eCh]    = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(GopIbRadioButton[eCh]), "I");
    
    // connect to signal
    g_signal_connect(GopIbRadioButton[eCh],  "toggled", G_CALLBACK(handler_gop), pCh);
    g_signal_connect(GopIpRadioButton[eCh],  "toggled", G_CALLBACK(handler_gop), pCh);
    g_signal_connect(GopIpbRadioButton[eCh], "toggled", G_CALLBACK(handler_gop), pCh);
    g_signal_connect(GopIRadioButton[eCh],   "toggled", G_CALLBACK(handler_gop), pCh);
    
    GopBox[eCh] = gtk_box_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(GopBox[eCh]), GopIbRadioButton[eCh], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(GopBox[eCh]), GopIpRadioButton[eCh], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(GopBox[eCh]), GopIpbRadioButton[eCh], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(GopBox[eCh]), GopIRadioButton[eCh],  FALSE, FALSE, 0);
    
    // Attatch GOP
    gtk_grid_attach
    (
        GridCh[eCh],
        GopLabel[eCh],
        0, GRID_ORDER_GOP, 1, 1
    );    

    gtk_grid_attach
    (
        GridCh[eCh],
        GopBox[eCh],
        1, GRID_ORDER_GOP, 1, 1
    ); 
}

static void draw_gop_size(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    GopSizeLabel[eCh] = gtk_label_new("GOP Size: ");
    GopSizeEntry[eCh] = gtk_entry_new();

    gtk_entry_set_text(GTK_ENTRY(GopSizeEntry[eCh]), "64");

    // Attatch GOP size
    gtk_grid_attach
    (
        GridCh[eCh],
        GopSizeLabel[eCh],
        0, GRID_ORDER_GOP_SIZE, 1, 1
    );
    
    gtk_grid_attach
    (
        GridCh[eCh],
        GopSizeEntry[eCh],
        1, GRID_ORDER_GOP_SIZE, 1, 1
    );     
}

static void draw_idr_interval(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    IdrIntervalLabel[eCh] = gtk_label_new("IDR Interval: ");
    IdrIntervalEntry[eCh] = gtk_entry_new();

    gtk_entry_set_text(GTK_ENTRY(IdrIntervalEntry[eCh]), "0");

    // Attatch GOP size
    gtk_grid_attach
    (
        GridCh[eCh],
        IdrIntervalLabel[eCh],
        0, GRID_ORDER_IDR_INTERVAL, 1, 1
    );

    gtk_grid_attach
    (
        GridCh[eCh],
        IdrIntervalEntry[eCh],
        1, GRID_ORDER_IDR_INTERVAL, 1, 1
    );     
}

static void draw_b_frame_num(API_VENC_CHN_E *pCh)
{
    API_VENC_CHN_E eCh = *pCh;

    // Ref frame number
    BNumLabel[eCh] = gtk_label_new("B frame #: ");
    BNumScale[eCh] = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1.0, 8.0, 1.0);
    
    // Attatch ref
    gtk_grid_attach
    (
        GridCh[eCh],
        BNumLabel[eCh],
        0, GRID_ORDER_BNUM, 1, 1
    );
    
    gtk_grid_attach
    (
        GridCh[eCh],
        BNumScale[eCh],
        1, GRID_ORDER_BNUM, 1, 1
    ); 
}

static void draw_run(API_VENC_CHN_E eCh)
{
    EncodeButton[eCh] = gtk_button_new_with_label("Run");

    tEncodeParam[eCh].eCh = eCh;
    tEncodeParam[eCh].window = window;
    g_signal_connect(EncodeButton[eCh], "clicked", G_CALLBACK(handler_run), &tEncodeParam[eCh]);

    // Attach encode
    gtk_grid_attach
    (
        GridCh[eCh],
        EncodeButton[eCh],
        0, GRID_ORDER_ENCODE + eCh * 2, 1, 1
    );
}

static void draw_open(GtkWidget *window, API_VENC_CHN_E eCh)
{
    OpenButton[eCh] = gtk_button_new_with_label("Open ...");

    tOpenParam[eCh].eCh = eCh;
    tOpenParam[eCh].window = window;

    g_signal_connect(OpenButton[eCh], "clicked", G_CALLBACK(handler_open), &tOpenParam[eCh]);

    // Attach open
    gtk_grid_attach
    (
        GridCh[eCh],
        OpenButton[eCh],
        0, GRID_ORDER_OPEN + eCh * 2, 2, 1
    );
}

static void draw_bar(API_VENC_CHN_E eCh)
{    
    ProgressBar[eCh] = gtk_progress_bar_new();

    // Attach open
    gtk_grid_attach
    (
        GridCh[eCh],
        ProgressBar[eCh],
        1, GRID_ORDER_BAR + eCh * 2, 2, 1
    );
}

int main(int argc, char *argv[])
{
    ui_logging = fopen("log_ui.txt", "w");
    __hvc_encoder_logging__ = fopen("log_api.txt", "w");
 
    gtk_init(&argc, &argv);
 
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "VEGA-330X");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 150, 100);

    notebook = GTK_NOTEBOOK(gtk_notebook_new());

    Label1  = gtk_label_new("Channel 1");
    Label2  = gtk_label_new("Channel 2");
    Label3  = gtk_label_new("About");

    GridCh[eCh1] = GTK_GRID(gtk_grid_new());
    GridCh[eCh2] = GTK_GRID(gtk_grid_new());
    GridAbout    = GTK_GRID(gtk_grid_new());

    // Create Channel 1 panel
    draw_profile(&eCh1);
    draw_level(&eCh1);
    draw_tier(&eCh1);
    draw_res(&eCh1);
    draw_framerate(&eCh1);
    draw_bitrate(&eCh1);
    draw_bitdepth(&eCh1);
    draw_chroma(&eCh1);
    draw_pixfmt(&eCh1);
    draw_gop(&eCh1);
    draw_gop_size(&eCh1);
    draw_idr_interval(&eCh1);
    draw_b_frame_num(&eCh1);

    draw_run(eCh1);
    draw_open(window, eCh1);
    draw_bar(eCh1);

    // Create Channel 2 panel
    draw_profile(&eCh2);
    draw_level(&eCh2);
    draw_tier(&eCh2);
    draw_res(&eCh2);
    draw_framerate(&eCh2);
    draw_bitrate(&eCh2);
    draw_bitdepth(&eCh2);
    draw_chroma(&eCh2);
    draw_pixfmt(&eCh2);
    draw_gop(&eCh2);
    draw_gop_size(&eCh2);
    draw_idr_interval(&eCh2);
    draw_b_frame_num(&eCh2);

    draw_run(eCh2);
    draw_open(window, eCh2);
    draw_bar(eCh2);

    // Create About panel
    CopyRight   = gtk_label_new("Copyright (C) 2015 Advantech Co.");
    ApiLabel    = gtk_label_new("API Version:");
    DrvLabel    = gtk_label_new("DRV Version:");
    SysFwLabel  = gtk_label_new("System FW version:");
    McpuLabel   = gtk_label_new("MCPU FW version:");
    FwSingleLabel = gtk_label_new("Single FW version:");
    FwMultiLabel = gtk_label_new("Multi FW version:");

    API_VENC_VERSION_INFO_T t_ver;

    memset(&t_ver, 0, sizeof(t_ver));
    Api_VENC_GetVersion(0, &t_ver);
    char str_api_ver[255];
    sprintf(str_api_ver, "%d.%d.%d.%d", 
        t_ver.u32KernelVer, t_ver.u32MajorVer, t_ver.u32MinorVer, t_ver.u32SvnVer);
    ApiVersion      = gtk_label_new(str_api_ver);
    DrvVersion      = gtk_label_new(t_ver.u8Driver);
    SysFwVersion    = gtk_label_new(t_ver.u8SystemFirm);
    char str_mcpu_ver[255];
    sprintf(str_mcpu_ver, "%d.%d.%d.%d", 
        t_ver.u32McpuKernelVer, t_ver.u32McpuMajorVer, t_ver.u32McpuMinorVer, t_ver.u32McpuExtraVer);
    McpuVersion     = gtk_label_new(str_mcpu_ver);
    FwSingleVersion = gtk_label_new(t_ver.u8HevcEncoderStdFirmSingle);
    FwMultiVersion = gtk_label_new(t_ver.u8HevcEncoderStdFirmMulti);

    gtk_grid_attach
    (
        GridAbout,
        CopyRight,
        0, 0, 2, 1
    );    
    gtk_grid_attach
    (
        GridAbout,
        ApiLabel,
        0, 1, 1, 1
    );  
    gtk_grid_attach
    (
        GridAbout,
        ApiVersion,
        1, 1, 1, 1
    ); 
    gtk_grid_attach
    (
        GridAbout,
        DrvLabel,
        0, 2, 1, 1
    );  
    gtk_grid_attach
    (
        GridAbout,
        DrvVersion,
        1, 2, 1, 1
    ); 
    gtk_grid_attach
    (
        GridAbout,
        SysFwLabel,
        0, 3, 1, 1
    ); 
    gtk_grid_attach
    (
        GridAbout,
        SysFwVersion,
        1, 3, 1, 1
    ); 
    gtk_grid_attach
    (
        GridAbout,
        McpuLabel,
        0, 4, 1, 1
    ); 
    gtk_grid_attach
    (
        GridAbout,
        McpuVersion,
        1, 4, 1, 1
    ); 
    gtk_grid_attach
    (
        GridAbout,
        FwSingleLabel,
        0, 5, 1, 1
    ); 
    gtk_grid_attach
    (
        GridAbout,
        FwSingleVersion,
        1, 5, 1, 1
    );
    gtk_grid_attach
    (
        GridAbout,
        FwMultiLabel,
        0, 6, 1, 1
    ); 
    gtk_grid_attach
    (
        GridAbout,
        FwMultiVersion,
        1, 6, 1, 1
    );

    /* Append to pages to the notebook container. */
    gtk_notebook_append_page(notebook, GTK_WIDGET(GridCh[eCh1]), Label1);
    gtk_notebook_append_page(notebook, GTK_WIDGET(GridCh[eCh2]), Label2);
    gtk_notebook_append_page(notebook, GTK_WIDGET(GridAbout), Label3);


    /* Add five pixels of spacing between every row and every column. */
    gtk_grid_set_row_spacing(GridCh[eCh1], 5);
    gtk_grid_set_row_spacing(GridCh[eCh2], 5);
    gtk_grid_set_row_spacing(GridAbout, 5);

    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(notebook));
    gtk_widget_show_all(window);
    
    gtk_main();
    
    fclose(ui_logging);
    fclose(__hvc_encoder_logging__);
    
    return 0;
}

