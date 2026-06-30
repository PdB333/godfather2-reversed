// FUNC_NAME: ObjectManagerNode::~ObjectManagerNode

struct DependentNode {
    void* field1;   // +0x00
    void* field2;   // +0x04
    DependentNode* next; // +0x08
};

struct ObjectManagerNode {
    void** vtable;             // +0x00
    DependentNode* dependList; // +0x04
    // padding?                // +0x08
    ObjectManagerNode* list1Prev; // +0x0C
    ObjectManagerNode* list1Next; // +0x10
    uint32_t inList1Flag;      // +0x14 (0 or non-zero)
    // padding?                // +0x18
    ObjectManagerNode* childHead; // +0x1C
    ObjectManagerNode* list2Head; // +0x20 (head of second list, could be parent's child list head)
    ObjectManagerNode* list2Prev; // +0x24
    ObjectManagerNode* list2Next; // +0x28
};

// Global variable used as head of first list
extern ObjectManagerNode* g_pGlobalListHead;

void ObjectManagerNode::destroy()
{
    // 1. Destroy all child nodes recursively
    while (childHead != nullptr) {
        childHead->destroy();
        // After child destruction, childHead is updated (child unlinked itself from this list)
    }

    // 2. Remove from first list (global object list)
    if (inList1Flag) {
        if (list1Prev == nullptr) {
            g_pGlobalListHead = list1Next;
        } else {
            list1Prev->list1Next = list1Next;
        }
        if (list1Next != nullptr) {
            list1Next->list1Prev = list1Prev;
        }
    }

    // 3. Remove from second list (e.g., per-parent children list)
    if (list2Head != nullptr) {
        if (list2Prev == nullptr) {
            // Update head's next pointer (offset +0x04 from head = head->list1Next? but here it's the next of head, which is stored at +0x10 in head)
            // Actually from the decompiled code: *(param_1[8] + 4) = param_1[10];
            // So the head (list2Head) has a next pointer at offset +0x04 (list2Head->list1Next? but that would be at +0x10 normally; inconsistent but we follow the code)
            // We use a separate field for head's next, but we'll just use reinterpret_cast to match the binary offsets.
            *(ObjectManagerNode**)((char*)list2Head + 4) = list2Next;
        } else {
            // Update previous node's next pointer (offset +0x08 from prev)
            *(ObjectManagerNode**)((char*)list2Prev + 8) = list2Next;
        }
        if (list2Next != nullptr) {
            // Update next node's previous pointer (offset +0x04 from next)
            *(ObjectManagerNode**)((char*)list2Next + 4) = list2Prev;
        }
    }

    // 4. Change vtable to base class vtable (destroyed state)
    vtable = &g_pBaseVTable; // PTR_LAB_00e42de4

    // 5. Clear dependent list
    DependentNode* pNode = dependList;
    while (pNode != nullptr) {
        DependentNode* pNext = pNode->next; // next at +0x08
        pNode->field1 = nullptr;
        pNode->field2 = nullptr;
        pNode->next = nullptr;
        pNode = pNext;
    }
}