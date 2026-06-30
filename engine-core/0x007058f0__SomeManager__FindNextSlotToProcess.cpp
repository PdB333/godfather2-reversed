// FUNC_NAME: SomeManager::FindNextSlotToProcess
// Function at 0x007058f0 - Iterates over slots to find a pending object, processes it, returns slot pointer or 0.
// Class layout: offset 0xf8: currentSlotIndex, offset 0x114: usedSlotBitmask (bits 0-10), array of Slot objects at offset 0x0, each slot 0x14 bytes.

struct Slot {
    uint8_t pad00[0x18];            // +0x00 to +0x17
    void* pObject;                  // +0x18 - pointer to object (handle -> base - 0x48?)
};

// Forward declarations of called functions (from other parts of the binary)
int __fastcall handleToObject(void* pObjectMinus0x48);  // 0x00704150 - returns -1 if invalid/released
void* __fastcall objectToInstance(int handle);           // 0x00704110 - returns pointer to full object or 0
void __fastcall releaseSlotPointer(void** ppSlot);     // 0x004daf90 - frees the pointer and sets *ppSlot = 0
void __cdecl onObjectReady(int param);                  // 0x00701830 - called with 0

int __fastcall SomeManager::FindNextSlotToProcess(int this) {
    int currentSlot = *(int*)(this + 0xf8);    // current index
    int slotIndex = currentSlot;
    // Loop up to 12 iterations (covering all 11 slots + one extra)
    for (int count = 0; count < 12; count++) {
        slotIndex--;
        if (slotIndex < 0 || slotIndex > 10) {
            slotIndex = 10;   // Wrap around (circular scan)
        }
        Slot* slot = (Slot*)(this + slotIndex * 0x14);
        void* objectPtr = slot->pObject;
        // Check if slot holds a valid object (not null, not a sentinel 0x48)
        if (objectPtr != nullptr && objectPtr != (void*)0x48) {
            int bitmask = *(int*)(this + 0x114);
            int bit = 1 << (slotIndex & 0x1f);
            // If the slot is NOT marked as occupied in the bitmask, process it
            if ((bitmask & bit) == 0) {
                *(int*)(this + 0xf8) = slotIndex;   // Update current index
                int handle = handleToObject((void*)((int)objectPtr - 0x48));
                if (handle == -1) {
                    // Object has been released, clean up the slot
                    if (objectPtr != nullptr && objectPtr != (void*)0x48) {
                        releaseSlotPointer(&slot->pObject);
                        slot->pObject = nullptr;
                    }
                    *(int*)(this + 0xf8) = 0;   // Reset current index
                } else {
                    // Object is alive, get full instance
                    void* objInstance = objectToInstance(handle);
                    if (objInstance != nullptr) {
                        if (*(char*)(objInstance + 0x1a8) == 1) {   // Some flag check
                            onObjectReady(0);
                        }
                        return (int)slot;   // Return pointer to the slot
                    }
                }
            }
        }
    }
    return 0;   // No valid slot found
}