// FUNC_NAME: SomeClass::init
void __thiscall SomeClass::init(int param_2, int param_3)
{
    undefined4 uVar1;

    if (param_2 != 0) {
        uVar1 = FUN_0060a380(); // Allocate or create component A
        *(undefined4 *)(this + 0x10) = uVar1; // Store at offset +0x10
    }
    if (param_3 != 0) {
        uVar1 = FUN_0060a2e0(param_3); // Allocate or create component B with param_3
        *(undefined4 *)(this + 0x14) = uVar1; // Store at offset +0x14
    }
    FUN_006127d0(); // Global initialization step
    FUN_006181d0(); // Another initialization step
    return;
}