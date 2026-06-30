// FUNC_NAME: PacketOrderedQueue::insertOrderedPacket

// Reconstructed C++ for function at 0x0060c500
// This function inserts a packet (or node) into a globally ordered linked list,
// sorted by a key field at offset +0x20 (likely a sequence number or timestamp).
// The list is protected by a global critical section.

class PacketOrderedQueue;
class PacketOrderedNode;

// Globals used by the function
extern void* (*g_allocator)(size_t size, int* params); // DAT_01205868 - custom allocator
extern CRITICAL_SECTION g_listCriticalSection;          // DAT_012224f8
extern PacketOrderedNode* g_listHead;                   // DAT_012224e0 - head of sorted list

// Helper functions (defined elsewhere)
void PacketOrderedQueue::cleanupNode();              // FUN_0060c430
void PacketOrderedQueue::insertBeforeNode(PacketOrderedNode* node, PacketOrderedNode* before); // FUN_0060d480
void PacketOrderedQueue::insertAtEnd(PacketOrderedNode* node);                                  // FUN_0060d370

class PacketOrderedNode {
public:
    // Assuming the node structure is at least 13 dwords (52 bytes) + potential padding
    unsigned int field_00[?];   // copied 13 dwords from source
    // +0x08 (byte): bool m_initialized;   // checked as byte at +0xA
    unsigned char m_initialized;        // offset +0x0A (10)
    // +0x20: unsigned int m_key;       // compared with other nodes
    unsigned int m_key;                 // offset +0x20 (32)
    // +0x2C (offset 0x2B? actually +0x2C): PacketOrderedNode* m_selfPointer; // self-reference or next/prev
    PacketOrderedNode* m_selfPointer;   // offset +0x2C (44)
    // ... other fields...
};

// The 'this' pointer is of type PacketOrderedQueue (or some class that owns the node)
void PacketOrderedQueue::insertOrderedPacket(PacketOrderedNode* this) {
    // this is actually the node being inserted (in_EAX)
    PacketOrderedNode* node = this;
    PacketOrderedNode* newCopy = nullptr;
    int allocParams[3]; // for the custom allocator

    // If the node's initialization flag is not set, cleanup and return
    if (!node->m_initialized) {
        cleanupNode(); // Probably frees the node or resets
        return;
    }

    // If the node's self pointer is null, allocate a copy and set up the node
    if (node->m_selfPointer == nullptr) {
        allocParams[0] = 2;
        allocParams[1] = 0x10;
        allocParams[2] = 0;
        newCopy = (PacketOrderedNode*)((*g_allocator)(0x40, allocParams));

        // Copy 13 dwords (52 bytes) from original node to new copy
        for (int i = 0; i < 13; i++) {
            *((unsigned int*)newCopy + i) = *((unsigned int*)node + i);
        }
        // Set the self pointer of the copy to point to itself
        newCopy->m_selfPointer = newCopy;  // +0x2C = pointer to self

        // Now use the new copy as the node to insert
        node = newCopy;
    }

    PacketOrderedNode* current = this; // The node to insert (may be copy)
    PacketOrderedNode* iter;

    EnterCriticalSection(&g_listCriticalSection);

    // Traverse the global sorted list
    iter = g_listHead;
    while (iter != nullptr) {
        // Compare keys: if the current node's key is less than the iter node's key,
        // insert before this iter node
        if (current->m_key < iter->m_key) {
            insertBeforeNode(current, iter);
            LeaveCriticalSection(&g_listCriticalSection);
            return;
        }
        iter = iter->m_next;  // Assuming linked list structure; actually iter is pointer to node with next pointer at offset +4? (piVar2[1])
        // In the decompiled code, piVar2 = (int*)piVar2[1]; so next pointer is at offset +4.
    }

    // If no larger key found, insert at the end of the list
    insertAtEnd(current);
    LeaveCriticalSection(&g_listCriticalSection);
    return;
}