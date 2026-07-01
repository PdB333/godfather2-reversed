// FUNC_NAME: SomeClass::handleMessage
uint SomeClass::handleMessage(int *param_1) // param_1 is this pointer (vtable at *this)
{
    char cVar1;
    int *unaff_ESI; // likely a pointer to some object (e.g., manager)
    int *unaff_retaddr; // likely a second parameter (e.g., message data)
    uint in_stack_00001f50; // stack parameter (maybe flags or message ID)
    undefined4 local_4; // local variable used as output parameter

    local_4 = 0;
    // Call virtual function at vtable+0x10 with message ID 0x383225a1
    cVar1 = (**(code **)(*param_1 + 0x10))(0x383225a1);
    if ((cVar1 == '\0') || (unaff_ESI == 0)) {
        // First message not handled or unaff_ESI is null
        local_4 = 0;
        // Call virtual function with second message ID and address of local_4 as output
        cVar1 = (**(code **)(*unaff_retaddr + 0x10))(0x383225a1, &local_4);
        if ((cVar1 != '\0') && (unaff_ESI != 0)) {
            // Second message handled and unaff_ESI not null
            cVar1 = (**(code **)(*param_1 + 0x10))(0x369ac561, &stack0xfffffff4); // stack variable? likely a parameter
            if ((cVar1 != '\0') && (&local_4 != (undefined4 *)0x0)) {
                // Return a bit-extracted value from the stack parameter
                return in_stack_00001f50 >> 9 & 0xffffff01;
            }
        }
    }
    else {
        // First message handled and unaff_ESI not null
        local_4 = 0;
        // Call virtual function with second message ID and address of local_4
        cVar1 = (**(code **)(*unaff_retaddr + 0x10))(0x369ac561, &local_4);
        if ((cVar1 != '\0') && (unaff_ESI != 0)) {
            // Call some global function with a global pointer
            FUN_0043b870(DAT_01131018);
            // Call another function with unaff_ESI
            cVar1 = FUN_009af6f0(unaff_ESI);
            return (uint)(cVar1 == '\0');
        }
    }
    return 0;
}