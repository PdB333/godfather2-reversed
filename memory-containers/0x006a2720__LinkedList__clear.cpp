// FUNC_NAME: LinkedList::clear
void __fastcall LinkedList::clear(LinkedList* this)
{
    // Sentinel node; first member (+0x00) is next pointer
    Node* node = *this; // this->next
    while (node != this)
    {
        Node* nextNode = *node; // node->next
        // Custom deallocation function (likely pool-based free)
        FUN_009c8f10(node);
        node = nextNode;
    }
    // Note: sentinel's next/prev are not reset here;
    // caller is responsible for re-initializing the list.
}