enum {

	LIST_ITEM = 0,
	N_COLUMNS
};


void select_item(GtkWidget *widget, gpointer selection) {
	GtkListStore *store;
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkTreePath * path ;
	gchar *value;
	int *i;
	int selecionado ;
	int Sts ;
	char *str[10];

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));
	if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) {
		return;
	}
	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), 		&model, &iter)) {
		path = gtk_tree_model_get_path ( model , &iter ) ;
		i = gtk_tree_path_get_indices ( path ) ;
		gtk_tree_model_get(model, &iter, LIST_ITEM, &value,  -1);
		selecionado =  (i[0]+1) ;
		sprintf(str, "%d", selecionado);
		EscondeTreeviewGlade();
		
		 //printf("%s SELECIONADO NA LISTA \n", str );
		do{
		Sts = ContinuaSitef(str);

	}while (Sts == 10000);
	 

			
	}
}

// gtk_tree_model_get(model, &iter, LIST_ITEM, &value,  -1);
  //// printf("Selecionou %s\n", value );


void remove_all() {

	GtkListStore *store;
	GtkTreeModel *model;
	GtkTreeIter  iter;
	GtkTreeSelection *selection; 
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));
	if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) {
		return;
	}
	gtk_list_store_clear(store);
}

void init_list(GtkWidget *list) {

	GtkCellRenderer    *renderer;
	GtkTreeViewColumn  *column;
	GtkListStore       *store;

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("List Item",	renderer, "text", LIST_ITEM, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

	store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

	g_object_unref(store);
}

void add_to_list(GtkWidget *list, const gchar *str) {

	GtkListStore *store;
	GtkTreeIter iter;

	store = GTK_LIST_STORE(gtk_tree_view_get_model
		(GTK_TREE_VIEW(list)));

	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
	
}


int MenuTreeview (char *pOpcoes, char *pEscolha)
{
	EscondeTelaInicial();
	TelaTreeview();
	remove_all();
	int init_size = strlen(pEscolha);
	char delim[] = ";";
	char *ptr = strtok(pEscolha, delim);
	while (ptr != NULL) 
	{
		add_to_list(list,ptr);
		ptr = strtok(NULL, delim);
	}	

	}
