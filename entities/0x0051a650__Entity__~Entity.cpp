// FUNC_NAME: Entity::~Entity
void __thiscall Entity::~Entity(void)
{
    // Field offsets (relative to this, in bytes):
    // +0x00: vtable pointer
    // +0x04: m_pChildList (linked list of child objects)
    // +0x08: m_pUnknown1
    // +0x0C: unknown
    // +0x10: unknown
    // +0x14: unknown
    // +0x18: m_pListHead2 (circular doubly linked list head)
    // +0x1C: m_pListTail2
    // +0x20: m_refCount
    // +0xC4: m_pListHead1 (circular doubly linked list head)
    // +0xC8: m_pListTail1

    // Step 1: Set vtable to first base destructor
    this->m_vtable = &PTR_FUN_00e3825c;   // vTable for first base class

    // Remove from first list (m_pListHead1 at +0xC4)
    int* pNode = this->m_pListHead1;
    if (pNode != nullptr)
    {
        int* pNext = *(int**)(pNode + 4);
        if (pNext == &this->m_pListHead1)
        {
            // Single node: adjust list head's previous pointer
            // Set node's next to the stored tail pointer
            *(int*)(pNode + 4) = this->m_pListTail1;
        }
        else
        {
            // Iterate to find the node whose next points back to the head?
            // Actually this is standard list node removal from a circular doubly linked list.
            int* pPrev = pNext;
            while (pPrev != &this->m_pListHead1)
            {
                pPrev = *(int**)(pPrev + 4); // follow next
                pNext = *(int**)(pPrev + 4); // next of previous
            }
            // pPrev is the node that points to the head, set its next to the tail
            *(int*)(pPrev + 4) = this->m_pListTail1;
        }
    }

    // Decrement reference count and possibly delete owned object
    if (this->m_refCount != 0)
    {
        int* refObj = (int*)(this->m_refCount + 4);
        *refObj = *refObj - 1;
        if (*(int*)(this->m_refCount + 4) == 0)
        {
            // Delete when reference count reaches zero
            (**(code**)(*(int*)this->m_refCount + 4))(); // call destructor on referenced object
        }
        this->m_refCount = 0;
    }

    // Remove from second list (m_pListHead2 at +0x18)
    int pNode2 = this->m_pListHead2;
    if (pNode2 != 0)
    {
        int* pNext2 = *(int**)(pNode2 + 4);
        if (pNext2 == &this->m_pListHead2)
        {
            // Single node: set node's next to tail
            *(int*)(pNode2 + 4) = this->m_pListTail2;
        }
        else
        {
            // Traverse to find node that points back to head
            int* pPrev2 = pNext2;
            while (pPrev2 != &this->m_pListHead2)
            {
                pPrev2 = *(int**)(pPrev2 + 4);
                pNext2 = *(int**)(pPrev2 + 4);
            }
            *(int*)(pPrev2 + 4) = this->m_pListTail2;
        }
    }

    // Set vtable to second base destructor
    this->m_vtable = &PTR_FUN_00e38258;   // vTable for second base class

    // Clear a pointer at offset +0x08? It sets *this->m_pUnknown1 = 0 and then sets field to 0
    if (this->m_pUnknown1 != (void*)0x0)
    {
        *(int*)this->m_pUnknown1 = 0;
        this->m_pUnknown1 = 0;
    }

    // Set vtable to final base (most derived) destructor
    this->m_vtable = &PTR_FUN_00e32808;   // vTable for this class

    // Walk the child list (m_pChildList at +0x04) and clear all nodes
    int* pChild = (int*)this->m_pChildList;
    while (pChild != (int*)0x0)
    {
        int* pNextChild = (int*)pChild[1];   // next pointer at offset +4 from node
        pChild[1] = 0;    // zero out next
        pChild[0] = 0;    // zero out data/pointer
        pChild = pNextChild;
    }

    return;
}