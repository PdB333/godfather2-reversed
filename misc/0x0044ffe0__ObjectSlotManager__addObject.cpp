// FUNC_NAME: ObjectSlotManager::addObject
// Function address: 0x0044ffe0
// Role: Registers an object into a fixed-size per-instance slot pool (256 slots, 64 bytes each).
//       The slot pool base is accessed via thread-local storage (FS segment).
//       Each slot stores a pointer to the object at offset 0, and a field from the object at +0x20
//       is copied into slot offset 8. This likely implements an object registration system
//       (e.g., for active objects or ghost replication in EARS engine).
//
// Note: The object pointer is passed in the ESI register (custom calling convention or global).
//       The function is __thiscall with 'this' in ECX.

#include <cstdint>

// Helper: dereference thread-local storage to obtain the base address of slot arrays.
// Layout: FS:[0x2c] → pointer → +0x8 → pointer containing global base.
inline int getSlotArrayBase() {
    int* tebBase = (int*)__readfsdword(0x2c);               // Thread Environment Block base
    int* ptr = *(int**)((char*)tebBase + 8);                 // offset 0x8 in TEB structure
    return *ptr;                                             // dereference to get global base
}

// Finalization function called after a slot is filled (address 0x0044e8d0).
static void finalizeSlotAddition();

void __thiscall ObjectSlotManager::addObject(void* object) {
    // Compute the address of this instance's slot array
    int baseAddr = getSlotArrayBase() + 0x110;                         // global pool offset
    int instanceOffset = *(int*)((char*)this + 0x68);                  // per-instance offset (+0x68)
    int slotArrayAddr = baseAddr + instanceOffset;                     // final byte address of slot array

    // Slot count is stored at the end of the 256-slot array (each slot 0x40 bytes)
    uint* countPtr = (uint*)(slotArrayAddr + 0x4000);                 // +0x4000 = after all slots
    uint count = *countPtr;

    if (count < 256) {
        // Compute pointer to the next available slot
        int* slot = (int*)(slotArrayAddr + count * 0x40);

        // Increment the slot count
        *countPtr = count + 1;

        // Fill slot fields:
        slot[0] = (int)object;                                        // store object pointer
        slot[2] = *(int*)((int)object + 0x20);                        // copy object's field at +0x20 (e.g., vtable or type ID)

        // Finalize slot addition (e.g., update lists or notify systems)
        finalizeSlotAddition();
    }
}