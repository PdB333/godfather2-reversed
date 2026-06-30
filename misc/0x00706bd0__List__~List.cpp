// FUNC_NAME: List::~List

class List {
public:
    struct ListNode {
        void* pData;   // +0x00: Data pointer
        ListNode* pNext; // +0x04: Next node pointer
    };

    void* m_pVtable;   // +0x00: vtable pointer
    ListNode* m_pHead; // +0x04: Head of linked list
    void* m_pExtra;    // +0x08: Extra object (e.g., a sentinel or auxiliary data)

    // Destructor: clears list and frees extra object
    __thiscall ~List();
};

// External memory free function (FUN_004daf90)
extern void FreeMemory(void* ptr);

// Base vtable pointer (PTR_FUN_00e32808)
extern void* g_BaseVtable;

void __thiscall List::~List() {
    // Free extra object if present
    if (this->m_pExtra != nullptr) {
        FreeMemory(this->m_pExtra);
    }

    // Restore vtable to base class (destructor chaining)
    this->m_pVtable = g_BaseVtable;

    // Walk the linked list and clear all nodes
    ListNode* pCurrent = this->m_pHead;
    while (pCurrent != nullptr) {
        ListNode* pNext = pCurrent->pNext; // Save next before clearing
        pCurrent->pNext = nullptr;
        pCurrent->pData = nullptr;
        pCurrent = pNext;
    }
}