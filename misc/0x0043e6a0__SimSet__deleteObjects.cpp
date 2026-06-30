// FUNC_NAME: SimSet::deleteObjects

void SimSet::deleteObjects()
{
    Node* sentinel = m_listHead;
    Node* node = sentinel->next;

    // Iterate through the linked list of managed objects
    while (node != sentinel)
    {
        // Get the interface pointer from the object (at +0x8)
        ObjectInterface* objIface = node->object->interface;

        // Notify pre-delete callback if present
        if (m_preDeleteCallback)
        {
            (objIface->vtable[2])(m_preDeleteCallback); // Offset 8 in vtable (2nd function)
        }
        // Notify post-delete callback if present
        if (m_postDeleteCallback)
        {
            (objIface->vtable[2])(m_postDeleteCallback);
        }

        node = node->next;
    }

    // Detach all nodes from the sentinel (make list empty)
    node = sentinel->next;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    m_count = 0;

    // Deallocate each node using the allocator interface
    while (node != sentinel)
    {
        Node* nextNode = node->next;
        m_allocator->deallocate(node, sizeof(Node));
        node = nextNode;
    }

    // Additional cleanup (FUN_006278d0)
    SharedCleanupFunction();

    // Clear post-delete callback
    m_postDeleteCallback = nullptr;
}