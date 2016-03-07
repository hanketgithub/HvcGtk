#include <gtk/gtk.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "libhvc_venc/HVC_types.h"
#include "HvcGtk.h"

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
    
    if (strcmp(val, "Main") == 0)
    {
        tApiHvcInitParam[eCh].eProfile = API_HVC_HEVC_MAIN_PROFILE;
    }
    else if (strcmp(val, "Main10") == 0)
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
    
    if (strcmp(val, "4.0") == 0)
    {
        tApiHvcInitParam[eCh].eLevel = API_HVC_HEVC_LEVEL_40;
    }
    else if (strcmp(val, "4.1") == 0)
    {
        tApiHvcInitParam[eCh].eLevel = API_HVC_HEVC_LEVEL_41;
    }
    else if (strcmp(val, "5.0") == 0)
    {
        tApiHvcInitParam[eCh].eLevel = API_HVC_HEVC_LEVEL_50;
    }
    else if (strcmp(val, "5.1") == 0)
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
    
    if (strcmp(val, "Main") == 0)
    {
        tApiHvcInitParam[eCh].eTier = API_HVC_HEVC_MAIN_TIER;
    }
    else if (strcmp(val, "High") == 0)
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

    if (strcmp(val, "3840x2160") == 0)
    {
        tApiHvcInitParam[eCh].eResolution = API_HVC_RESOLUTION_3840x2160;
    }
    else if (strcmp(val, "1920x1080") == 0)
    {
        tApiHvcInitParam[eCh].eResolution = API_HVC_RESOLUTION_1920x1080;
    }
    else if (strcmp(val, "1280x720") == 0)
    {
        tApiHvcInitParam[eCh].eResolution = API_HVC_RESOLUTION_1280x720;
    }
    else if (strcmp(val, "720x576") == 0)
    {
        tApiHvcInitParam[eCh].eResolution = API_HVC_RESOLUTION_720x576;
    }
    else if (strcmp(val, "720x480") == 0)
    {
        tApiHvcInitParam[eCh].eResolution = API_HVC_RESOLUTION_720x480;
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
    
    list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(PixFmtNV12RadioButton[eCh]));
    
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

void handler_gop(GtkWidget *widget, gpointer *data)
{
    GSList *list; 
    GtkToggleButton *button = NULL;
    API_HVC_CHN_E eCh = (API_HVC_CHN_E) *data;
    
    list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(GopIbRadioButton));
    
    while (list) // As long as we didn't reach the end of the group.
    {
        button = list->data;    // Get one of the buttons in the group.
        list = list->next;      // Next time we're going to check this one.

        if (gtk_toggle_button_get_active(button))
        {
            break;
        }
    }
    
    const char *val = gtk_button_get_label(GTK_BUTTON(button));

    if (strcmp(val, "IP") == 0)
    {
        tApiHvcInitParam[eCh].eGopType = API_HVC_GOP_IP;
        gtk_widget_set_sensitive(GTK_WIDGET(BNumScale), FALSE);
    }
    else if (strcmp(val, "IB") == 0)
    {
        tApiHvcInitParam[eCh].eGopType = API_HVC_GOP_IB;
        gtk_widget_set_sensitive(GTK_WIDGET(BNumScale), TRUE);
    }
    else if (strcmp(val, "IPB") == 0)
    {
        tApiHvcInitParam[eCh].eGopType = API_HVC_GOP_IPB;
        gtk_widget_set_sensitive(GTK_WIDGET(BNumScale), TRUE);
    }
    else if (strcmp(val, "I") == 0)
    {
        tApiHvcInitParam[eCh].eGopType       = API_HVC_GOP_I;
        tApiHvcInitParam[eCh].eGopSize       = API_HVC_GOP_SIZE_1;
        tApiHvcInitParam[eCh].eIDRFrameNum   = API_HVC_IDR_FRAME_ALL;
        tApiHvcInitParam[eCh].eBFrameNum     = API_HVC_B_FRAME_NONE;
        gtk_widget_set_sensitive(GTK_WIDGET(BNumScale), FALSE); 
    }
    
    LOG("%s: %s selected\n", __FUNCTION__, val);
}

