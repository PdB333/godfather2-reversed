// FUNC_NAME: EARS::Framework::Object::constructor
int __thiscall EARS::Framework::Object::constructor(int thisPtr, byte flags)
{
    undefined4 *vtableSlot;
    
    if (thisPtr == 0) {
        vtableSlot = (undefined4 *)0x0;
    }
    else {
        vtableSlot = (undefined4 *)(thisPtr + 0x20); // +0x20: vtable pointer
    }
    *vtableSlot = &PTR_LAB_00d580e4; // Set vtable to this class's table
    
    g_initialized = 0; // Global flag reset (DAT_011298f0)
    
    baseInitFunction(); // FUN_007edfb0: likely base class initialization
    
    if ((flags & 1) != 0) {
        deallocateObject(thisPtr); // FUN_009c8eb0: operator delete or cleanup
    }
    
    return thisPtr;
}