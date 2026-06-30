// FUNC_NAME: DualVTableClass::constructor

// This constructor sets up dual vtable pointers for a class that inherits from
// an abstract interface (vtable with __purecall) and a concrete base class.
// The concrete base vtable is stored at offset +0x04 relative to this.
// A global singleton flag (0x0112994c) is reset to 0.
// The 'flags' byte controls whether a finalizer (FUN_009c8eb0) is called,
// likely for freeing memory if the constructor was invoked by operator new.

undefined4* __thiscall DualVTableClass_constructor(undefined4* thisObj, byte flags)
{
    undefined4* secondVtablePtr;

    if (thisObj == (undefined4*)0x0) {
        secondVtablePtr = (undefined4*)0x0;  // null check (defensive)
    }
    else {
        secondVtablePtr = thisObj + 1;       // +0x04: offset for second vtable
    }
    // Set concrete base vtable at offset +0x04
    *secondVtablePtr = &PTR_LAB_00d580f4;

    // Clear global initialization flag (probably a singleton or manager flag)
    DAT_0112994c = 0;

    // Set abstract interface vtable at offset +0x00 (contains __purecall entries)
    *thisObj = &PTR___purecall_00d580a8;

    // If the 'flags' parameter has bit 0 set, call a finalizer function
    // (likely operator delete or registration cleanup)
    if ((flags & 1) != 0) {
        FUN_009c8eb0(thisObj);
    }

    return thisObj;
}