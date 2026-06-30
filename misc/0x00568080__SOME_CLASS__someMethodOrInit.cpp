// FUNC_NAME: SOME_CLASS::someMethodOrInit
void __thiscall SomeClass::initWithParam(int *this, int *param_2)
{
    char cVar1;
    char buffer[2048]; // local_800

    if (param_2 != (int *)0x0) {
        // Clear the buffer (0x800 = 2048 bytes)
        FUN_00b220d0(buffer, 0x800);
        FUN_004d3d90(buffer);

        // Store the input pointer at offset +0x0C (this[3])
        this[3] = (int)param_2;

        // Call a virtual method at vtable offset +0x74 on param_2
        // Likely a "register" or "prepare" call with argument 1
        (**(code **)(*param_2 + 0x74))(1);

        // Call another virtual method at vtable offset +0x8c on the stored param_2 object
        cVar1 = (**(code **)(*(int *)this[3] + 0x8c))();
        if (cVar1 != '\0') {
            // If it returned non-zero, call a virtual method at offset +0x68 on 'this' with argument 0
            // Possibly "disable" or "notify"
            (**(code **)(*this + 0x68))(0);
        }
    }
    return;
}