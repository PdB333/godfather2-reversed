// FUNC_NAME: DestructibleBase::~DestructibleBase

// Reconstructs the destructor at 0x007fff40 for a base class that manages an intrusive linked list node at offset +0x48.
// The function copies a resource pointer from param_2, finalizes it via FUN_00408a00, and then detaches the node from the list via FUN_004daf90.

void __thiscall DestructibleBase::~DestructibleBase(void* this, int* pData)
{
    // Debug guard: stores a stack trace marker (auto-function pointer)
    void** __debugTrace = &PTR_FUN_00e31e2c; // static auto function pointer, unused

    // +0x48: pointer to the intrusive list node (ListNode) within this object
    ListNode* node = (this != 0) ? reinterpret_cast<ListNode*>(reinterpret_cast<char*>(this) + 0x48) : 0;

    int savedNext = 0; // stores old value at node->field_4 (likely m_pNext)
    if (node != 0)
    {
        // Save the next pointer (or some integral field at offset +4)
        savedNext = node->field_4; // +4 from node: might be m_pNext or m_pData
        // Overwrite it with the address of the local node pointer (debug / break awareness)
        node->field_4 = reinterpret_cast<int>(&node);
    }

    // Copy the resource ID / pointer from pData and finalize it
    int dataCopy = *pData; // assume pData points to a simple int or resource handle
    char flag = 0; // not used, but needed for the call signature
    FUN_00408a00(&dataCopy, 0); // likely destructor / release for the copy

    // If the node existed, unlink it from its list
    if (node != 0)
    {
        FUN_004daf90(&node); // removes node from intrusive list (passes pointer-to-pointer)
    }

    // __debugTrace goes out of scope (stack variable)
}