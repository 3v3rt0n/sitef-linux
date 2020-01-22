GtkWidget *sw;
GtkWidget *add;
GtkWidget *vbox;
GtkWidget *hbox;
GtkTreeSelection *selection;
GtkWidget *treeviewWindow;
GtkWidget *labelTreeview;
GtkWidget *list;

    GdkColor color;
void quit_app();
void select_item(GtkWidget *widget, gpointer selection) ;


void  TelaTreeview() 
{
    treeviewWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(treeviewWindow), "SITEF E-POC V2");
      if (gdk_color_parse("#FFFF00", &color)) {
       
    gtk_widget_modify_bg(treeviewWindow, GTK_STATE_NORMAL, &color);
} else {
    // set default color
}
    gtk_window_set_position(GTK_WINDOW(treeviewWindow), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(treeviewWindow), 10);
        gtk_widget_set_size_request(treeviewWindow , 400, 300);
    gtk_window_set_resizable(GTK_WINDOW(treeviewWindow), FALSE);
    gtk_window_set_keep_above(GTK_WINDOW(treeviewWindow), TRUE);
    sw = gtk_scrolled_window_new(NULL, NULL);
    list = gtk_tree_view_new();
    gtk_container_add(GTK_CONTAINER(sw), list);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw), GTK_SHADOW_ETCHED_IN);
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);
    vbox = gtk_vbox_new(FALSE, 0);
    //vbox = gtk_vbox(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), sw, TRUE, TRUE, 5);
    hbox = gtk_hbox_new(FALSE, 2);
    //hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    add = gtk_button_new_with_label("Selecionar");
    gtk_box_pack_start(GTK_BOX(hbox), add, TRUE, TRUE, 3);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 3);
    gtk_container_add(GTK_CONTAINER(treeviewWindow), vbox);
    init_list(list);
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
    g_signal_connect(G_OBJECT(add), "clicked", G_CALLBACK(select_item), selection);
    g_signal_connect(G_OBJECT(treeviewWindow), "destroy", G_CALLBACK(DestruirTela), NULL);
    gtk_widget_show_all(treeviewWindow); 
} 


void MostrarTreeviewGlade(){
    	
gtk_widget_show_all(treeviewWindow);
while (gtk_events_pending())
	{
		gtk_main_iteration();
	}

}

void EscondeTreeviewGlade(){
    	
gtk_widget_hide_all(treeviewWindow);
while (gtk_events_pending())
	{
		gtk_main_iteration();
	}

}
