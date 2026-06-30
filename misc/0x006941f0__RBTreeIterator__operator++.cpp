// FUNC_NAME: RBTreeIterator::operator++

// Increments an iterator for a red-black tree (or similar ordered container).
// Node structure offsets:
//   +0x00: void* left (or parent in some context)
//   +0x04: void* parent (or previous)
//   +0x08: void* right (or next)
//   +0x29: char color/flag (0 = sentinel, non-zero = real node)
// Iterator structure (param_1):
//   [0] : void* sentinel (nil node)
//   [1] : void* current node pointer

void __fastcall RBTreeIterator::operator++(int* iterator)
{
    char cFlag;
    int* pNode;
    int* pRight;
    int* pParent;
    int* pTemp;

    if (iterator[0] == 0) {
        FUN_00b97aea(); // sentinel is null – error
    }

    pNode = (int*)iterator[1];
    if (*(char*)(pNode + 0x29) == '\0') {
        FUN_00b97aea(); // current node is sentinel – cannot increment
        return;
    }

    pRight = *(int**)((char*)pNode + 8);
    if (*(char*)((int)pRight + 0x29) != '\0') { // right child exists
        // Standard increment: traverse up until we come from a left child
        pParent = *(int**)((char*)pNode + 4);
        cFlag = *(char*)((int)pParent + 0x29);
        while (cFlag == '\0' && (iterator[1] == *(int*)((int)pParent + 8))) {
            iterator[1] = (int)pParent;
            pParent = *(int**)((char*)pParent + 4);
            cFlag = *(char*)((int)pParent + 0x29);
        }
        iterator[1] = (int)pParent;
        return;
    }
    else {
        // No right child: navigate to leftmost descendant of current node's subtree
        // (This branch appears to handle the case where the tree is actually traversed
        //  in a different order – possibly a custom variant)
        cFlag = *(char*)(*pRight + 0x29);
        pTemp = pRight;
        while (cFlag == '\0') {
            cFlag = *(char*)(*pTemp + 0x29);
            pRight = pTemp;
            pTemp = (int*)*pTemp;
        }
        iterator[1] = (int)pRight;
        return;
    }
}