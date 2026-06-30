// FUNC_NAME: EventScheduler::handleEvent
void __thiscall EventScheduler::handleEvent(int this, int eventType)
{
    // Temporary string objects for event data
    String tempString1;  // local_30
    String tempString2;  // local_30 reused
    // List node pointer (intrusive list)
    ListNode* node;      // local_1c
    // Pointer to a static vtable or function table
    void** staticTable;  // local_24
    int someHash;        // local_20
    // Other temporaries for string construction
    int tempInt;         // local_18
    int zero1;           // local_14
    int zero2;           // local_10
    int zero3;           // local_c
    byte tempByte;       // local_8
    int globalData1;     // local_4
    byte tempByte2;      // local_28

    if (eventType == 0) {
        // Event type 0: global start/stop? (no this usage)
        FUN_006b6da0(); // likely global event handler
    } else {
        // All other event types call this global function first
        FUN_006b6e30(); // likely global event setup

        if (eventType == 4) {
            // Event type 4: initialization with list manipulation
            staticTable = &PTR_FUN_00d5dbbc; // static function table
            someHash = 0x1970c04;            // event hash/ID

            // Get list node pointer (offset +0x48 from this)
            if (this == 0) {
                node = 0;
            } else {
                node = (ListNode*)(this + 0x48);
            }

            // Save old next pointer and make node point to itself (circular list)
            tempInt = 0;
            if (node != 0) {
                tempInt = *(int*)(node + 4); // old next
                *(int**)(node + 4) = &node;  // set next to self
            }

            // Initialize temporary string with global data
            // This looks like constructing a string from a static string and a hash
            tempString1 = DAT_0112ad8c; // global string
            // ... other fields set to zero
            FUN_00408a00(&tempString1, 0); // string assignment/init

            // Now assign another string from this+0x26c
            tempString2 = *(int*)(this + 0x26c); // string field
            FUN_00408a00(&tempString2, 0); // string assignment

            // Set a pointer at this+0x18c to a global value
            *(int*)(this + 0x18c) = _DAT_00d5780c;

            // Set flag bit 1 at this+0x2b4
            *(byte*)(this + 0x2b4) |= 2;

            // Remove node from list (if it was inserted)
            if (node != 0) {
                FUN_004daf90(&node); // list remove function
            }
        } else if (eventType == 3) {
            // Event type 3: just set flag bit 1
            *(byte*)(this + 0x2b4) |= 2;
        } else if (eventType == 2) {
            // Event type 2: clear flag bit 1 and clear a string
            *(byte*)(this + 0x2b4) &= 0xfd; // clear bit 1
            tempString1 = *(int*)(this + 0x274); // another string field
            FUN_00408a00(&tempString1, 0); // clear/assign
        }
    }

    // Notify a listener/callback object (if present)
    if (*(int**)(this + 0x130) != 0) {
        // Call function at vtable offset 0x44 of the listener object
        // First argument is a constant hash 0xf86f4484, second is eventType
        (**(code**)(**(int**)(this + 0x130) + 0x44))(0xf86f4484, eventType);
    }
}