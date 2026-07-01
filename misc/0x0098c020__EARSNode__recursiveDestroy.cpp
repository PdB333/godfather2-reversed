// FUNC_NAME: EARSNode::recursiveDestroy
// Address: 0x0098c020
// This function recursively frees a tree of nodes using child-sibling representation.
// Node layout (based on offsets):
//   +0x00 : firstChild (EARSNode*)
//   +0x04 : nextSibling (EARSNode*)
//   +0x14 : dataPtr (void*)
//   +0x20 : dataDestructor (void (*)(void*))

struct EARSNode
{
    EARSNode* firstChild;   // +0x00
    EARSNode* nextSibling;  // +0x04
    void* dataPtr;          // +0x14
    void (*dataDestructor)(void*); // +0x20
};

void EARSNode::recursiveDestroy(EARSNode* node)
{
    if (node == nullptr)
        return;

    do
    {
        // Recursively destroy the first child subtree
        recursiveDestroy(node->firstChild);

        EARSNode* nextSibling = node->nextSibling;

        // If there is attached data, call its destructor
        if (node->dataPtr != nullptr)
        {
            node->dataDestructor(node->dataPtr);
        }

        // Deallocate the current node (likely calling operator delete or a pool deallocator)
        FUN_009c8f10(node); // internal node deallocation function

        node = nextSibling;
    } while (node != nullptr);
}