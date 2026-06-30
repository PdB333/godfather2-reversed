// FUNC_NAME: PointerLink::setNode
// Address: 0x006f0bf0
// Role: Sets the node pointer (offset +0x14) to a new node in an intrusive list.
//       If an existing node is present, it is removed via RemoveNode (FUN_004daf90).
//       The new node's backlink (offset +4) is updated to point to the pointer slot,
//       and the previous backlink value is saved at offset +0x18 for restoration.

// External helper: removes the node at the given pointer-to-pointer location
void RemoveNode(void** ppNode);

class PointerLink {
public:
    void setNode(void* newNode);
private:
    void* m_pNode;         // +0x14 – pointer to the node
    void* m_pPrevBacklink; // +0x18 – saved previous backlink value
};

void __thiscall PointerLink::setNode(void* this, void* newNode)
{
    void** nodeSlot = (void**)((char*)this + 0x14);
    if (*nodeSlot != newNode) {
        if (*nodeSlot != 0) {
            RemoveNode(nodeSlot); // unlink the old node
        }
        *nodeSlot = newNode;
        if (newNode != 0) {
            // Save the node's previous backlink (pointer to a pointer)
            *(void**)((char*)this + 0x18) = *(void**)((char*)newNode + 4);
            // Set the new node's backlink to point to the slot (for O(1) removal)
            *(void***)((char*)newNode + 4) = nodeSlot;
        }
    }
}