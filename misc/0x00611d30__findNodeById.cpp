// FUNC_NAME: findNodeByID
// Function address: 0x00611d30 - looks up a node by a key in a global singly linked list.
// Each node at offset +0: unused, +4: next pointer, +8: 4-byte key (ID)

struct ListNode {
    int  field_0;      // +0x00 - unknown/possibly padding
    ListNode* next;    // +0x04
    int  id;           // +0x08 - key value to compare against
};

static ListNode* g_pObjectListHead = (ListNode*)0x012058ec;   // global linked list head

int __cdecl findNodeByID(int targetID)
{
    ListNode* currentNode = g_pObjectListHead;
    while (currentNode != nullptr)
    {
        if (targetID == currentNode->id)
        {
            return (int)currentNode;
        }
        currentNode = currentNode->next;
    }
    return 0;
}