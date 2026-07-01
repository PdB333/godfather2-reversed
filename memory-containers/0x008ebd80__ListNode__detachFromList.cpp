// FUNC_NAME: ListNode::detachFromList
void __fastcall ListNode::detachFromList(ListNode* this)
{
    // Call a helper to update the list's head/tail pointers (likely unlink this->next from the list)
    FUN_008eb390(this->next->next); // this->next->next is the node after the one being detached

    // Reinitialize the node (this->next) as a standalone circular node
    this->next->next = this->next;   // next points to self
    this->list = 0;                  // clear list pointer (offset +8)
    this->next->prev = this->next;   // prev points to self
    this->next->list = this->next;   // list pointer points to self
}