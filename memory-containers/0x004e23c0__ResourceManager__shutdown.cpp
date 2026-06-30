// FUNC_NAME: ResourceManager::shutdown

// Function at 0x004e23c0: shutdown/cleanup of a global resource manager.
// Clears state variables and frees an array of 20 pointer slots (8 bytes each, starting at offset +0x110).
// The global base is at 0x01218d40 (assumed struct ResourceManagerGlobals).
// Calls FUN_004e1c40 (likely finalization step) then frees each non-null pointer via FUN_006065a0 (memory deallocation).

struct ResourceManagerSlot {
    void* ptr;       // +0x00
    int   unknown;   // +0x04 (not used here)
};

struct ResourceManagerGlobals {
    int   field_0x100;   // +0x100
    short field_0x102;   // +0x102
    int   field_0x104;   // +0x104
    int   field_0x108;   // +0x108
    int   field_0x10c;   // +0x10c
    // padding (2 bytes to align to 8?)
    ResourceManagerSlot slots[20]; // +0x110, each 8 bytes, 20 entries
};

static ResourceManagerGlobals g_resourceManager; // at address 0x01218d40

// Forward declarations of called functions
void FUN_004e1c40(void);               // flush / finalize
void MemoryManager_free(void* ptr, int tag); // FUN_006065a0

void ResourceManager::shutdown(void)
{
    // Perform final cleanup before resetting all state
    FUN_004e1c40();

    // Clear global counters / flags
    g_resourceManager.field_0x100 = 0;
    g_resourceManager.field_0x102 = 0;
    g_resourceManager.field_0x104 = 0;
    g_resourceManager.field_0x108 = 0;
    g_resourceManager.field_0x10c = 0;

    // Iterate over all 20 slots (offset range 0x110 to 0x1b0, step 8)
    for (int i = 0; i < 20; ++i)
    {
        ResourceManagerSlot& slot = g_resourceManager.slots[i];
        if (slot.ptr != nullptr)
        {
            MemoryManager_free(slot.ptr, 0);
            slot.ptr = nullptr;
        }
    }
}