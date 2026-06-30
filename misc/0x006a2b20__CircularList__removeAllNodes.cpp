// FUNC_NAME: CircularList::removeAllNodes
void __fastcall CircularList::removeAllNodes(CLink* listHead)
{
    CLink* current = listHead->pNext;   // Start with the first node after the sentinel head
    while (current != listHead)           // Continue until we loop back to the sentinel
    {
        CLink* nextNode = current->pNext; // Save next node before destruction
        destroyNode(current);             // Free/release the current node (calls FUN_009c8f10)
        current = nextNode;               // Move to the next node
    }
}