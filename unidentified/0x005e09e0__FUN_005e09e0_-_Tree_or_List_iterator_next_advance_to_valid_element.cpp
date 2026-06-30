// FUNC_NAME: FUN_005e09e0 - Tree or List iterator next/advance to valid element
void FUN_005e09e0(void)
{
    char cVar1;
    int iVar2;
    int *piVar3;
    int *piVar4;
    int *unaff_ESI; // this pointer (likely a tree/list iterator/state struct)

    // If the root node pointer is null, call error handler
    if (*unaff_ESI == 0) {
        FUN_00b97aea();
    }

    iVar2 = unaff_ESI[1]; // current node pointer (offset +0x4)

    // If current node is not valid (character at +0x15 is '\0')...
    if (*(char *)(iVar2 + 0x15) == '\0') {
        piVar3 = *(int **)(iVar2 + 8); // child or sibling pointer at +0x8

        // If the child (or sibling) is valid, go to it
        if (*(char *)((int)piVar3 + 0x15) != '\0') {
            iVar2 = *(int *)(iVar2 + 4); // next node at +0x4
            cVar1 = *(char *)(iVar2 + 0x15);
            // Walk until we find a valid node or the root loop back
            while ((cVar1 == '\0' && (unaff_ESI[1] == *(int *)(iVar2 + 8)))) {
                unaff_ESI[1] = iVar2;
                iVar2 = *(int *)(iVar2 + 4);
                cVar1 = *(char *)(iVar2 + 0x15);
            }
            unaff_ESI[1] = iVar2;
            return;
        }

        // Otherwise, traverse leftmost valid node (linked list style)
        cVar1 = *(char *)(*piVar3 + 0x15); // first node's validity
        piVar4 = (int *)*piVar3; // next in list
        while (cVar1 == '\0') {
            cVar1 = *(char *)(*piVar4 + 0x15);
            piVar3 = piVar4;
            piVar4 = (int *)*piVar4;
        }
        unaff_ESI[1] = (int)piVar3;
        return;
    }

    // Current node is valid, but we still call the error handler? (probably degenerate case)
    FUN_00b97aea();
    return;
}