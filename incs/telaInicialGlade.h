GtkWidget *confirmar;
GtkWidget *vbox;
GtkWidget *hbox;
GtkTreeSelection *selection;
GtkWidget *inicialWindow;
GtkWidget *labelInicial;
GtkWidget *entry;
GtkWidget *btnConfirmar;
gint timeout;
int Sts = 0;

GdkColor color;

// void on_window_main_show(GtkWidget *widget, char *file)
// {

// }

void iniciarTransacao()
{
    g_source_remove(timeout);
    //printf("INIICAR TRANSACAO\n\n");
    int StS = 0;
    //printf("%s\n", pIpSiTef);
    //printf("%s\n", pEmpresa);
    //printf("%s\n", pTerminal);

    StS = iniciarSitef(pIpSiTef, pEmpresa, pTerminal);

    ChamaDll(0);
    //printf("%s\n", pTerminal);
    do
    {
        //printf("%s\n", pTerminal);
        StS = ContinuaSitef("-1");
    } while (StS == 10000);
}

static void confirmarEntry(GtkWidget *widget, gpointer selection)
{
    const gchar *entry_text;
    entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    Sts = ContinuaSitef(entry_text);
    ////printf("Inicial STS NO ENTER %i\n" , Sts);
    while (Sts == 10000)
    {
        // //printf("Inicial STS NO ENTER %i\n" , Sts);
        Sts = ContinuaSitef("-1");
        //printf("Inicial ContinuaSitef STS NO ENTER %i\n" , Sts);
    }
}

static void enter_callback(GtkWidget *widget, GtkWidget *entry)
{

    ////printf("Inicial STS NO ENTER %i\n" , Sts);
    const gchar *entry_text;
    entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    Sts = ContinuaSitef(entry_text);
    ////printf("Inicial STS NO ENTER %i\n" , Sts);
    while (Sts == 10000)
    {
        // //printf("Inicial STS NO ENTER %i\n" , Sts);
        Sts = ContinuaSitef("-1");
        //printf("Inicial ContinuaSitef STS NO ENTER %i\n" , Sts);
    }
}

void TelaInicial()
{
    inicialWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(inicialWindow), "SITEF E-POC V2");
    gtk_window_set_position(GTK_WINDOW(inicialWindow), GTK_WIN_POS_CENTER);
    // gtk_window_set_decorated(GTK_WINDOW(inicialWindow), false);
    gtk_container_set_border_width(GTK_CONTAINER(inicialWindow), 10);
    gtk_widget_set_size_request(inicialWindow, 600, 100);
    gtk_window_set_resizable(GTK_WINDOW(inicialWindow), FALSE);
    gtk_window_set_keep_above(GTK_WINDOW(inicialWindow), TRUE);
    labelInicial = gtk_label_new("BEM VINDO AO SITEF ");
    gtk_widget_modify_font(labelInicial, pango_font_description_from_string("Monospace 10"));

    if (gdk_color_parse("#FFFF00", &color))
    {

        gtk_widget_modify_bg(inicialWindow, GTK_STATE_NORMAL, &color);
    }
    else
    {
        // set default color
    }
    vbox = gtk_vbox_new(TRUE, 0);
    //vbox = gtk_vbox(GTK_ORIENTATION_VERTICAL, 0);
    hbox = gtk_hbox_new(TRUE, 2);
    //hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);

    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), 50);
    g_signal_connect(entry, "activate",
                     G_CALLBACK(enter_callback),
                     entry);
    gtk_entry_set_text(GTK_ENTRY(entry), "");

    confirmar = gtk_button_new_with_label("Confirmar");

    g_signal_connect(G_OBJECT(confirmar), "clicked", G_CALLBACK(confirmarEntry), 1);

    //  tmp_pos = GTK_ENTRY (entry)->text_length;
    gtk_box_pack_start(GTK_BOX(hbox), labelInicial, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 3);
    //   gtk_box_pack_start(GTK_BOX(hbox), confirmar, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), confirmar, TRUE, TRUE, 1);
    gtk_container_add(GTK_CONTAINER(inicialWindow), vbox);
    g_signal_connect(G_OBJECT(inicialWindow), "destroy", G_CALLBACK(DestruirTela), NULL);
    // g_signal_connect(G_OBJECT(inicialWindow), "show", G_CALLBACK(on_window_main_show), "file.ini");
    gtk_widget_show(inicialWindow);
    while (gtk_events_pending())
    {
        gtk_main_iteration();
    }
    gtk_widget_hide(entry);
    gtk_widget_hide(confirmar);
    timeout = g_timeout_add(250, (GSourceFunc)iniciarTransacao, NULL);
}

void MostrarTelaInicial(int input, char *msg)
{
    gtk_widget_show_all(inicialWindow);
    while (gtk_events_pending())
    {
        gtk_main_iteration();
    }
    if (input == 1)
    {
        gtk_entry_set_max_length(GTK_ENTRY(entry), TamanhoMaximo);
        gtk_label_set_text(GTK_LABEL(labelInicial), msg);
        gtk_entry_set_text(GTK_ENTRY(entry), "");
        gtk_widget_grab_focus(GTK_ENTRY(entry));
        //printf("\nMENSAGEM NO ENTRY= %s\n" , msg);

        gtk_widget_show(entry);
        gtk_widget_show(confirmar);
    }
    else
    {
        gtk_widget_hide(entry);
        gtk_widget_hide(confirmar);
    }
}

void EscondeTelaInicial()
{
    gtk_widget_hide_all(inicialWindow);
    while (gtk_events_pending())
    {
        gtk_main_iteration();
    }
}
