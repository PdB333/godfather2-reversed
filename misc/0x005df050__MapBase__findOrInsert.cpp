// FUNC_NAME: MapBase::findOrInsert
undefined4* __thiscall MapBase::findOrInsert(uint* keyPtr)
{
    // this+0x1c: pointer to tree header node
    node* header = *(node**)(this + 0x1c);
    node* cur = header;
    node* target;

    // If the tree is not empty (header's parent has interior flag)
    // Header->parent is the root node (offset 0x04 from header)
    if (*(char*)((int)header->parent + 0x15) == '\0')
    {
        target = (node*)header->parent; // root
        do {
            // Compare keys (offset 0x0C from node)
            if (target->key < *keyPtr)
            {
                // Go right (offset 0x08)
                cur = target;
                target = (node*)target->right;
            }
            else
            {
                // Go left (offset 0x00)
                cur = target;
                target = (node*)target->left;
            }
        } while (*(char*)((int)target + 0x15) == '\0'); // while interior node
    }

    // If we ended at header or key should be inserted before cur
    if (cur == header || *keyPtr < cur->key)
    {
        // Prepare insertion data: key and a placeholder
        uint insertData[2] = { *keyPtr, 0 };
        int* ret = FUN_005dfb70(this, stackBuf, insertData, this, cur);
        // Update this and cur from the inserted node
        this = (int)*ret;
        cur = (node*)ret[1];
    }

    // Safety checks
    if (this == 0)
        FUN_00b97aea();
    if (cur == header)
        FUN_00b97aea();

    // Return pointer to value field (offset 0x04 from node)
    return (undefined4*)((int)cur + 4);
}