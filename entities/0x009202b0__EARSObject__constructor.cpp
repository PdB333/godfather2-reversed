// FUNC_NAME: EARSObject::constructor
// Address: 0x009202b0
// Role: Constructor for an EARSObject-derived class; optionally initializes vtable/manager using a size constant.

undefined4 __thiscall EARSObject::constructor(EARSObject *this, byte allocFlag)
{
    // Call base class constructor
    baseConstructor(); // FUN_0091fd30

    if ((allocFlag & 1) != 0) {
        // Full initialization path: obtain manager pointer and call init function at offset 4
        int *managerPtr = (int *)getManager(); // FUN_009c8f80
        ((void (*)(EARSObject *, uint))(*managerPtr + 4))(this, 0x1dd0); // offset 4 = vtable/init call, 0x1dd0 = object size or ID
    }

    return this;
}