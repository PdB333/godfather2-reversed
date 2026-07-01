// FUNC_NAME: CGameObjectManager::processCallbackList
// Function address: 0x00790b10
// This function processes a list of callback objects (stored as pointer array in a ListContainer)
// Caller: 0x007912d0 (likely an update loop)
// It checks a processing flag (bit 25 at +0x5C) to prevent reentrancy, sets it, iterates over the list
// in reverse order, calls the virtual function at vtable offset 8 on each non-null object, then calls
// an external helper (FUN_007909d0).

#include <cstdint>

// Structure at +0xAC (pointer to a simple container with data pointer and count)
struct ListContainer {
    void** items; // +0x00
    int32_t count; // +0x04
};

class CGameObjectManager {
public:
    // +0x5C: flags (bit 25 = 0x02000000: processing flag)
    // +0xAC: pointer to ListContainer (list of callback objects)
    void __thiscall processCallbackList();
};

// Helper: call the virtual function at vtable offset 8 on an object.
// The object's this pointer is passed to the called function (here the manager itself).
typedef void (__thiscall* VirtualFuncAtOffset8)(void* managerThis);

void CGameObjectManager::processCallbackList() {
    uint32_t* flagsPtr = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x5C);
    if (*flagsPtr & 0x02000000) // Check if already processing
        return;

    // Get pointer to the list container
    ListContainer** listContainerPtr = reinterpret_cast<ListContainer**>(
        reinterpret_cast<uint8_t*>(this) + 0xAC);
    ListContainer* listContainer = *listContainerPtr;
    if (listContainer == nullptr)
        return;

    // Set the processing flag to prevent recursive calls
    *flagsPtr |= 0x02000000;

    // Iterate over the list in reverse order (from count-1 down to 0)
    int32_t count = listContainer->count;
    int32_t i = count - 1;
    while (i >= 0) {
        // Dereference: listContainer->items[i] gives the object pointer
        void** item = &listContainer->items[i];
        void* obj = *item;
        if (obj != nullptr) {
            // Call virtual function at vtable offset 8 (third virtual function)
            VirtualFuncAtOffset8 func = *reinterpret_cast<VirtualFuncAtOffset8*>(
                *reinterpret_cast<uint32_t*>(obj) + 8);
            func(this);
        }
        --i;
    }

    // External helper function (likely finalizes the processing, possibly clears the flag)
    FUN_007909d0(); // defined elsewhere
}