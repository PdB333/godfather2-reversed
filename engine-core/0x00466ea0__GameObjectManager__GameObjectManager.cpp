// FUNC_NAME: GameObjectManager::GameObjectManager
// Address: 0x00466ea0
// Purpose: Constructor for a game object manager that allocates a fixed-size array of 127 object slots (0x54 bytes each).
//          Initializes slot data, sets up virtual function table pointers (multiple inheritance), and stores singleton pointer.

class GameObjectManager
{
public:
    // Virtual table pointers at offsets 0, 4, 16 (likely for multiple inheritance or interface)
    void** vtable1;       // +0x00
    void** vtable2;       // +0x04
    uint32_t field_8;     // +0x08
    uint32_t field_C;     // +0x0C
    void** vtable3;       // +0x10 (offset 16)
    // Array of 127 slots, each of size 0x54 bytes
    // Offset 0x14 (20) to 0x14 + 127*0x54 = 0x29C0
    GameObjectSlot slots[127]; // +0x14
    uint32_t slotCount;      // +0x2A14 (index 0xA85 * 4 = 0x2A14)
    uint32_t somethingCount; // +0x2A18 (index 0xA86 * 4)
    // Additional fields beyond
};

// Size of each slot: 0x54 bytes, contains:
struct GameObjectSlot
{
    uint32_t field_00;  // +0x00 (zeroed as a word)
    uint32_t field_04;  // +0x04 (zeroed)
    uint32_t field_08;  // +0x08 (zeroed)
    uint8_t field_0C;   // +0x0C (zeroed)
    uint8_t field_4D;   // +0x4D (set to 1)
    uint8_t field_4E;   // +0x4E (set to 0)
    // ... remaining bytes
};

// Global singleton pointer
static GameObjectManager* g_gameObjectManager = nullptr; // DAT_0122346c

// Constructor
// __fastcall with this in ECX
GameObjectManager* __fastcall GameObjectManager::GameObjectManager(GameObjectManager* thisObj)
{
    // Set up initial virtual tables (likely base class vtable pointers)
    thisObj->vtable2 = &PTR_FUN_00e2f19c;
    thisObj->field_8 = 1;
    thisObj->field_C = 0;
    thisObj->vtable3 = &PTR_LAB_00e31f18;

    // Store global singleton
    g_gameObjectManager = thisObj;

    // Set final virtual table pointers (overwrites previous)
    thisObj->vtable1 = &PTR_FUN_00e31ef8;
    thisObj->vtable2 = &PTR_LAB_00e31f04;
    thisObj->vtable3 = &PTR_LAB_00e31f14;

    // Initialize array of slots
    uint32_t* slotBase = reinterpret_cast<uint32_t*>(thisObj) + 5; // +0x14
    for (int i = 0; i < 0x7F; i++)
    {
        // Zero first three words (12 bytes)
        slotBase[0] = 0;
        slotBase[1] = 0;
        slotBase[2] = 0;

        // Set byte at offset 0x4C to 0
        *reinterpret_cast<uint8_t*>(slotBase + 0x13) = 0; // 0x13 * 4 = 0x4C

        // Set byte at offset 0x4D to 1
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(slotBase) + 0x4D) = 1;

        // Set byte at offset 0x4E to 0
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(slotBase) + 0x4E) = 0;

        // Set byte at offset 12 (from start of slot) to 0
        *reinterpret_cast<uint8_t*>(slotBase + 3) = 0; // slotBase+3 is at byte offset 12

        // Advance to next slot (each slot is 0x54 = 21 * 4 bytes)
        slotBase += 0x15; // 21 dwords
    }

    // Set additional counters after the array
    thisObj->slotCount = 0; // at +0x2A14
    thisObj->somethingCount = 0; // at +0x2A18

    // Call base class constructor or additional initialization
    FUN_0043e2e0(thisObj);

    return thisObj;
}