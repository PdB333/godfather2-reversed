// FUNC_NAME: ListManager::~ListManager
void __fastcall ListManager::~ListManager(void* this)
{
    Node** ppHead; // pointer to head of linked list (offset +0x40)
    Node* pNode;   // current node in list
    Node* pNext;   // next node

    // Set vtable to base class vtable (offset +0x3C)
    // (common destructor pattern: avoid calls to derived virtual functions)
    *(void***)((char*)this + 0x3C) = &PTR_FUN_00e32808; // BaseVTable

    // Get pointer to head of list (stored right after vtable at +0x40)
    ppHead = (Node**)((char*)this + 0x40);
    pNode = *ppHead;

    // Unlink all nodes in the singly linked list
    // Node layout: +0x00 vtable, +0x04 next pointer
    while (pNode != nullptr)
    {
        pNext = pNode->next; // save next node
        // Clear node's vtable and next pointer to detach from chain
        pNode->vtable = nullptr;
        pNode->next = nullptr;
        pNode = pNext;
    }

    // Call base class cleanup (likely base destructor or memory manager)
    BaseClass::OnDestroy(); // FUN_0043b400()
}