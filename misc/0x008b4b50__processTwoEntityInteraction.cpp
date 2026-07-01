// FUNC_NAME: processTwoEntityInteraction
void processTwoEntityInteraction(void)
{
    char cVar1;
    undefined4 uVar2;
    undefined1 *puVar3;
    int *piVar4;
    int *piVar5;
    undefined4 uVar6;
    undefined4 *puVar7;
    int in_stack_00000010; // handle1
    int in_stack_0000001c; // handle2
    int in_stack_00000028; // handle3
    byte in_stack_00000034; // flags1
    int in_stack_00000044; // handle4
    int in_stack_00000050; // handle5
    int in_stack_0000005c; // handle6
    byte in_stack_00000068; // flags2
    int iStack_28; // resolved object1
    int iStack_24; // resolved object2
    undefined1 *local_20; // string1
    code *local_14; // destructor for string1
    undefined1 *local_10; // string2
    code *pcStack_4; // destructor for string2

    if (((in_stack_00000034 & 1) != 0) && ((in_stack_00000068 & 1) != 0)) {
        uVar2 = FUN_004bb600(&stack0x00000004); // duplicate string from stack offset 0x04
        FUN_004d3b50(uVar2); // free duplicated string? (maybe a no-op)
        uVar2 = FUN_004bb600(&stack0x00000038); // duplicate another string
        FUN_004d3b50(uVar2);
        puVar3 = local_10;
        if (local_10 == (undefined1 *)0x0) {
            puVar3 = &DAT_0120546e; // default empty string
        }
        piVar4 = (int *)FUN_00568320(puVar3); // look up object by name
        puVar3 = local_20;
        if (local_20 == (undefined1 *)0x0) {
            puVar3 = &DAT_0120546e;
        }
        piVar5 = (int *)FUN_00568320(puVar3);
        if ((piVar4 != (int *)0x0) && (piVar5 != (int *)0x0)) {
            uVar2 = (**(code **)(*piVar4 + 0xc))(); // virtual call: getID or getHash
            uVar6 = (**(code **)(*piVar5 + 0xc))(); // virtual call
            FUN_008b3d60(&iStack_28, &stack0x0000000c); // resolve handle to object
            FUN_008b3d60(&iStack_24, &stack0x00000040);
            if ((iStack_28 != 0) &&
               (((*(int *)(iStack_28 + 4) != 0 && (iStack_24 != 0)) && (*(int *)(iStack_24 + 4) != 0)))) {
                puVar7 = (undefined4 *)FUN_008b4100(&stack0x0000000c); // get pointer from handle
                cVar1 = (**(code **)(*(int *)*puVar7 + 0x14))(uVar6); // virtual: canInteract?
                if (cVar1 != '\0') {
                    puVar7 = (undefined4 *)FUN_008b4100(&stack0x00000040);
                    cVar1 = (**(code **)(*(int *)*puVar7 + 0x14))(uVar2);
                    if (cVar1 != '\0') {
                        puVar7 = (undefined4 *)FUN_008b4100(&stack0x0000000c);
                        (**(code **)(*(int *)*puVar7 + 0x10))(uVar6); // virtual: doAction
                        puVar7 = (undefined4 *)FUN_008b4100(&stack0x0000003c);
                        (**(code **)(*(int *)*puVar7 + 0x10))(uVar2);
                    }
                }
            }
        }
        if (local_20 != (undefined1 *)0x0) {
            (*local_14)(local_20); // free string1
        }
        if (local_10 != (undefined1 *)0x0) {
            (*pcStack_4)(local_10); // free string2
        }
    }
    if (in_stack_00000028 != 0) {
        FUN_009c8f10(in_stack_00000028); // release handle
    }
    if (in_stack_0000001c != 0) {
        FUN_009c8f10(in_stack_0000001c);
    }
    if (in_stack_00000010 != 0) {
        FUN_009c8f10(in_stack_00000010);
    }
    if (in_stack_0000005c != 0) {
        FUN_009c8f10(in_stack_0000005c);
    }
    if (in_stack_00000050 != 0) {
        FUN_009c8f10(in_stack_00000050);
    }
    if (in_stack_00000044 != 0) {
        FUN_009c8f10(in_stack_00000044);
    }
    return;
}