// FUNC_NAME: Entity::Entity

#include <cstdint>

// Forward declaration of base constructor
void BaseClassConstructor(void* thisPtr);

// Global constant used for initialization
extern const uint32_t DAT_00d5780c;
extern void* PTR_LAB_00d7340c; // vtable pointer

class Entity {
public:
    void** vtable; // +0x00

    // Constructor function at 0x00822f30
    // Initializes a large array of slots starting at offset 0x50 (0x14 dwords)
    static Entity* __fastcall Entity(Entity* thisObject);
};

Entity* __fastcall Entity::Entity(Entity* thisObject) {
    BaseClassConstructor(thisObject);

    uint32_t defaultValue = DAT_00d5780c; // e.g., 0xFFFFFFFF or some sentinel

    // Override vtable pointer set by base constructor
    thisObject->vtable = &PTR_LAB_00d7340c;

    // Access the slot array as uint32_t* starting at offset 0x50 (i.e., this + 0x14 dwords)
    uint32_t* slots = reinterpret_cast<uint32_t*>(thisObject) + 0x14;

    // Slot 0 (offset 0x14)
    slots[0] = defaultValue;
    slots[1] = 0;
    slots[2] = 0;
    slots[3] = 0;
    slots[4] = 0;

    // Slot 1 (offset 0x19)
    slots[5] = defaultValue;
    slots[6] = 0;
    slots[7] = 0;
    slots[8] = 0;
    slots[9] = 0;

    // Slot 2 (offset 0x1e)
    slots[10] = defaultValue;
    slots[11] = 0;
    slots[12] = 0;
    slots[13] = 0;
    slots[14] = 0;

    // Slot 3 (offset 0x23) – two consecutive default values
    slots[15] = defaultValue;
    slots[16] = defaultValue;
    slots[17] = 0;
    slots[18] = 0;
    slots[19] = 0;
    slots[20] = 0;

    // Slot 4 (offset 0x29)
    slots[21] = defaultValue;
    slots[22] = 0;
    slots[23] = 0;
    slots[24] = 0;
    slots[25] = 0;

    // Slot 5 (offset 0x2e)
    slots[26] = defaultValue;
    slots[27] = 0;
    slots[28] = 0;
    slots[29] = 0;
    slots[30] = 0;

    // Slot 6 (offset 0x33) – two consecutive default values
    slots[31] = defaultValue;
    slots[32] = defaultValue;
    slots[33] = 0;
    slots[34] = 0;
    slots[35] = 0;
    slots[36] = 0;

    // Slot 7 (offset 0x39)
    slots[37] = defaultValue;
    slots[38] = 0;
    slots[39] = 0;
    slots[40] = 0;
    slots[41] = 0;

    // Slot 8 (offset 0x3e)
    slots[42] = defaultValue;
    slots[43] = 0;
    slots[44] = 0;
    slots[45] = 0;
    slots[46] = 0;

    // Slot 9 (offset 0x43) – last slot, only one value
    slots[47] = defaultValue;

    return thisObject;
}