// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __thiscall GodfatherGameManager::~GodfatherGameManager()
{
    // Save vtable pointers for runtime type info (derived then base)
    *(int *)this = (int)&PTR_FUN_00d78830;     // Derived class vtable
    *(int *)((char *)this + 4) = (int)&PTR_LAB_00d78820; // Secondary vtable?

    // Cleanup embedded subsystem objects (likely singleton managers)
    destroySubsystem(&DAT_01130278);
    destroySubsystem(&DAT_01130300);
    destroySubsystem(&DAT_011303c0);
    destroySubsystem(&DAT_011301c8);
    destroySubsystem(&DAT_01130280);
    destroySubsystem(&DAT_011301a0);
    destroySubsystem(&DAT_011304e0);
    destroySubsystem(&DAT_01130490);
    destroySubsystem(&DAT_011304c0);
    destroySubsystem(&DAT_01130250);
    destroySubsystem(&DAT_011302d8);
    destroySubsystem(&DAT_011304b8);

    // Another batch of cleanups
    releaseSubsystem(&DAT_0112eb5c);
    releaseSubsystem(&DAT_0112eb64);
    releaseSubsystem(&DAT_0112eb84);
    releaseSubsystem(&DAT_0112eb7c);
    releaseSubsystem(&DAT_0112eb74);
    releaseSubsystem(&DAT_0112eb6c);
    releaseSubsystem(&DAT_01130278);
    releaseSubsystem(&DAT_01130300);
    releaseSubsystem(&DAT_011303c0);
    releaseSubsystem(&DAT_011301c8);
    releaseSubsystem(&DAT_01130280);
    releaseSubsystem(&DAT_011301a0);
    releaseSubsystem(&DAT_011304e0);
    releaseSubsystem(&DAT_01130490);
    releaseSubsystem(&DAT_011304c0);
    releaseSubsystem(&DAT_01130250);
    releaseSubsystem(&DAT_011302d8);
    releaseSubsystem(&DAT_011304b8);

    // Call subsystem finalizer
    finalizeSubsystems();

    // Release arrays of pointers at offsets +0xB4 (0x2d) and +0xAC (0x2b)
    // Offsets are in DWORDs, so multiply by 4
    // +0x2d * 4 = 0xB4
    if (*(int *)((char *)this + 0xB4) != 0) {
        releasePointerArray((int *)((char *)this + 0xB4));
    }
    // +0x2b * 4 = 0xAC
    if (*(int *)((char *)this + 0xAC) != 0) {
        releasePointerArray((int *)((char *)this + 0xAC));
    }

    // Loop to free 3 pointers at decreasing offsets from +0xAC
    int *current = (int *)((char *)this + 0xAC);
    for (int i = 3; i >= 0; i--) {
        int *prev = current - 3;
        current = prev;
        if (*prev != 0) {
            releasePointerArray(prev);
        }
    }

    // Another loop at offset +0x7C (0x1f * 4)
    int *current2 = (int *)((char *)this + 0x7C);
    for (int i = 3; i >= 0; i--) {
        int *prev = current2 - 3;
        current2 = prev;
        if (*prev != 0) {
            releasePointerArray(prev);
        }
    }

    // Call additional destructors for contained objects
    destructObjectA();
    destructObjectA(); // called twice intentionally
    destructObjectB();
    destructObjectC();
    destructObjectD();

    // Global finalizer
    globalCleanup();

    // Restore base vtable (likely to avoid virtual calls during destruction)
    *(int *)this = (int)&PTR_LAB_00d77e34;

    // Mark global as uninitialized
    DAT_01129914 = 0;
}