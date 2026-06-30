// FUNC_NAME: MemoryPool::removeItem

// Reconstructed from address 0x00587680
// Removes a node identified by key from the linked list and adjusts total size.
// Uses EA EARS engine custom memory pool with size tracking.

// Node structure for the memory pool linked list
struct MemoryPoolNode {
    int m_key;          // +0x00: Identifier key for the node
    int m_size;         // +0x04: Size of the allocation (bytes)
    // +0x08: padding or unknown field
    MemoryPoolNode* m_next; // +0x0C: Next node in the linked list
};

// Memory pool container (polymorphic, has vtable)
class MemoryPool {
public:
    // +0x00: vtable pointer (base, virtual functions)
    int m_totalSize;    // +0x0C: Total tracked size (sum of all nodes' m_size)
    bool m_dirty;       // +0x10: Dirty flag (set to 1 after removal)
    MemoryPoolNode* m_head; // +0x14: Head of the node linked list

    // Virtual function at vtable offset +0x04: destroyItem(MemoryPoolNode* node, int param)
    // This method handles deallocation or cleanup of a node.
    // Called after unlinking the node from the list.
    void destroyItem(MemoryPoolNode* node, int param);

    // Removes a node with the given key from the pool.
    // If found, unlinks it, updates total size, marks pool dirty, and destroys the node.
    void __thiscall removeItem(int key);
};

void __thiscall MemoryPool::removeItem(int key) {
    MemoryPoolNode* current = this->m_head;  // Start at head
    MemoryPoolNode* previous = nullptr;      // Track previous node for unlinking

    // Traverse the list until we find a matching key or reach the end
    while (current != nullptr) {
        // Check if this node's key matches the target
        if (current->m_key == key) {
            // Update total size by subtracting this node's size
            this->m_totalSize -= current->m_size;

            // Unlink the node from the list
            if (previous != nullptr) {
                // Node is not the head: point previous's next to current's next
                previous->m_next = current->m_next;
            } else {
                // Node is the head: update head pointer
                this->m_head = current->m_next;
            }

            // Call the virtual destroy method on the removed node
            this->destroyItem(current, 0);

            // Mark the pool as dirty (needs compaction or update)
            this->m_dirty = true;
            return; // Node removed, exit
        }

        // Move to next node
        previous = current;
        current = current->m_next;
    }
    // If we exit the loop, the key was not found; do nothing
}