// FUNC_NAME: EARSCharacter::updateState
void __thiscall EARSCharacter::updateState(int *this, int someID, char forceSkip)
{
    char cVar1;
    uint uVar2;
    int nodePtr;
    int *slotPtr;
    bool bVar5;

    // Skip major update if list head is null
    if (this[0x86] == 0) goto LAB_0045e4c5;

    // iVar3 = node->someField (offset 0x14 from node)
    nodePtr = *(int *)(this[0x86] + 0x14);

    // Check if we should early-out: same node and global state, not forced
    if ((nodePtr == this[0x8b]) && (this[0x8b] != -1) && 
        (DAT_01205224 == this[0x8d]) && (forceSkip == '\0')) 
        goto LAB_0045e4c5;

    // Update tracked IDs
    this[0x8d] = DAT_01205224;
    this[0x8b] = nodePtr;

    bVar5 = false;

    // Flags check: bit0 of m_flags not set, and (globalFlag false or bit2 set)
    if (((this[0x61] & 1U) == 0) && 
        ((DAT_012053ca == '\0' || ((this[0x61] & 4U) != 0)))) 
    {
        if (this[0x60] != 0) 
        {
            bVar5 = false;
            goto LAB_0045e406;
        }
        cVar1 = (**(code **)(*this + 0x140))();  // virtual check
        bVar5 = cVar1 == '\0';
        if (!bVar5) goto LAB_0045e406;
    }
    else 
    {
LAB_0045e406:
        this[0x61] = this[0x61] | 4;   // set bit2
    }

    // Compute mask based on flags
    uVar2 = -(uint)bVar5 & 0x1000;
    if ((char)this[0x9d] != '\0') {
        uVar2 = uVar2 | 0x100000;
    }
    if (*(char *)((int)this + 0x275) != '\0') {
        uVar2 = uVar2 | 0x4000;
    }
    if (*(char *)((int)this + 0x276) != '\0') {
        uVar2 = uVar2 | 0x100;
    }

    // Traverse linked list (offset 0x124 is next pointer)
    for (nodePtr = this[0x86]; nodePtr != 0; nodePtr = *(int *)(nodePtr + 0x124)) 
    {
        *(uint *)(nodePtr + 0x10) = (*(uint *)(nodePtr + 0x10) & 0xffefaeff) | uVar2;
    }

    // Call external function with someID and three 64-bit values from this+0x9e,0xa0,0xa2
    nodePtr = FUN_00571890(someID, *(undefined8 *)(this + 0x9e), 
                           *(undefined8 *)(this + 0xa0), 
                           *(undefined8 *)(this + 0xa2));
    if ((this[0x9a] != 0) && (nodePtr != 0)) {
        FUN_0056f8d0();  // some action
    }

LAB_0045e4c5:
    // Check bit3 of flags: if set and list exists, and node has certain flags or low float
    if (((this[0x61] & 8U) != 0) && (nodePtr = this[0x86], nodePtr != 0) &&
        ((*(uint *)(nodePtr + 0x10) & 0x2000003) != 0 || 
         (*(float *)(nodePtr + 0x24) <= DAT_00e2b1a4))) 
    {
        this[0x61] = this[0x61] & 0xfffffff7;  // clear bit3
        (**(code **)(*this + 0x180))();  // virtual update
    }

    // Process 8 slots starting at this+0x90
    slotPtr = this + 0x90;
    for (int i = 8; i > 0; i--, slotPtr++) 
    {
        if (*slotPtr != 0) {
            (**(code **)(*this + 0xb8))();  // virtual per-slot
        }
    }

    // Check bit5 of flags: if set, and condition on this[0x19] pointer
    if ((*(byte *)(this + 0x61) & 0x20) != 0) 
    {
        nodePtr = this[0x19];
        if ((nodePtr == 0) ||
            (((*(uint *)(nodePtr + 0x30) >> 1 & 1) == 0 && 
              ((*(byte *)(nodePtr + 0x3c) & 1) == 0)))) 
        {
            (**(code **)(*this + 0x16c))();  // virtual cleanup
        }
        this[0x61] = this[0x61] & 0xffffffdf;  // clear bit5
    }
    return;
}