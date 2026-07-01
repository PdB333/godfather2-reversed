// FUNC_NAME: SomeClass::handleObjectEvent
void __thiscall SomeClass::handleObjectEvent(int this, int* object, int arg3, int arg4)
{
    char result;
    int buffer[3]; // local_28, used for hash lookup result

    buffer[0] = 0;
    // Call virtual function at vtable+0x10 on object with hash 0x369ac561 and buffer
    result = (*(code**)(*object + 0x10))(0x369ac561, buffer);
    if ((result != 0) && (unaff_ESI != (int*)0x0)) {
        // If lookup succeeded and global ESI pointer is valid, call virtual at vtable+0x1c
        (*(code**)(*unaff_ESI + 0x1c))(unaff_retaddr);
    }
    // Call initialization/processing function with this, return address, and arg4
    FUN_0083cac0(this, unaff_retaddr, arg4);
    // Call global function with a global data pointer, object+0xf, stack variable, and 0
    FUN_00408bb0(&DAT_0112dc58, object + 0xf, &stack0xffffffd4, 0);
    // Free dynamically allocated arrays if non-null
    if (aiStack_14[0] != 0) {
        FUN_004daf90(aiStack_14);
    }
    if (aiStack_1c[0] != 0) {
        FUN_004daf90(aiStack_1c);
    }
    return;
}