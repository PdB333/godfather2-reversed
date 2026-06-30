// FUNC_NAME: EARSObject::constructor
// Function at 0x0047cb70: Constructor for an EARS engine object, calls base constructor and optionally invokes a virtual initialization function.
// The constructor receives a byte flag (allocFlag) where bit 0 indicates whether to call a virtual init function from a global vtable table.

void* __thiscall EARSObject::constructor(uint this_ptr, byte allocFlag) {
    // Call base class constructor at 0x0047cba0
    BaseClass::constructor(this_ptr);

    // Check if allocation flag indicates virtual init should be called
    if ((allocFlag & 1) != 0) {
        // Retrieve vtable pointer from global table (DAT_01223410 + 0x2d4)
        void** globalVtableTable = *(void***)((char*)s_globalTable + 0x2d4);  // +0x2d4
        // Call the function at vtable index 1 (offset 4) with this and argument 0
        void (*initFunc)(void*, int) = (void (*)(void*, int))globalVtableTable[1];
        initFunc(this_ptr, 0);
    }

    // Return this pointer as per __thiscall convention
    return (void*)this_ptr;
}