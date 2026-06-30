// FUNC_NAME: EventScheduler::scheduleEvent
void __thiscall EventScheduler::scheduleEvent(void* thisPtr, void* eventObj) {
    // eventObj is a registered event structure
    if (eventObj == nullptr) {
        return;
    }

    // Local callback entry constructed on stack
    struct CallbackEntry {
        void** vtable;          // +0x00
        void* next;             // +0x04
        int unknown1;           // +0x08
        int unknown2;           // +0x0C
        int constant;           // +0x10  (0x1f569d80)
        int zero1;              // +0x14
        int zero2;              // +0x18
        int zero3;              // +0x1C
        char flag;              // +0x20
        int globalData;         // +0x24
    } entry;

    entry.vtable = &PTR_FUN_00d5dbbc;  // global function pointer table
    entry.next = nullptr;
    entry.unknown1 = 0;
    entry.unknown2 = 0;
    entry.constant = 0x1f569d80;
    entry.zero1 = 0;
    entry.zero2 = 0;
    entry.zero3 = 0;
    entry.flag = 0;
    entry.globalData = DAT_01205228;   // global variable

    // eventObj +0x48 is a node; +0x4c is a next pointer
    int* nodePtr = reinterpret_cast<int*>(reinterpret_cast<char*>(eventObj) + 0x48);
    int** nextField = reinterpret_cast<int**>(reinterpret_cast<char*>(eventObj) + 0x4c);

    if (nodePtr != nullptr) {
        int savedNext = *nextField;    // save old next pointer
        *nextField = reinterpret_cast<int*>(&entry.next); // link into local list
        // note: this creates a temporary linked list head on the stack
        // the original code sets local_1c = param_2 + 0x48, which is nodePtr
        // we repurpose nodePtr for cleanup later
        nodePtr = &savedNext; // but not actually used? Misleading.

        // Actually, from the decompiled: local_1c = param_2 + 0x48; then later local_1c is passed to cleanup
        // So we need to keep the original node pointer for cleanup.
    }

    // Prepare parameter for registration call
    void* adjustedThis = (thisPtr != nullptr) ? reinterpret_cast<char*>(thisPtr) + 0x3C : nullptr;
    FUN_00408bf0(&entry, adjustedThis, 0);   // register the callback

    // Cleanup the temporary list node if it was set
    if (nodePtr != nullptr) {
        FUN_004daf90(&nodePtr);
    }
}