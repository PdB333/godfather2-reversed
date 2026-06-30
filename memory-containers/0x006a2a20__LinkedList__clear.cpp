// FUNC_NAME: LinkedList::clear
void __fastcall LinkedList::clear(LinkedListNode* sentinel)
{
    LinkedListNode* currentNode = (LinkedListNode*)*sentinel;
    while (currentNode != sentinel) {
        LinkedListNode* nextNode = (LinkedListNode*)*currentNode;
        FUN_009c8f10(currentNode); // deleteNode(currentNode)
        currentNode = nextNode;
    }
}