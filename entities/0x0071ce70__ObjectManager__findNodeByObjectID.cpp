// FUNC_NAME: ObjectManager::findNodeByObjectID
// Address: 0x0071ce70
// Searches a singly linked list of nodes (stored in this->head) for a node whose associated object
// (at node+0x8) has an ID field at offset 0x48 matching targetID.
// Returns the node address as an integer if found, else 0.

int __thiscall ObjectManager::findNodeByObjectID(int targetID)
{
    // this points to a structure whose first member is a pointer to the head of the node list
    ListNode* node = this->head;  // dereference this to get head pointer
    int nodeAddr = 0;

    if (node != nullptr)
    {
        while (true)
        {
            nodeAddr = (int)node;                     // current node address (return value)
            Object* obj = node->object;               // object pointer at node+0x8
            int id;
            if (obj == nullptr)
            {
                id = 0;
            }
            else
            {
                id = *(int*)((char*)obj + 0x48);      // object ID at offset 0x48
            }

            if (id == targetID) break;                // found matching ID

            node = node->next;                        // advance to next node (node+0x4)
            if (node == nullptr)
            {
                return 0;                             // not found
            }
        }
    }
    return nodeAddr;
}