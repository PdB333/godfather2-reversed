// FUN_NAME: Node::destroy
// Address: 0x00729ba0
// Purpose: Removes a node from a doubly linked list and calls cleanup/deallocation.
// The node is embedded within a larger object at offsets +0x48 (self pointer to the node's next pointer?),
// +0x4c (previous node), +0x50 (next node or list head handle).
// The exactly intended logic is obscured by the decompiler's type confusion, but the pattern matches
// a typical list unlink-and-free sequence. The two callees likely perform reference counting and memory release.
void Node::destroy() {
    if (this == nullptr) return;

    // Offsets (relative to 'this'):
    // +0x48: Node** m_ppSelfPointer (maybe pointer to the embedded node's own 'next' pointer)
    // +0x4c: Node* m_pPrev (previous node in the list)
    // +0x50: Node* m_pNext (next node or list anchor)
    Node** ppSelf = (Node**)((uintptr_t)this + 0x48);
    Node*  pPrev  = *(Node**)((uintptr_t)this + 0x4c);
    Node*  pNext  = *(Node**)((uintptr_t)this + 0x50);

    // This block seems to re-read the previous pointer and then store the address of the local ppSelf
    // into the prev field. This is likely a decompilation artifact; the original probably does something
    // like: this->m_pPrev = ppSelf; (i.e., linking backward to the embedded list entry).
    if (ppSelf != nullptr) {
        pPrev = *(Node**)((uintptr_t)this + 0x4c); // redundant read
        *(Node***)((uintptr_t)this + 0x4c) = &ppSelf; // store stack address - bug or misdecompile
    }

    // Release or decrement the reference of the next node (or list head)
    FUN_00729a50(&pNext);

    // If the self-pointer was valid, clean up the embedded list entry (maybe free the node)
    if (ppSelf != nullptr) {
        FUN_004daf90(&ppSelf);
    }
}