// FUNC_NAME: BaseGameObject::constructor
void __fastcall BaseGameObject::constructor(unsigned int* this)
{
    ListNode* node;
    ListNode* current;
    ListNode* next;

    // Set vtable pointers for multiple inheritance (base class and possibly interfaces)
    this[0] = (unsigned int)&BaseGameObject_vtable;
    this[0xF] = (unsigned int)&BaseGameObject_vtable2; // +0x3C
    this[0x12] = (unsigned int)&BaseGameObject_vtable3; // +0x48

    // Initialize subobjects at offsets 0x50 and 0x58
    initSubObject(this + 0x14); // offset 0x50
    linkSubObject(this + 0x14); // offset 0x50 - add to some list?
    initSubObject(this + 0x16); // offset 0x58
    linkSubObject(this + 0x16); // offset 0x58

    // If the object is already linked in a global list (offset 0x70), remove it
    node = (ListNode*)this[0x1C]; // +0x70
    if (node != 0)
    {
        // Node's next pointer (offset 4 from node)
        next = *(ListNode**)((unsigned int)node + 4);
        if (next == (ListNode*)(this + 0x1C)) // if next points back to the head
        {
            // Single node in list: set next to the previous pointer (offset 0x74)
            *(ListNode**)((unsigned int)node + 4) = (ListNode*)this[0x1D];
            operatorDelete(node);
            return;
        }
        // Walk the list to find the node whose next points to the head
        current = (ListNode*)((unsigned int)node + 4); // start at node->next
        while (current != (ListNode*)(this + 0x1C))
        {
            node = current;
            current = *(ListNode**)((unsigned int)current + 4);
        }
        // Update the found node's next to skip the node being removed
        *(ListNode**)((unsigned int)node + 4) = (ListNode*)this[0x1D];
    }
    operatorDelete(node);
    return;
}