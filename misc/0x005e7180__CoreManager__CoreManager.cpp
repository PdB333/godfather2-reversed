// FUNC_NAME: CoreManager::CoreManager

class CoreManager {
public:
    void** vtable;        // +0x00
    int data[4];          // +0x04
    int field_14;         // +0x14
    uint8_t flags[4];     // +0x18
    uint8_t type;         // +0x1C
    uint8_t subType;      // +0x1D
};

extern CoreManager* g_coreManager; // DAT_01223504
extern void* PTR_LAB_00e3f6d4;     // vtable reference

void __thiscall CoreManager::CoreManager(CoreManager* this) {
    g_coreManager = this;

    this->vtable = &PTR_LAB_00e3f6d4;
    this->field_14 = 0;
    this->type = 4;      // default state
    this->subType = 0;

    for (int i = 0; i < 4; i++) {
        this->data[i] = 0;
        this->flags[i] = 0;
    }

    return;
}