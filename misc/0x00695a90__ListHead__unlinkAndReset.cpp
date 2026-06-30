// FUNC_NAME: ListHead::unlinkAndReset
struct Node {
    Node* prev;   // +0x00
    Node* next;   // +0x04
    Node* somePtr; // +0x08
};

void __fastcall ListHead::unlinkAndReset(void* thisPtr)
{
    Node* node = *(Node**)((int)thisPtr + 4);  // this->nodePtr
    // Release whatever was held in the old next pointer (handle/ID)
    FUN_006956b0(*(int*)((int)node + 4));      // node->next as integer
    // Reinitialize node as a self‑referencing circular list element
    node->next = node;
    *(int*)((int)thisPtr + 8) = 0;            // clear count/flag at this+0x08
    node->prev = node;
    node->somePtr = node;
}