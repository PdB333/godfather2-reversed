// FUNC_NAME: TreeBase::insertOrFind
void __thiscall TreeBase::insertOrFind(int this, undefined4 *outNode, undefined4 key)
{
    undefined4 *current;
    undefined4 *parent;
    int compareResult;
    bool goRight;

    // Tree structure:
    // +0x00: ??? (maybe header sentinel)
    // +0x04: parent pointer (initial anchor)  
    // +0x08: rightmost/end sentinel pointer
    // +0x0C: root node pointer
    // Node structure (assumed 12 bytes):
    // +0x00: left child pointer
    // +0x04: right child pointer
    // +0x08: key value (actual key compared)

    current = *(undefined4 **)(this + 0xC); // root
    parent = (undefined4 *)(this + 4);      // initial parent anchor

    // Standard BST descent using comparison
    while (current != (undefined4 *)0x0) {
        // Note: FUN_004d4b20 compares current->key with insertion key?
        // Decompiled shows only one arg (node+4), but likely takes two:
        // compareResult = compareKey(*(undefined4*)(current + 8), key);
        // Actually passed "current + 4", which suggests key at offset +4?
        // Assuming node structure: left(0), key(4), right(8) 
        // Then compare on key at +4.
        compareResult = FUN_004d4b20(current + 4); 
        goRight = compareResult < 0;
        parent = current;
        if (goRight) {
            current = (undefined4 *)*(current + 1); // right child (offset 4? or 8?)
        } else {
            current = (undefined4 *)*current;        // left child (offset 0)
        }
    }

    // After loop, 'parent' is the node that would be the parent of the new node
    // If last move was right and parent equals the rightmost sentinel, tree empty?
    if (goRight && parent == *(undefined4 **)(this + 8)) {
        // Insert as first node (or root)
        FUN_00699df0(&key, parent, key, 0); // allocate and link
        *outNode = key;
        *(unsigned char*)(outNode + 1) = 1; // flag: inserted
        return;
    }

    // Otherwise, find the inorder predecessor for comparison
    current = (undefined4 *)FUN_00ab3c90(parent); // predecessor of parent
    compareResult = FUN_004d4b20(key);            // compare insertion key with predecessor? Or with parent?
    if (compareResult < 0) {
        // Insert as left child of parent
        FUN_00699df0(&key, parent, key, 0);
        *outNode = key;
        *(unsigned char*)(outNode + 1) = 1; // inserted
        return;
    }

    // Key already exists (or should be placed elsewhere)
    *outNode = current; // returning the existing node
    *(unsigned char*)(outNode + 1) = 0; // not inserted
    return;
}