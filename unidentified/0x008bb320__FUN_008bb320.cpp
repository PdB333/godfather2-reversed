// FUNC_NAME: SomeClass::updateThingOrTick
void __thiscall SomeClass::updateThingOrTick(int *this, int param_2)
{
    int *piVar1;
    int iVar2;

    // Some subsystem update calls
    FUN_0046f160(param_2);
    FUN_008b9590(param_2);

    // Check if bit 0 of byte at +0x18F (399 = 0x18F) is set, and dword at +0x194 (0x65*4 = 0x194) is non-zero
    if (((*(byte *)((int)this + 399) & 1) != 0) && (this[0x65] != 0)) {
        // Call some function on the object referenced by this[0x65]
        iVar2 = FUN_006b0ee0(this[0x65]);
        if ((iVar2 != 0) &&
           // Check bit 22 (0x16) of dword at iVar2+0x34 is clear
           (((~(byte)(*(uint *)(iVar2 + 0x34) >> 0x16) & 1) == 0 &&
            // And dword at +0x130 (0x4c*4 = 0x130) is non-null
            (piVar1 = (int *)this[0x4c], piVar1 != (int *)0x0)))) {
            // Some effect/state reset
            FUN_004a56e0();
            // Call vtable function at +0x154 (offset 0x55 * 4)
            (**(code **)(*this + 0x154))(0);
            // Call vtable function at +0x2c on the object at this[0x4c]
            (**(code **)(*piVar1 + 0x2c))();
        }
    }
    return;
}