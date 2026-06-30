// FUNC_NAME: EARS::Utils::ListNode::insertAfter
// Function at 0x007393b0
// Role: Inserts this node after the embedded list node at offset 0x48 in the given container.
//       If container is null, the node is detached from its current list.

class ListNode {
public:
    ListNode* prev; // +0x00
    ListNode* next; // +0x04

    // Insert this node after the node at offset 0x48 in 'container'.
    // If container is null, remove this node from its list.
    __thiscall ListNode* insertAfter(void* container) {
        ListNode* target = nullptr;
        if (container != nullptr) {
            target = reinterpret_cast<ListNode*>(static_cast<char*>(container) + 0x48);
        }
        if (this->prev != target) {
            if (this->prev != nullptr) {
                // Remove from current list (calls FUN_004daf90)
                this->removeFromList();
            }
            this->prev = target;
            if (target != nullptr) {
                this->next = target->next;
                target->next = this;
            }
        }
        return this;
    }

private:
    // Removes this node from its current list (calls external function at 0x004daf90)
    void removeFromList(); // defined elsewhere
};