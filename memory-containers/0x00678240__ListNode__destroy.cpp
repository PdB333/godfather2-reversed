// FUNC_NAME: ListNode::destroy
void __thiscall ListNode::destroy() {
    // this: node to destroy (pointer to ListNode)
    // +0x00: parent container (List*)
    int* parent = *reinterpret_cast<int**>(this);
    if (parent == nullptr) return;

    // +0x14: first child node pointer
    int* firstChild = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x14);
    if (firstChild == reinterpret_cast<int*>(parent[0x38])) {
        parent[0x70 / 4] = 1; // flag: first child cleared
    } else if (firstChild != nullptr) {
        // Remove child from parent's array and decrement count
        int childIndex = *(reinterpret_cast<int*>(firstChild) - 2);
        *reinterpret_cast<int*>(parent[0x0c / 4] + childIndex * 4) = 0;
        parent[0x04 / 4]--;
        // Free child allocation (header at child - 0x10)
        DAT_01206694(reinterpret_cast<char*>(firstChild) - 0x10);
    }

    // +0x3C (0x0f * 4): some pointer (maybe tail?)
    int* somePtr = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x3C);
    if (somePtr != reinterpret_cast<int*>(this) + 5 && somePtr != nullptr) {
        int tailIndex = *(reinterpret_cast<int*>(somePtr) - 2);
        *reinterpret_cast<int*>(parent[0x0c / 4] + tailIndex * 4) = 0;
        parent[0x04 / 4]--;
        DAT_01206694(reinterpret_cast<char*>(somePtr) - 0x10);
    }

    // +0x64 (0x19 * 4): last child node pointer
    int* lastChild = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x64);
    if (lastChild == reinterpret_cast<int*>(parent[0x40 / 4])) {
        parent[0x78 / 4] = 1; // flag: last child cleared
    } else if (lastChild != nullptr) {
        int lastIndex = *(reinterpret_cast<int*>(lastChild) - 2);
        *reinterpret_cast<int*>(parent[0x0c / 4] + lastIndex * 4) = 0;
        parent[0x04 / 4]--;
        DAT_01206694(reinterpret_cast<char*>(lastChild) - 0x10);
    }

    // +0x58 (0x16 * 4): another child pointer
    int* anotherChild = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x58);
    if (anotherChild != nullptr) {
        int childIndex2 = *(reinterpret_cast<int*>(anotherChild) - 2);
        *reinterpret_cast<int*>(parent[0x0c / 4] + childIndex2 * 4) = 0;
        parent[0x04 / 4]--;
        DAT_01206694(reinterpret_cast<char*>(anotherChild) - 0x10);
    }

    // Now check if this node is the root of the list
    if (this == reinterpret_cast<ListNode*>(parent[0x34 / 4])) {
        parent[0x6c / 4] = 1; // flag: root cleared
        return;
    }

    // Otherwise, remove this node from parent's array and free it
    int thisIndex = *(reinterpret_cast<int*>(this) - 2);
    *reinterpret_cast<int*>(parent[0x0c / 4] + thisIndex * 4) = 0;
    parent[0x04 / 4]--;
    DAT_01206694(reinterpret_cast<char*>(this) - 0x10);
}