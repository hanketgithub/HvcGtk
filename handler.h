#ifndef ___HANDLER_H___
#define ___HANDLER_H___

void handler_profile(GtkWidget *widget, gpointer *data);

void handler_level(GtkWidget *widget, gpointer *data);

void handler_tier(GtkWidget *widget, gpointer *data);

void handler_res(GtkWidget *widget, gpointer *data);

void handler_framerate(GtkWidget *widget, gpointer *data);

void handler_bitdepth(GtkWidget *widget, gpointer *data);

void handler_chroma(GtkWidget *widget, gpointer *data);

void handler_pixfmt(GtkWidget *widget, gpointer *data);

void handler_gop(GtkWidget *widget, gpointer *data);

void handler_run(GtkWidget *button, ENCODE_CALLBACK_PARAM_T *param);

void handler_open(GtkWidget *button, OPEN_CALLBACK_PARAM_T *param);

#endif

