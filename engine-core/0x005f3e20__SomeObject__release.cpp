// FUNC_NAME: SomeObject::release
void __thiscall SomeObject::release(int *owner)
{
    // Enter global critical section (mutex) for this operation
    globalCSEnter(&g_critSec);
    
    if (*(int *)(this + 0xA4) == 1) {
        // If state is ACTIVE, perform specific resource release
        doPreRelease();
        if (*(int *)(this + 0xF8) != 0) {
            releaseResource(*(int *)(this + 0xF8), 0, 0, 0);
            globalCSLeave(&g_critSec);
        }
    }
    
    // If child object pointer is non-null and owner is provided,
    // invoke a virtual callback on the owner to notify about child release
    if ((*(int *)(this + 0x11C) != 0) && (owner != (int *)0x0)) {
        (**(code **)(*owner + 4))(*(int *)(this + 0x11C), *(undefined4 *)(this + 0x128));
        // Clear child references
        *(undefined4 *)(this + 0x11C) = 0;
        *(undefined4 *)(this + 0x128) = 0;
        *(undefined4 *)(this + 0x12C) = 0;  // +300 (0x12C)
    }
    
    // Perform remaining cleanup steps
    doSubObjectCleanup();
    doMemoryRelease();
    return;
}