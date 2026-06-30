// FUNC_NAME: ObjectContainer::cleanupListAndSubObject

class ObjectContainer {
    // vtable pointer at offset 0
    // ListNode* m_pHead;            // +0x04, linked list head
    // SubObject* m_pChild;          // +0x08, pointer to a child object
public:
    void cleanupListAndSubObject() {
        // If m_pChild exists, destroy it (call its destructor/cleanup at FUN_004daf90)
        if (m_pChild != nullptr) {
            subObjectCleanup(m_pChild); // FUN_004daf90
        }

        // Set vtable to base class vtable (likely base destructor stub)
        this->vtable = &PTR_FUN_00e32808;

        // Clear linked list: iterate through nodes and nullify their data and next pointers
        ListNode* pNode = m_pHead;
        while (pNode != nullptr) {
            ListNode* pNext = pNode->next; // save next
            pNode->next = nullptr;
            pNode->data = nullptr;
            pNode = pNext;
        }
        // Note: nodes are not deallocated here; ownership or lifecycle is external
    }
};