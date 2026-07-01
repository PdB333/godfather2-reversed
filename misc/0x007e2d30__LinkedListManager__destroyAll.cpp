// FUNC_NAME: LinkedListManager::destroyAll

// Forward declaration for external release function (likely frees resources)
extern void __fastcall releaseNode(ListNode* node);

// Linked list node structure (partial, offsets inferred)
struct ListNode {
    int flags;          // +0x00 (checked for non-zero before release)
    int field_0x04;     // unknown
    int field_0x08;     // unknown
    ListNode* next;     // +0x0C (pVar2[3])
};

// Vtable for LinkedListManager (partial, offsets from param_1[4])
struct LinkedListManagerVtable {
    void (__thiscall *unknown0)(void* self);          // +0x00
    void (__thiscall *deleteNode)(ListNode* node, int zero); // +0x04
    void (__thiscall *unknown2)(void* self);          // +0x08
    void (__thiscall *shutdown)(void* self);          // +0x0C
};

// Manager class managing a linked list of nodes
struct LinkedListManager {
    ListNode* head;                     // +0x00 (first element in param_1)
    int field_0x04;                     // +0x04
    int field_0x08;                     // +0x08
    ListNode* spareNode;                // +0x0C (param_1[3])
    LinkedListManagerVtable* vtable;    // +0x10 (param_1[4])

    // Iterates through all nodes, releases flagged ones, deletes them,
    // then handles the spare node and calls shutdown.
    void __thiscall destroyAll() {
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* next = current->next; // save next before deletion
            if (current->flags != 0) {
                releaseNode(current);       // external release (e.g., free resources)
            }
            vtable->deleteNode(current, 0); // virtual deallocation of node
            current = next;
        }

        if (spareNode != nullptr) {
            vtable->deleteNode(spareNode, 0);
        }

        vtable->shutdown(this);             // virtual cleanup of the manager
    }
};