// FUNC_NAME: Entity::Entity
// Address: 0x00549b60
// Role: Constructor for Entity class (EARS engine base object). Sets vtable, initializes fields.

#include <cstdint>

// Forward declaration of global data
extern uint32_t g_someGlobal; // DAT_00e2eff4

// External function (likely internal init)
void initializeObject(); // FUN_00a64fd0

class Entity {
public:
    // Fields reconstructed from offsets
    void* vtable;            // +0x00: virtual function table pointer (set from param2)
    int32_t someHandle;      // +0x04: initialized to -1
    int32_t someParam;       // +0x08: set from param3
    int32_t field_0C;        // +0x0C: zero
    uint8_t field_10;        // +0x10: zero
    int32_t field_14;        // +0x14: zero
    uint8_t field_18;        // +0x18: set from param4 (byte)
    int32_t field_1C;        // +0x1C: zero
    uint16_t field_1A;       // +0x1A: zero (overlaps with field_19? careful)
    // Note: fields at 0x11, 0x12, 0x19 might be packed
    uint8_t field_19;        // +0x19: set twice (0x7f then 0xec)
    uint8_t field_11;        // +0x11: zero
    uint16_t field_12;       // +0x12: zero
    // Additional fields up to 0x48
    int32_t globalRef;       // +0x48: set from global

    // Constructor
    Entity(void* vtablePtr, int32_t param3, uint8_t param4) {
        // Set vtable
        this->vtable = vtablePtr;

        // Initialize fields
        this->someHandle = -1;
        this->someParam = param3;
        this->field_0C = 0;
        this->field_10 = 0;
        this->field_14 = 0;
        this->field_18 = param4;
        this->field_1C = 0;

        // Packed byte/word region
        *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x1A) = 0; // word at +0x1A
        *reinterpret_cast<uint8_t*>(this) + 0x19 = 0x7f; // byte at +0x19

        // Call internal initialization
        initializeObject();

        // Overwrite some flags after init
        *reinterpret_cast<uint8_t*>(this) + 0x19 = 0xec;
        *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x12) = 0; // word at +0x12
        *reinterpret_cast<uint8_t*>(this) + 0x11 = 0;

        // Set the global reference
        this->globalRef = g_someGlobal;
    }
};

// Note: The actual class definition would have more members and possibly bitfields.
// The offsets above simulate the writes seen in the decompilation.