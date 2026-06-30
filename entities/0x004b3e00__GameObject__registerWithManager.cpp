// FUNC_NAME: GameObject::registerWithManager
// Address: 0x004b3e00
// Role: Registers this object with the global object manager, initializes state.
// Fields: +0x10: initialization flag, +0x86C: some resource handle.
// Globals: gObjectManagerList (DAT_01206880), gFlag1 (DAT_0120546d), gCallbackFunc (DAT_01218020)

void __thiscall GameObject::registerWithManager(void)
{
    int* pListEntry;

    // Only proceed if not already initialized
    if (*(int*)(this + 0x10) != 0) {
        // Release global resources
        FUN_004086d0(&DAT_01206970);
        FUN_004086d0(&DAT_01206978);
        
        // Clear initialization flag and resource handle
        *(int*)(this + 0x10) = 0;
        *(int*)(this + 0x86C) = 0;
        
        // Add this object to the global registration list
        pListEntry = (int*)(DAT_01206880 + 0x14); // Pointer to current entry slot
        **(int**)(DAT_01206880 + 0x14) = (int*)&PTR_LAB_01124550; // Store vtable/function table
        *pListEntry = *pListEntry + 4; // Advance pointer
        *(int*)*pListEntry = (int)this; // Store this object
        *pListEntry = *pListEntry + 4; // Advance pointer again
        
        // Clear global flag
        DAT_0120546d = 0;
        
        // Prepare callback info and invoke registration notifier
        struct {
            int funcPtr;      // +0x00: callback function pointer
            int objectPtr;    // +0x04: this object
            char padding;    // +0x08: unused
        } callbackInfo;
        callbackInfo.funcPtr = DAT_01218020;
        callbackInfo.objectPtr = (int)this;
        callbackInfo.padding = 0;
        FUN_00408a00(&callbackInfo, 0); // Invoke registration notification with zero argument
    }
}