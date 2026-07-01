// FUNC_NAME: EASTLIntrusiveList::insert
void __thiscall EASTLIntrusiveList::insert(int thisPtr, int* outNewNode, int positionNode, uint* data, bool insertAfter)
{
    int newNode;
    bool shouldInsertAfter;

    // Determine insertion direction: if not forced to insert after, and position is not sentinel,
    // and position node's key <= new key, then insert after; otherwise insert before.
    if (!insertAfter && (positionNode != thisPtr + 4) && (*(uint*)(positionNode + 0x10) <= *data)) {
        shouldInsertAfter = true;
    } else {
        shouldInsertAfter = false;
    }

    // Allocate new node (size 0x24 = 36 bytes) using EASTL debug allocator
    newNode = FUN_0068ab90(0x24, "EASTL", 0, 0,
                           "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);

    // Copy key and value(s) into new node
    if (newNode != 0) {
        *(uint*)(newNode + 0x10) = *data;               // key at offset +0x10
        FUN_004dba00(data[1], data[2]);                  // copy value(s) at offsets +0x14, +0x18
    }

    // Link new node into the list (before or after positionNode, using sentinel at this+4)
    FUN_00ab3da0(newNode, positionNode, thisPtr + 4, shouldInsertAfter);

    // Increment container size
    *(int*)(thisPtr + 0x14) += 1;

    // Return new node pointer
    *outNewNode = newNode;
}