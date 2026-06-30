// FUNC_NAME: HashTable::moveToFront
void __fastcall HashTable::moveToFront(int this)
{
    int iVar1;
    ushort *in_EAX;
    int iVar2;
    
    // Hash table lookup: param_1+0xc is the hash table array
    // in_EAX points to a key structure: [ushort key0, ushort key1, int key2]
    // Hash is computed as (key0 * 0x10 + key2 + key1) & 0x7f
    iVar2 = *(int *)(*(int *)(this + 0xc) +
                    ((uint)*in_EAX * 0x10 + *(int *)(in_EAX + 2) + (uint)in_EAX[1] & 0x7f) * 4);
    if (iVar2 != 0) {
        // Walk the linked list to find matching entry
        while (((*(ushort *)(iVar2 + 0x62) != in_EAX[1] || (*(ushort *)(iVar2 + 0x60) != *in_EAX)) ||
               (*(int *)(iVar2 + 100) != *(int *)(in_EAX + 2)))) {
            iVar2 = *(int *)(iVar2 + 4); // next pointer
            if (iVar2 == 0) {
                return;
            }
        }
        // If found and not already at front
        if (iVar2 != *(int *)(this + 0x14)) {
            // Remove from current position
            if (iVar2 == *(int *)(this + 0x18)) {
                *(undefined4 *)(this + 0x18) = *(undefined4 *)(iVar2 + 0xc);
            }
            else {
                *(undefined4 *)(*(int *)(iVar2 + 0x10) + 0xc) = *(undefined4 *)(iVar2 + 0xc);
            }
            *(undefined4 *)(*(int *)(iVar2 + 0xc) + 0x10) = *(undefined4 *)(iVar2 + 0x10);
            // Insert at front
            iVar1 = *(int *)(this + 0x14);
            *(int *)(iVar2 + 0x10) = iVar1;
            *(int *)(iVar1 + 0xc) = iVar2;
            *(int *)(this + 0x14) = iVar2;
            *(undefined4 *)(iVar2 + 0xc) = 0;
        }
    }
    return;
}