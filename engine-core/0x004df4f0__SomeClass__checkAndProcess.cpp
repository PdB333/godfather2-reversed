// FUNC_NAME: SomeClass::checkAndProcess
void __thiscall SomeClass::checkAndProcess(void)
{
    int *thisPtr; // in_EAX
    int *piVar1;
    int iVar2;

    // Check if first two fields are zero and second two fields are zero
    if (thisPtr[0] == 0 && thisPtr[1] == 0) {
        if (thisPtr[2] == 0 && thisPtr[3] == 0) {
            goto LAB_004df528; // All fields zero -> process
        }
        if (thisPtr[2] != 0 || thisPtr[3] != 0) {
            goto LAB_004df50e; // Second pair non-zero -> check resource
        }
LAB_004df522:
        iVar2 = 0;
    }
    else {
LAB_004df50e:
        // First pair non-zero or second pair non-zero -> try to get resource
        piVar1 = (int *)FUN_004e0f60(); // Possibly getResource() or getManager()
        if (piVar1 == (int *)0x0) {
            goto LAB_004df522; // No resource -> skip
        }
        iVar2 = *piVar1; // Check first field of resource
    }
    if (iVar2 == 0) {
        return; // Resource not valid -> skip
    }
LAB_004df528:
    FUN_0051a9f0(); // Process function (e.g., update, execute)
    return;
}