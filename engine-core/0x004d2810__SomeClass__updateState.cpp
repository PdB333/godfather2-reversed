// FUNC_NAME: SomeClass::updateState
char SomeClass::updateState(void)
{
    undefined4 *puVar1;
    // pointer to some structure at this+0x14
    int *piVar2;
    char cVar3;
    int unaff_ESI;         // this pointer
    uint uVar4;
    int local_c;           // array pointer
    uint local_8;           // array count

    // Get pointer to structure at this+0x14
    puVar1 = *(undefined4 **)(unaff_ESI + 0x14);
    // Set field at offset 4 to 0
    puVar1[1] = 0;
    // Call free on the value at *puVar1
    FUN_009c8f10(*puVar1);
    // Set field at offset 0 to 0
    *puVar1 = 0;
    // Set field at offset 8 to 0
    puVar1[2] = 0;
    // Call some function on this+4
    FUN_00497c00(*(undefined4 *)(unaff_ESI + 4));
    // Set byte at this+0x18 to 0
    *(undefined1 *)(unaff_ESI + 0x18) = 0;

    // If this+8 is non-zero, iterate over an array
    if (*(int *)(unaff_ESI + 8) != 0) {
        uVar4 = 0;
        if (local_8 != 0) {
            do {
                piVar2 = *(int **)(local_c + uVar4 * 4);
                if (piVar2 != (int *)0x0) {
                    // Call virtual function at vtable+0x34 on each element
                    (**(code **)(*piVar2 + 0x34))();
                }
                uVar4 = uVar4 + 1;
            } while (uVar4 < local_8);
        }
    }

    // Determine return value
    cVar3 = '\0';
    if (*(char *)(unaff_ESI + 0x18) == '\0') {
        cVar3 = '\x01';  // Return 1 if flag is 0
    }
    else if (*(int *)(*(int *)(unaff_ESI + 0x14) + 4) != 0) {
        // Call another method and compute return value
        cVar3 = FUN_004d29e0(unaff_ESI);
        cVar3 = (cVar3 != '\0') + '\x02';  // Returns 2 or 3
    }

    // Free the array if it exists
    if (local_c != 0) {
        FUN_009c8f10(local_c);
    }

    return cVar3;
}