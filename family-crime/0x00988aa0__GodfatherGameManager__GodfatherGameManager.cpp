// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x00988aa0
// Role: Constructor for the GodfatherGameManager singleton. Initializes all state to zero, sets vtable pointers, and initializes two linked list structures for internal use.

#include <cstdint>

// Forward declaration of base class constructor (likely from EARS::Framework::Object or similar)
void __fastcall BaseObjectConstructor(void* this); // at 0x005bf9b0

// Globally stored singleton pointer
static GodfatherGameManager* g_gameManager; // DAT_011305b0

class GodfatherGameManager {
public:
    void* __fastcall GodfatherGameManager(void);

    // Member variables (order and offsets as per decompilation)
    // offset 0x00: main vtable (*PTR_FUN_00d91070)
    // offset 0x04: secondary vtable (*PTR_LAB_00d91048) – but note param_1[4] is set, that's offset 0x10
    // offset 0x10: another vtable
    // offset 0x4C: pointer that gets two assignments (initial & final)
    // offset 0x50: byte
    // offset 0x51: byte
    // offsets 0x54..0xC0: 30 zeroed 4-byte fields (indices 0x15..0x30)
    // offsets 0xC4,0xCC,0xD4,0xDC: first linked list nodes (each 8 bytes)
    // offset 0xE4: pointer to first list head
    // offsets 0xE8,0xF0,0xF8,0x100: second linked list nodes (each 8 bytes)
    // offset 0x108: pointer to second list head
    // offsets 0x10C,0x10D,0x10E,0x110,0x114,0x118: bytes and ints (last zeros)
};

void* __fastcall GodfatherGameManager::GodfatherGameManager(void)
{
    // Call base class constructor
    BaseObjectConstructor(this);

    // Set a vtable pointer at offset 0x4C (initial value)
    this->field_0x4C = (void*)&PTR_LAB_00d91040; // vtable #3

    // Store the singleton globally
    g_gameManager = this;

    // Zero byte at offset 0x50
    *(uint8_t*)((uintptr_t)this + 0x50) = 0;

    // Zero byte at offset 0x51
    *(uint8_t*)((uintptr_t)this + 0x51) = 0;

    // Zero 30 consecutive 4-byte fields (indices 0x15 through 0x30)
    for (int i = 0; i < 30; ++i)
        ((int32_t*)this)[0x15 + i] = 0;

    // Zero bytes at offsets 0x10D and 0x10E
    *(uint8_t*)((uintptr_t)this + 0x10D) = 0;
    *(uint8_t*)((uintptr_t)this + 0x10E) = 0;

    // Zero three 4-byte fields at offsets 0x110, 0x114, 0x118
    ((int32_t*)this)[0x44] = 0;
    ((int32_t*)this)[0x45] = 0;
    ((int32_t*)this)[0x46] = 0;

    // Set main vtable at offset 0x00
    this->vtable0 = (void*)&PTR_FUN_00d91070;

    // Set secondary vtable at offset 0x10 (index 4)
    this->vtable1 = (void*)&PTR_LAB_00d91048;

    // Update the vtable at offset 0x4C to final value
    this->field_0x4C = (void*)&PTR_LAB_00d91044;

    // Zero two 8-byte blocks (likely linked list nodes) at specified offsets
    // First block: indices 0x31,0x32 (offset 0xC4) to 0x37,0x38 (offset 0xDC)
    *reinterpret_cast<uint64_t*>(&((int32_t*)this)[0x31]) = 0;
    *reinterpret_cast<uint64_t*>(&((int32_t*)this)[0x33]) = 0;
    *reinterpret_cast<uint64_t*>(&((int32_t*)this)[0x35]) = 0;
    *reinterpret_cast<uint64_t*>(&((int32_t*)this)[0x37]) = 0;

    // Set pointer at offset 0xE4 to point to the start of first block (offset 0xC4)
    ((int32_t*)this)[0x39] = (int32_t) &((int32_t*)this)[0x31];

    // Second block: indices 0x3A,0x3B (offset 0xE8) to 0x40,0x41 (offset 0x100)
    *reinterpret_cast<uint64_t*>(&((int32_t*)this)[0x3A]) = 0;
    *reinterpret_cast<uint64_t*>(&((int32_t*)this)[0x3C]) = 0;
    *reinterpret_cast<uint64_t*>(&((int32_t*)this)[0x3E]) = 0;
    *reinterpret_cast<uint64_t*>(&((int32_t*)this)[0x40]) = 0;

    // Set pointer at offset 0x108 to point to the start of second block (offset 0xE8)
    ((int32_t*)this)[0x42] = (int32_t) &((int32_t*)this)[0x3A];

    return this;
}