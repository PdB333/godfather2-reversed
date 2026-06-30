// FUNC_NAME: EARSObject::freeSlotList
void EARSObject::freeSlotList(void)
{
    // This function appears to iterate over a small array (4 entries) of slot structures,
    // each slot containing a pointer to a linked list node. It removes each node from its
    // parent list if the slot is active (field at -0x0C != 0), not a "dead" sentinel (0x2a7ed975),
    // and the node pointer (at -0x24 from iteration base) is non-zero.

    int iVar1;           // node value from field at -0x20
    int iVar2;           // pointer to next field in parent list
    int *piVar3;         // temporary traversal pointer
    int in_EAX;          // 'this' pointer
    int *piVar4;         // current iteration pointer (starts at this->slotArray[3].end?)
    int iVar6;           // loop counter (3 to 0)
    int *piVar5;         // base pointer of current slot entry (points to node pointer)

    iVar6 = 3;
    // +0x90 is offset to an array of 4 slot structures, each 0x24 bytes (9 ints)
    piVar4 = (int *)(in_EAX + 0x90);

    do {
        // piVar5 points to the beginning of the current slot entry
        // (reverse offset of 9 ints from piVar4)
        piVar5 = piVar4 + -9;

        // Check: slot is active (field at -12 bytes ≠ 0)
        // and the value at -32 bytes is not the sentinel 0x2a7ed975
        // and the node pointer at start of slot (piVar5[0]) is non-zero
        if (((piVar4[-3] != 0) &&
             (iVar1 = piVar4[-8], iVar1 != 0x2a7ed975)) &&
            (iVar2 = *piVar5, iVar2 != 0)) {

            // iVar2 is the parent list's 'next' pointer (at offset +4 of the node)
            // iVar1 is the new 'next' value to link (current node's stored successor)
            piVar4 = *(int **)(iVar2 + 4);

            if (piVar4 == piVar5) {
                // If the parent points directly to this slot node, update it
                *(int *)(iVar2 + 4) = iVar1;
            }
            else {
                // Otherwise, traverse the linked list until we find the node
                piVar3 = (int *)piVar4[1];
                while (piVar3 != piVar5) {
                    piVar4 = (int *)piVar4[1];
                    piVar3 = (int *)piVar4[1];
                }
                // Bypass the current node
                piVar4[1] = iVar1;
            }

            // Clear the slot's node pointer (mark as free)
            *piVar5 = 0;
        }

        iVar6 = iVar6 + -1;
        // Move to the previous slot entry
        piVar4 = piVar5;
    } while (-1 < iVar6);

    return;
}