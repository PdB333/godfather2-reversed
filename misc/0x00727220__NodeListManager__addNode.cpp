// FUNC_NAME: NodeListManager::addNode
void __thiscall NodeListManager::addNode(void* pObject)
{
    // m_count at +0x14? No, at +0xb4: number of nodes added so far (used as slot index)
    // m_flags at +0x114: initialization flag (bit 5)
    
    // Initialization on first call (when m_count is 0 and not yet initialized)
    if (m_count == 0 && !(m_flags & 0x20))
    {
        m_flags |= 0x20;
        // Setup the node slot array at +0xc4 with size/capacity from +0xa0 and +0xa4,
        // and possibly an allocator at +0x50.
        initializeNodeArray(/* offset 0xa0 */ m_arrayBegin, /* offset 0xa4 */ m_arrayCapacity, /* offset 0x50 */ m_allocator);
    }

    // Get a pointer to the current slot (8 bytes each, index = m_count)
    // Each slot is a small structure (e.g., head pointer + tail pointer)
    NodeSlot* slot = reinterpret_cast<NodeSlot*>(reinterpret_cast<char*>(this) + 0xc4 + m_count * sizeof(NodeSlot));

    // The actual list node is embedded in pObject at offset 0x48
    ListNode* node = (pObject != nullptr) 
                     ? reinterpret_cast<ListNode*>(reinterpret_cast<char*>(pObject) + 0x48) 
                     : nullptr;

    // If the slot's head is not already pointing to this node, update the list
    if (slot->head != node)
    {
        if (slot->head != nullptr)
        {
            // Remove previous node from the list (unlink/destroy)
            unlinkNodeFromSlot(slot);
        }
        slot->head = node;

        if (node != nullptr)
        {
            // Intrusive linked list insertion: 
            //   Save the current next pointer of the node into slot->tail
            //   Then set the node's next pointer to point to the slot (circular? or backlink)
            slot->tail = node->next;
            node->next = reinterpret_cast<ListNode*>(slot);
        }
    }

    // Increment the node counter for the next slot
    m_count++;
}