// FUNC_NAME: FreeList::popNode

struct Node {
    void* vtable;          // +0x00
    int field4;            // +0x04
    int relativeOffset;    // +0x08 (self-relative pointer to next node, resolved on activate)
    int fieldC;            // +0x0C
};

class FreeList {
    Node* m_head;          // +0x14
    Node* m_current;       // +0x1C
public:
    Node* popNode();
};

Node* FreeList::popNode()
{
    Node* node = m_head;       // +0x14
    m_current = node;          // +0x1C
    if (node != nullptr)
    {
        // Initialize the node's vtable and zero out fields
        node->vtable = (void*)&PTR_FUN_00e36678; // VTable pointer
        node->field4 = 0;       // +0x04
        node->fieldC = 0;       // +0x0C

        // Resolve self-relative offset to an absolute pointer (if any)
        if (node->relativeOffset != 0)
        {
            node->relativeOffset = (int)node + node->relativeOffset;
        }
        return node;
    }
    return nullptr;
}