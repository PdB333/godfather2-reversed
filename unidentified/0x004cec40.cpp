// FUN_NAME: ListManager::insertAfterHead
void __thiscall ListManager::insertAfterHead(void* this)
{
    // this + 0x18 points to the list head sentinel node
    ListNode* head = *(ListNode**)((char*)this + 0x18);
    
    // Allocate a new node, passing the head and its 'next' pointer as context
    // in_EAX is likely an implicit parameter (e.g., from a previous call)
    ListNode* newNode = (ListNode*)FUN_004cf1f0(head, *(int*)((char*)head + 4), __eax);
    
    // Perform any post-allocation updates (e.g., increment count)
    FUN_004cf240();
    
    // Insert newNode after the head sentinel:
    // Set head->next to newNode
    *(int*)((char*)head + 4) = (int)newNode;
    // Set the next pointer of the old first node (or the sentinel's next) to point back to newNode
    // This effectively updates the previous node's 'next' pointer stored at newNode+4
    **(int**)((char*)newNode + 4) = (int)newNode;
}