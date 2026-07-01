// FUNC_NAME: LinkedList::deleteAll
void LinkedList::deleteAll(LinkedListNode* node)
{
    char flag;
    
    flag = *(char*)((int)node + 0x15); // +0x15: deletion flag / marker
    while (flag == '\0') {
        // Recursively delete the next node (param_1[2] = next pointer)
        LinkedList::deleteAll(*(LinkedListNode**)((int)node + 8)); // +0x08: next pointer
        
        // Get the previous node before freeing current
        LinkedListNode* prevNode = (LinkedListNode*)*(int*)node; // +0x00: prev pointer
        
        // Free the current node's data / destroy node
        FUN_009c8eb0(node); // likely operator delete or node destructor
        
        // Move to previous node in list
        node = prevNode;
        flag = *(char*)((int)prevNode + 0x15);
    }
    return;
}