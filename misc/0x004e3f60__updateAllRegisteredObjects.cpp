// FUNC_NAME: updateAllRegisteredObjects

// Global update list
extern int g_registeredObjectCount;
extern void** g_registeredObjects; // array of pointers, each object has a virtual function table

// Forward declaration: each object must have a virtual function at offset 0x20 (vtable index 8)
// Typically a tick/update method

void updateAllRegisteredObjects(void)
{
    for (int i = 0; i < g_registeredObjectCount; i++)
    {
        void* obj = g_registeredObjects[i];
        // Call virtual function at offset 0x20 (5th vtable entry after 0x00,0x04,0x08,0x0C,0x10,0x14,0x18,0x1C,0x20)
        void (*updateFunc)(void*) = *(void(**)(void*))((char*)obj + 0x20);
        updateFunc(obj);
    }

    // Perform follow-up processing (e.g., pending deletions, swap, etc.)
    FUN_0052e5f0();
}