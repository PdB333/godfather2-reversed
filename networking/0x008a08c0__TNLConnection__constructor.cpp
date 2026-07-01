// FUNC_NAME: TNLConnection::constructor
void __thiscall TNLConnection::constructor(TNLConnection* this) {
    // Initialize sub-objects (e.g., packet windows)
    sub_89fc80(this + 0x34); // likely cleanup/reset of a member
    sub_89fc80(this + 0x40);
    sub_89fcf0(this + 0x28); // possibly init a list or object
    
    // Initialize first linked list head (e.g., mPacketList)
    int* listHead1 = reinterpret_cast<int*>(this + 0x10);
    sub_89ebc0();            // maybe list init helper
    *listHead1 = reinterpret_cast<int>(listHead1);
    *(int*)(this + 0x14) = reinterpret_cast<int>(listHead1);
    
    // Initialize second linked list head (e.g., mReliableList)
    int* listHead2 = reinterpret_cast<int*>(this + 0x1c);
    sub_89ec40();            // another list init
    *listHead2 = reinterpret_cast<int>(listHead2);
    *(int*)(this + 0x20) = reinterpret_cast<int>(listHead2);
    
    // Release any existing connection data at +0xAC
    int* dataPtr = reinterpret_cast<int*>(this + 0xAC);
    if (*dataPtr != 0 && *dataPtr != 0x14) {
        if (*dataPtr != 0) {
            // Call virtual destructor (vtable at negative offset -0x14)
            undefined4* vtable = reinterpret_cast<undefined4*>(*dataPtr - 0x14);
            if (vtable != nullptr) {
                (*(void(__thiscall**)(int))vtable)(1); // release with argument 1
            }
        }
        if (*dataPtr != 0) {
            FUN_004daf90(dataPtr); // free the pointer
            *dataPtr = 0;
        }
    }
    
    // Decrement reference count on global object (e.g., gNetInterface)
    FUN_004086d0(&DAT_012069c4);
    
    // Clear per-frame state (e.g., last send time, sequence numbers)
    sub_89e820();
    sub_89eb80();
    
    // Zero out a block of per-connection data (connection flags, counters)
    *(undefined4*)(this + 0xBC) = 0; // mLastRecvTime
    *(undefined4*)(this + 0xC0) = 0; // mNextSendTime
    *(undefined4*)(this + 0xC4) = 0; // mSendRate
    *(undefined4*)(this + 0xC8) = 0; // mRecvRate
    *(undefined1*)(this + 0xD0) = 0; // mFlags[0]
    *(undefined1*)(this + 0xD1) = 0; // mFlags[1]
    *(undefined1*)(this + 0xD2) = 0; // mFlags[2]
    *(undefined1*)(this + 0xD3) = 0; // mFlags[3]
    *(undefined4*)(this + 0xCC) = 0; // mPadding
}