// FUNC_NAME: DebugActionItem::DebugActionItem
// Function at 0x005ca060: Constructor for a debug menu action item. Initializes fields and registers a callback (event type 6) with a global manager.

// Forward declarations (from reverse engineering)
extern int g_debugMenuManager; // DAT_00e3ebc0 - global debug menu manager singleton
extern bool DebugMenuManager_IsReady(void* manager); // FUN_005c0830 - returns 0 if ready, negative if not
extern void* GrowArray(void* oldArray, int newCapacity, int elementSize, int* outCapacity, int* outCount); // FUN_005c27a0 - reallocates array

// Callback handler identified from the registration (FUN_005c7150)
extern void __cdecl DebugActionHandler(void* context, int actionId); // Not defining signature, placeholder

// Structure of an entry in the dynamic array (0x18 bytes)
struct DebugActionEntry {
    void* manager;          // +0x00 (points to g_debugMenuManager)
    void* context;          // +0x04 (address of this->m_callbackContext)
    int    actionType;      // +0x08 (always 6)
    void*  callback;        // +0x0C (DebugActionHandler)
    int    field_0x10;      // +0x10 (0)
    int    field_0x14;      // +0x14 (1)
};

// Object layout:
// +0x00 void* vtable;                   (set to PTR_FUN_00e3ecac)
// +0x04 DebugActionEntry* m_pEntries;   (pointer to array of entries)
// +0x08 int m_capacity;                 (allocated size)
// +0x0C int m_count;                    (current number of entries)
// +0x10 int field_0x10;                 (unused/unknown)
// +0x14 int field_0x14;
// +0x18 int field_0x18;
// +0x1C void* m_callbackContext;        (context pointer passed to callback)

void __thiscall DebugActionItem::Constructor(void* this) {
    int* capacityPtr;
    DebugActionEntry* newEntry;
    int checkResult;

    // Initialize all fields to 0
    *(int*)((char*)this + 0x0C) = 0;  // m_count = 0
    *(int*)((char*)this + 0x04) = 0;  // m_pEntries = NULL
    *(int*)((char*)this + 0x08) = 0;  // m_capacity = 0
    *(void**)this = (void*)&PTR_FUN_00e3ecac; // vtable
    *(int*)((char*)this + 0x18) = 0;  // field_0x18
    *(int*)((char*)this + 0x10) = 0;  // field_0x10
    *(int*)((char*)this + 0x14) = 0;  // field_0x14
    *(int*)((char*)this + 0x1C) = 0;  // m_callbackContext

    // Check if global manager is ready (returns negative if not ready)
    checkResult = DebugMenuManager_IsReady(&g_debugMenuManager);
    if (checkResult < 0) {
        capacityPtr = (int*)((char*)this + 0x08); // pointer to m_capacity
        // If we have reached capacity, grow the array
        if (*(int*)((char*)this + 0x0C) < *(int*)((char*)this + 0x08) + 1) {
            // Grow array of entries (element size 0x18)
            *(int*)((char*)this + 0x04) = (int)GrowArray(
                *(void**)((char*)this + 0x04),           // old array
                *(int*)((char*)this + 0x08) + 1,         // new capacity
                0x18,                                     // element size
                capacityPtr,                              // output capacity
                (int*)((char*)this + 0x0C)               // output count (?? actually used for count increment later)
            );
        }
        // Add new entry at the end
        newEntry = (DebugActionEntry*)(*(int*)((char*)this + 0x04) + *(int*)((char*)this + 0x08) * 0x18);
        *(int*)((char*)this + 0x08) = *(int*)((char*)this + 0x08) + 1; // increment capacity
        newEntry->manager    = &g_debugMenuManager;
        newEntry->context    = (void*)((char*)this + 0x1C); // address of m_callbackContext
        newEntry->actionType = 6;
        newEntry->callback   = (void*)DebugActionHandler;
        newEntry->field_0x10 = 0;
        newEntry->field_0x14 = 1;
    }
}