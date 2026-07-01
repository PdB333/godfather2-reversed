// FUNC_NAME: LinkedNode::~LinkedNode
void __fastcall LinkedNode::~LinkedNode(int this)
{
    // Temporary buffer for unlinking from list
    char swapBuffer[8];
    
    // Unlink this node from its doubly linked list: passes this->prevPtr, this->prev, and this
    FUN_008ee740(swapBuffer, this, **(int**)(this + 4), this, *(int*)(this + 4));
    
    // Free the node pointed to by field at offset +0x4 (likely a sibling or child)
    FUN_009c8eb0(*(int*)(this + 4));
    
    // Clear both pointer fields
    *(int*)(this + 4) = 0;
    *(int*)(this + 8) = 0;
}