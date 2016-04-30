
//erstmal als einfach verkettete Liste implementiert
//wenn jemand zu viel Zeit hat, bitte als AVL-Baum implementieren

struct dict;


struct dict *new_dict();
void del_dict(struct dict *dict);

void dict_add(struct dict *dict, int key, void *value);
void dict_remove(struct dict *dict, int key);

void *dict_get(struct dict *dict, int key);
void dict_set(struct dict *dict, int key, void *value);
