// FUNC_NAME: EARSLinkedListNode::attachToSentinel(int*)
// Function at 0x006d6930: Attaches this node to a doubly-linked list sentinel located at offset 0x48 of a given owner object.
// If the owner pointer is null, the node is detached from any list.
struct EARSLinkedListNode {
    int* pNext; // +0x00
    int* pPrev; // +0x04
};

// External removal function (detach node)
void __stdcall removeNode(EARSLinkedListNode* node);

int* __thiscall EARSLinkedListNode::attachToSentinel(void* owner) {
    // owner is a pointer to the containing object; list sentinel is at owner + 0x48
    EARSLinkedListNode* sentinel = nullptr;
    if (owner != nullptr) {
        sentinel = reinterpret_cast<EARSLinkedListNode*>(reinterpret_cast<uintptr_t>(owner) + 0x48);
    }

    if (this->pNext != sentinel) {
        if (this->pNext != nullptr) {
            // Remove this node from its current list
            removeNode(this);
        }
        this->pNext = reinterpret_cast<int*>(sentinel);
        if (sentinel != nullptr) {
            // Insert this node after the sentinel (tail insertion)
            this->pPrev = sentinel->pPrev;
            sentinel->pPrev = reinterpret_cast<int*>(this);
        }
    }
    return reinterpret_cast<int*>(this);
}