// FUNC_NAME: DoublyLinkedList::pushBack
void __fastcall DoublyLinkedList::pushBack(Node *node, DoublyLinkedList *list)
{
    node->prev = NULL;          // Node::prev at +0x00
    node->next = list->tail;    // Node::next at +0x04, List::tail at +0x04
    if (list->tail != NULL)
    {
        list->tail->prev = node; // List::tail->prev at +0x00
    }
    else
    {
        list->head = node;       // List::head at +0x00
    }
    list->tail = node;
}