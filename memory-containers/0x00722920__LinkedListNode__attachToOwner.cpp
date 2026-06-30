// FUNC_NAME: LinkedListNode::attachToOwner
int* __thiscall LinkedListNode::attachToOwner(int* thisNode, int* ownerObject)
{
    int* listHead = 0;
    
    if (ownerObject == 0) {
        listHead = 0;
    } else {
        listHead = (int*)((char*)ownerObject + 0x3c); // +0x3c: offset to list head pointer
    }
    
    if (thisNode[0] != (int)listHead) { // current list head pointer stored at this+0
        if (thisNode[0] != 0) {
            // Remove this node from its current list
            LinkedListNode::removeFromList(thisNode); // FUN_004daf90
        }
        thisNode[0] = (int)listHead; // store new list head pointer
        if (listHead != 0) {
            // Insert this node at the front of the list
            thisNode[1] = listHead[1]; // this->next = head->next (listHead+4)
            listHead[1] = (int)thisNode; // head->next = this
        }
    }
    return thisNode;
}