// FUNC_NAME: ManagerClass::findFirstActiveNode

struct ListNode {
    char unknown0[0x08];   // +0x00: padding or vtable pointer
    ListNode* next;        // +0x08: next node in singly linked list
    char unknownC[0x0D];   // +0x0C to +0x14: padding/other fields
    char flag;             // +0x15: non-zero indicates active/valid node
};

class ManagerClass {
    // this +0x8 is a pointer to the head of the linked list
    ListNode* head; // offset +0x08

public:
    // Traverse linked list starting from head, return first node with flag != 0
    ListNode* __thiscall findFirstActiveNode() {
        ListNode* pNode = this->head;
        while (pNode->flag == '\0') {
            pNode = pNode->next;
        }
        return pNode;
    }
};