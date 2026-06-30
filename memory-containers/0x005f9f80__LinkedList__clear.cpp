// FUNC_NAME: LinkedList::clear
void __thiscall LinkedList::clear()
{
    // 'this' in ESI
    // Structure: sentinel node at offset +0x18 (unaff_ESI[6])
    // sentinel node: next at +0x00, prev at +0x04
    // Count at offset +0x1C (unaff_ESI[7])
    // Nodes have vtable at +0x00, destructor at vtable[1]

    Node* sentinel = reinterpret_cast<Node*>(this->sentinelOffset); // offset +0x18
    Node* node = sentinel->next; // piVar2 = *piVar1

    // Reset sentinel to empty list (circular self-pointing)
    sentinel->next = sentinel;         // *piVar1 = (int)piVar1
    sentinel->prev = sentinel;         // *(sentinel + 4) = sentinel
    this->count = 0;                   // unaff_ESI[7] = 0

    // Iterate and destroy all nodes
    while (node != sentinel)
    {
        Node* nextNode = node->next; // piVar1 = *piVar2
        // Call the node's destructor via vtable[1] with flag 0xc
        vtable_destroy(node, 0xc); // (**(code**)(*(int*)node + 4))(node, 0xc)
        node = nextNode;
    }
}