// FUNC_NAME: HashTable::removeEntry

void HashTable::removeEntry(uint *param) // param[0]=key, param[1]=tableIndex
{
    int oldRemoveTarget; // iVar3
    uint key; // uVar2
    int node; // iVar1

    oldRemoveTarget = gRemoveTarget; // DAT_01217d38
    key = param[0];

    // Compute node pointer:
    // base = sTableBases[tableIndex]
    // size = sTableSizes[tableIndex]
    // slot = key % size
    // node = base + slot * 0x1c
    node = *(int *)(&sTableBases + param[1] * 4) +
           (key % *(uint *)(&sTableSizes + param[1] * 4)) * 0x1c;

    // Check if the stored key (at node+0x18) does NOT match the input key,
    // but the stored secondary identifier (at node+0x14) DOES match.
    if ((key != *(uint *)(*(int *)(&sTableBases + param[1] * 4) + 0x18 +
                         (key % *(uint *)(&sTableSizes + param[1] * 4)) * 0x1c)) &&
        (key == *(uint *)(node + 0x14)))
    {
        if (gRemoveLockEnabled != 0) // DAT_01217d34
        {
            LOCK();
            gRemoveTarget = 0; // DAT_01217d38
            UNLOCK();
            if (oldRemoveTarget != 0)
            {
                releaseResource(oldRemoveTarget); // FUN_00ab51e0
            }
        }
        freeNode(node); // FUN_00495490
    }
    return;
}