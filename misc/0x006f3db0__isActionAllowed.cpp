// FUNC_NAME: isActionAllowed
// Function at 0x006f3db0: checks if a given set of action flags is allowed based on game state
// Returns 1 (allowed) or 0 (not allowed)
// Condition: internal state must have certain flags or timer, and none of the bits in param_1&0x0e are set
// Globals:
//   DAT_012233a0: pointer to a structure, presumably some global game manager
//   DAT_01205224: an unsigned int (maybe a timestamp or counter)
int __cdecl isActionAllowed(byte actionFlags)
{
    int iVar1;
    bool bVar2;
    byte bVar3;

    // Dereference global pointer chain: DAT_012233a0 likely points to a struct with a member at offset 4
    // which is a pointer to another struct; we take the int value at that address
    iVar1 = **(int **)(DAT_012233a0 + 4);

    // Check if the pointer is null or equals 0x1f30 (some sentinel value)
    if ((iVar1 == 0) || (iVar1 == 0x1f30)) {
        bVar3 = 0;
    }
    else {
        // Read flag byte from offset iVar1 - 0x164a (negative offset - suggests iVar1 points to a large structure)
        bVar3 = *(byte *)(iVar1 + -0x164a) & 1;

        // Check if there is a timer value at offset iVar1 - 0x7c, and global timer is less than that + 2000
        if ((*(int *)(iVar1 + -0x7c) != 0) && (DAT_01205224 < *(int *)(iVar1 + -0x7c) + 2000U)) {
            bVar2 = true;
            goto LAB_006f3ded;
        }
    }
    bVar2 = false;

LAB_006f3ded:
    // Allow action if either condition is true and no forbidden action bits are set (bits 1-3)
    if (((bVar3 != 0) || (bVar2)) && ((actionFlags & 0xe) == 0)) {
        return 1;
    }
    return 0;
}