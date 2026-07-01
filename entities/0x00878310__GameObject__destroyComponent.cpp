// FUNC_NAME: GameObject::destroyComponent
void __thiscall GameObject::destroyComponent(GameObject *this, Component *component)
{
    char cVar1;
    int iVar2;
    int unused_esi; // Note: unaff_ESI, likely a register variable not properly captured
    SomeStruct local_10;
    SomeStruct local_c;

    // Ensure component is valid
    if (component != 0) {
        // Reset local structures
        local_c = 0;
        local_10 = 0;

        // Poll the component until it reports completion or timeout (8 attempts)
        // vtable+0x1cc: virtual bool Component::isReady()
        // vtable+0x1d0: virtual void Component::update()
        cVar1 = (**(code (__thiscall **)(SomeStruct *))(*(int *)this + 0x1cc))(&local_10);
        while ((cVar1 != '\0') && (unused_esi != 8)) {
            cVar1 = (**(code (__thiscall **)(SomeStruct *,SomeStruct *))(*(int *)this + 0x1d0))(&stack0xffffffec, &stack0xffffffec); // note: parameters likely incorrect; actual call may be update(this)
        }

        // Destroy the component (FUN_005430c0 likely a deallocator or destructor)
        FUN_005430c0(component, &stack0xffffffec); // stack variable used as temp

        // Remove this object from manager (FUN_007ff8a0 likely this->removeSelf())
        FUN_007ff8a0(this);

        // Log or signal destruction (FUN_005512c0 likely Log::print(2, ...))
        FUN_005512c0(2);

        // Reset component's vtable pointer to base class default (static vtable at DAT_0086b930)
        // Component has a vtable pointer at offset +0x158
        *(vtable_type **)(component + 0x158) = &DAT_0086b930;

        // Access global manager: DAT_012233a0 is likely a pointer to a singleton manager
        // Its second field (at +4) points to another object. Subtract 0x1f30 to get back to containing struct (if embedded).
        if ((*(int **)(DAT_012233a0 + 4) != 0) &&
            (iVar2 = *(int **)(DAT_012233a0 + 4) + -0x1f30, iVar2 != 0)) {
            // Notify manager of removal (FUN_00717730 takes pointer and 0)
            FUN_00717730(iVar2, 0);
        }
    }
}