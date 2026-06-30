// FUNC_NAME: ControllerManager::constructor
void __fastcall ControllerManager::constructor(void* this) // 0x006fb040
{
    // Set the vtable pointer at offset +0x00
    *(void**)this = &PTR_FUN_00d60a4c;

    // Set a field at offset +0x08 to a static address (type info or vtable pointer?)
    *(void**)((int)this + 0x08) = &PTR_LAB_00d60a48;

    // Call internal initialization subroutine
    sub_constructComponents((ControllerManager*)this); // FUN_006faf00

    // Call a virtual function through a double indirection:
    // this[3] (offset +0x0C) points to a pointer to a vtable,
    // then call the function at offset +0x0C within that vtable.
    // This is likely a virtual init function specific to subclasses.
    ((void (*)())(*(int*)(*(int*)((int)this + 0x0C) + 0x0C)))();

    // Call another finalization subroutine
    sub_finalizeComponents((ControllerManager*)this); // FUN_006faeb0

    // Update the field at +0x08 to a different static address
    *(void**)((int)this + 0x08) = &PTR_LAB_00d60a40;

    // Set global flag to 0 (e.g., initialization complete or reset state)
    g_controllerManagerReady = 0; // DAT_0112996c

    // Call a global initialization routine (e.g., register with engine)
    FUN_0049c640(); // likely a global init or registration function
}