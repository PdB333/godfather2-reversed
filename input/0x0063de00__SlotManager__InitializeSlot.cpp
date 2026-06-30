// FUNC_NAME: SlotManager::InitializeSlot

// Function at 0x0063de00
// Purpose: Initializes a slot structure in a manager, likely for resource/peer slot.
// this+0x1c is a pointer to a key or identifier used to create a handle.
// The slot receives a type (4), the handle, and two invalid indices (-1).

struct SlotData {
    int slotType;       // +0x00: Type of slot (e.g., resource type)
    int resourceHandle; // +0x04: Handle to allocated resource or connection
    int unk1;           // +0x08: Unused
    int unk2;           // +0x0c: Unused
    int slotIndexA;     // +0x10: Often set to -1 (invalid)
    int slotIndexB;     // +0x14: Often set to -1 (invalid)
};

// Forward declarations of helper functions (addresses guessed)
// FUN_0063dd40 - may return a global manager or unused value
static int GetSomeGlobalValue(void);

// FUN_00642970 - creates a handle from a key and returns it
// First param: pointer to key (this+0x1c)
// Second param: pointer to size (4)
// Returns: handle ID
static int CreateHandleFromKey(void* key, int* size);

void __thiscall SlotManager::InitializeSlot(SlotData* slot) {
    // Call to some global function, result discarded (possibly debug or locking)
    int temp = GetSomeGlobalValue(); // local_8
  
    int size = 4; // local_c
    // Obtain a handle from the key stored at this+0x1c
    int handle = CreateHandleFromKey(*(void**)((char*)this + 0x1c), &size); // uVar1

    // Initialize the slot structure
    slot->slotIndexA = -1;          // unaff_ESI[3] = 0xffffffff
    slot->slotIndexB = -1;          // unaff_ESI[4] = 0xffffffff
    slot->slotType = 4;             // *unaff_ESI = 4
    slot->resourceHandle = handle;  // unaff_ESI[1] = uVar1
    // Note: slot->unk1 and slot->unk2 remain unchanged (uninitialized)
}