// FUNC_NAME: MergeIterator::next
// Function address: 0x00587fc0
// This function advances a merge iterator over two sorted lists and returns the next smallest element.
// The iterator structure is passed via param_2 (edx) and has:
//   +0x00: targetKey (int) – the key to stop at (or -1 for no stop)
//   +0x04: leftPtr (int*) – pointer to current node in left list (node = value + next pointer)
//   +0x08: rightPtr (int*) – pointer to current node in right list
//   +0x0C: endPtr (int*) – pointer to the sentinel (one past the last node)
// Each node is at least 12 bytes (?) but key extraction uses offsets 0, 0xB, 5, 7 depending on flags.
// The function returns the value (int) of the yielded node, or 0 if both lists exhausted.

int __fastcall MergeIterator_next(int targetKey, MergeIterator* it) {
    int* leftNode = (int*)it->leftPtr;
    int* rightNode = (int*)it->rightPtr;

    if (leftNode == nullptr) {
        goto processRight;
    }

    if (rightNode != nullptr) {
        int leftVal = *leftNode; // value of left node
        // Extract key from left node
        int leftKey;
        if (((*(unsigned char*)((char*)leftVal + 0xB) & 0x20) == 0) || (*leftVal < 4)) {
            leftKey = 0;
        } else {
            leftKey = *(int*)((char*)leftVal + 0x14); // offset 20 (5*4)
        }

        int rightVal = *rightNode;
        int rightKey;
        if (((*(unsigned char*)((char*)rightVal + 0xB) & 0x20) == 0) || (*rightVal < 4)) {
            rightKey = 0;
        } else {
            rightKey = *(int*)((char*)rightVal + 0x14);
        }

        if (rightKey < leftKey) {
            goto processRight;
        }
    }

    // Yield from left list
    int result = *leftNode;
    it->leftPtr = (int*)((int*)it->leftPtr + 1); // advance to next pointer
    leftNode = (int*)it->leftPtr;
    if (leftNode < it->endPtr) {
        leftNode = (int*)*leftNode; // dereference next pointer
        int newKey;
        if (((*(unsigned char*)((char*)leftNode + 0xB) & 0x20) == 0) || (*leftNode < 2)) {
            newKey = *(int*)((char*)leftNode + 0x14); // offset 20
        } else {
            newKey = *(int*)((char*)leftNode + 0x1C); // offset 28 (7*4)
        }
        if (newKey == targetKey) {
            return result;
        }
    }
    it->leftPtr = nullptr;
    return result;

processRight:
    if (rightNode == nullptr) {
        return 0;
    }
    int result = *rightNode;
    it->rightPtr = (int*)((int*)it->rightPtr + 1);
    rightNode = (int*)it->rightPtr;
    if (rightNode < it->endPtr) {
        rightNode = (int*)*rightNode;
        int newKey;
        if (((*(unsigned char*)((char*)rightNode + 0xB) & 0x20) == 0) || (*rightNode < 2)) {
            newKey = *(int*)((char*)rightNode + 0x14);
        } else {
            newKey = *(int*)((char*)rightNode + 0x1C);
        }
        if (newKey == targetKey) {
            return result;
        }
    }
    it->rightPtr = nullptr;
    return result;
}