 #gcc ini.c main.c -o ../../sitef `pkg-config --libs --cflags gtk+-2.0` -Wint-conversion  -lclisitef -rdynamic
 
 gcc ini.c main.c -o /usr/local/bin/sitef `pkg-config --libs --cflags gtk+-2.0` -Wdiscarded-qualifiers -Wimplicit-function-declaration -Wint-conversion  -lclisitef -rdynamic $(mysql_config --cflags)  $(mysql_config --libs) 
