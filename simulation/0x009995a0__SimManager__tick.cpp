// FUNC_NAME: SimManager::tick

#include <cstdint>

// Likely a node in a linked list; offset +0x4 is next pointer
struct ListNode {
    ListNode* m_prev;   // offset +0x0 (maybe)
    ListNode* m_next;   // offset +0x4
    // ... additional data
};

// Global linked list heads (from DAT_01130958 and DAT_01130974)
static ListNode* s_listHead1 = reinterpret_cast<ListNode*>(0x01130958);
static ListNode* s_listHead2 = reinterpret_cast<ListNode*>(0x01130974);

// Forward declarations for the two object processing functions
void processFirstListNode(ListNode* node);   // corresponds to FUN_00999470
void processSecondListNode(ListNode* node);  // corresponds to FUN_009964c0

void SimManager::tick() {
    ListNode* node1 = s_listHead1;
    ListNode* node2 = s_listHead2;

    // Process the first linked list (do‑while loop)
    if (node1 != nullptr) {
        do {
            processFirstListNode(node1);          // FUN_00999470
            node1 = node1->m_next;                // next from offset +0x4
            node2 = s_listHead2;                  // reset node2 to head each iteration
        } while (node1 != nullptr);
    }

    // Process the second linked list (for loop)
    for (; node2 != nullptr; node2 = node2->m_next) {
        processSecondListNode(node2);             // FUN_009964c0
    }
}