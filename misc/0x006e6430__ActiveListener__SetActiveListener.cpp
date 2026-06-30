// FUNC_NAME: ActiveListener::SetActiveListener
void __thiscall ActiveListener::SetActiveListener(bool enable, void* listener)
{
    // Offset 0x8a: bit 0 controls whether the listener list is active
    byte* flag = reinterpret_cast<byte*>(this + 0x8a);
    // Offset 0x60: pointer to the head of the listener node list (only one node allowed?)
    void** head = reinterpret_cast<void**>(this + 0x60);

    if (!enable)
    {
        // Clear the active flag (bit 0)
        *flag &= 0xFE;

        // If there is a current listener, remove it and set head to null
        if (*head != nullptr)
        {
            RemoveNode(head);  // 0x004daf90: removes node pointed to by *head, updates head if needed, possibly frees memory
            *head = nullptr;
        }
    }
    else
    {
        // Set the active flag
        *flag |= 1;

        // Convert listener pointer to node pointer: the node is embedded at offset 0x48 from the listener object
        void* node = listener;
        if (listener != nullptr)
        {
            node = reinterpret_cast<char*>(listener) + 0x48;
        }

        // Only update if the new node differs from the current head
        if (*head != node)
        {
            // Remove old node if present
            if (*head != nullptr)
            {
                RemoveNode(head);  // 0x004daf90: removes node, updates head
            }

            // Set head to the new node
            *head = node;

            if (node != nullptr)
            {
                // ListenerNode structure at offset 0x48 within listener has a 'back pointer' at offset +4
                // The back pointer stores the address of the pointer that points to this node (i.e., &head)
                // Save the old back pointer into this+0x64 (possibly for later restoration or debugging)
                *reinterpret_cast<void**>(this + 0x64) = *reinterpret_cast<void**>(reinterpret_cast<char*>(node) + 4);
                // Update the node's back pointer to point to the head pointer (so it can be updated on removal)
                *reinterpret_cast<void***>(reinterpret_cast<char*>(node) + 4) = head;
            }
        }
    }
}