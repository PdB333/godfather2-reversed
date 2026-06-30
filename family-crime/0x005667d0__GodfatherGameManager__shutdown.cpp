// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(GodfatherGameManager* this)
{
    int iVar1;

    // Set vtable to the class vtable (likely the destructor vtable)
    *this = &PTR_FUN_00e3a7a8;                     // +0x00: vtable pointer
    this[1] = &PTR_LAB_00e3a840;                   // +0x04: secondary vtable or base class vtable

    // Free memory at offset 0x11C (0x47 * 4)
    operatorDelete(this[0x47]);                     // +0x11C: some allocated buffer

    // If pointer at offset 0x0C is non-null, call its virtual function at vtable+4 (likely release/destroy)
    if (this[3] != nullptr) {                       // +0x0C: pointer to another object
        (*(void (__thiscall**)(GodfatherGameManager*))(*(int*)this[3] + 4))(this);
    }

    // Shutdown various subsystems
    shutdownSubsystem1();                           // FUN_00566b70
    shutdownSubsystem2();                           // FUN_00af3560

    iVar1 = this[2];                                // +0x08: some handle or pointer
    if (iVar1 != 0) {
        shutdownSubsystem3();                       // FUN_00b0fa90
        operatorDelete(iVar1);                      // free the handle
    }

    // Clean up another allocated block at offset 0x20
    if (this[8] != 0) {                             // +0x20: allocated memory
        this[9] = 0;                                // +0x24: set to null
        operatorDeleteArray(this[8]);               // FUN_009c8f10 (array delete)
        this[8] = 0;                                // +0x20: set to null
    }

    // Call virtual function at vtable+0x0C on object at offset 0x28
    (*(void (__thiscall**)(void))(*(int*)this[10] + 0x0C))(); // +0x28: pointer to another object

    // More subsystem shutdowns
    shutdownSubsystem4();                           // FUN_00ae3e50
    shutdownSubsystem5();                           // FUN_00aedb70
    shutdownSubsystem6();                           // FUN_00ae97f0

    // Update vtable pointers to purecall handler (prevents further virtual calls)
    this[1] = &PTR_LAB_00e3a844;                   // +0x04: set to another vtable
    DAT_012234b8 = 0;                               // global flag indicating shutdown complete
    *this = &PTR___purecall_00e3a738;               // +0x00: set to purecall vtable
    return;
}