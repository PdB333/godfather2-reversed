// FUN_004e4040: findObjectByID
typedef struct {
    int field_0;
    int field_4;
    int id; // +0x8
} ObjectStruct;

extern int g_objectCount; // DAT_011946b4
extern ObjectStruct* g_objectArray[]; // DAT_011946b8

ObjectStruct* findObjectByID(int id) {
    for (int i = 0; i < g_objectCount; i++) {
        if (g_objectArray[i]->id == id) {
            return g_objectArray[i];
        }
    }
    return nullptr;
}