// FUNC_NAME: GameObject::isActiveAndNotDisabled
// 0x006ad370 (thunk to 0x006b4860) - Checks if the object is active and not disabled via internal flags and a related object's flags.
int __thiscall GameObject::isActiveAndNotDisabled(void)
{
    // +0x16c: Active/visible status (0 or 1)
    int activeStatus = *(int *)(this + 0x16c);
    // +0x34: Flags bitfield; check bits 0x120000 (bit 17 and 20?) and low bit
    bool flagsOk = ((*(uint *)(this + 0x34) & 0x120000) == 0) && ((*(byte *)(this + 0x34) & 1) == 0);
    // +0x40: Pointer to a related object (e.g., a data block or component)
    int *relatedObj = *(int **)(this + 0x40);
    if (flagsOk && (relatedObj != (int *)0x0))
    {
        // Resolve handle or get pointer from related object
        int *resolved = (int *)FUN_008c74d0((int)relatedObj);
        // +0x84: Flags on the resolved object; check bit 5 (value 0x20) is clear
        if ((resolved != (int *)0x0) && ((~((uint)*(byte *)((int)resolved + 0x84) >> 5) & 1) != 0))
        {
            return activeStatus;
        }
    }
    return 1; // default active = true
}