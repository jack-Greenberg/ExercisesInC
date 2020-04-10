#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <gio/gio.h>

void print_hash_table(gpointer key, gpointer value, gpointer user_data) {
    char* read_key = key;
    printf("%s: %i,\n", read_key, GPOINTER_TO_INT(value));
}

int main() {
	GHashTable * hash_table = g_hash_table_new(g_str_hash, g_str_equal);
    GScanner * scanner = g_scanner_new(NULL);
    FILE * fp;
   
    fp = fopen("test.txt", "r+");
    gint file = fileno(fp);
    g_scanner_input_file(scanner, file);

    while(!g_scanner_eof(scanner)) {
        g_scanner_get_next_token(scanner);

        if (scanner->value.v_string) {
            if (!g_hash_table_lookup(hash_table, scanner->value.v_string)) {
                g_hash_table_insert(hash_table, g_strdup(scanner->value.v_string), GINT_TO_POINTER(1));
            } else {
                g_hash_table_insert(hash_table, g_strdup(scanner->value.v_string), g_hash_table_lookup(hash_table, scanner->value.v_string) + 1);
            }
        }
    }

    g_hash_table_foreach(hash_table, print_hash_table, NULL);

    return 0;
}
