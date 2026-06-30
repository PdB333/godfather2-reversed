// FUNC_NAME: EARSObject::~EARSObject

void __thiscall EARSObject::~EARSObject(void)
{
    // vtable pointer at +0x00
    *(int **)this = &PTR_FUN_00e313c8;  // Switch to derived vtable for destruction

    if (*(int *)((char *)this + 0x90) != 0)  // +0x90: allocation flag for sub-object
    {
        // +0x10: sub-object (e.g., string or array) destructor
        FUN_00610100((int *)this + 0x4);   // call member destructor on this+0x10
    }

    *(int **)this = &PTR_LAB_00e2f638;  // Reset vtable to base class after destruction
}