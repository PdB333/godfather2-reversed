// FUNC_NAME: WorldObjectManager::activateMatchingObjects
int __thiscall WorldObjectManager::activateMatchingObjects(int this, int typeId, int* pInstanceId, FilterObject* pFilter, int maxCount)
{
    ushort flags;
    int count = 0;
    int arrayIndex;
    Node* listHead;
    Node* currentNode;
    Node* nextNode;
    int nodeIndex;
    int unkFlag;
    byte filterResult;
    int stackBuffer[2];

    // Get the base list from the current sub-index
    listHead = *(Node**)(*(int*)(this + 0x18) + *(short*)(this + 0x16) * 4);
    currentNode = *(Node**)listHead->list;  // listHead->list points to the head of the linked list
    nodeIndex = (int)listHead;

    // Iterate through linked list nodes, possibly crossing buckets
    while (true) {
        Node* bucket = *(Node**)(nodeIndex + 0x18);  // bucket pointer from the current node
        if ((nodeIndex == 0) || (nodeIndex != (int)listHead)) {
            // debug assertion
            FUN_00b97aea();
        }
        if (currentNode == bucket) break;  // Reached end of this bucket? (circular check)
        if ((maxCount >= 0) && (count > maxCount)) {
            return count;
        }
        if (nodeIndex == 0) {
            FUN_00b97aea();
        }
        if (currentNode == *(Node**)(nodeIndex + 0x18)) {  // null check via sentinel?
            FUN_00b97aea();
        }

        // Check if node matches the criteria
        if ((currentNode->typeId == typeId) &&
            ((pInstanceId == nullptr) || (*pInstanceId == currentNode->instanceId)) &&
            ((pFilter == nullptr) ||
             (filterResult = pFilter->vtbl->evaluate(currentNode->typeId, currentNode->instanceId, currentNode->actionObject, currentNode->extraData),
              filterResult != 0))) {

            // Save data for processing
            int instanceIdSaved = currentNode->instanceId;
            int extraDataSaved = currentNode->extraData;  // may not be used later directly
            count++;

            // Process if the type object exists and instance is valid and marked
            TypeObject* typeObj = currentNode->typeObject;
            if ((typeObj != nullptr) && (instanceIdSaved != 0) && ((typeObj->flags & 1) != 0)) {
                // Look up the instance in the global hash table (hash = instanceId & 0xFFF)
                InstanceEntry* entry = InstanceHashTable[instanceIdSaved & 0xFFF];
                while ((entry != nullptr) && (entry->instanceId != instanceIdSaved)) {
                    entry = entry->next;
                }
                if (entry != nullptr) {
                    ushort oldFlags = *(ushort*)((int)entry + 0x16);
                    *(ushort*)((int)entry + 0x16) = oldFlags | 1;  // set flag
                    typeObj->vtbl->activate(&instanceIdSaved);     // call virtual function
                    *(ushort*)((int)entry + 0x16) = (oldFlags & 1) | (*(ushort*)((int)entry + 0x16) & 0xFFFE);
                    if ((entry->callback != 0) && ((oldFlags & 1) == 0)) {
                        FUN_00408af0();  // some callback
                    }
                }
            }

            // Notify the action object attached to this node
            ActionObject* action = currentNode->actionObject;
            if ((action != nullptr) && ((currentNode->actionFlags & 1) == 0)) {
                action->vtbl->notify(1);
            }

            // Advance to next node using the node manager (handles bucket boundaries)
            int* nextPair = (int*)FUN_00440e30((int)listHead, &stackBuffer[0], nodeIndex, currentNode);
            nodeIndex = *nextPair;
            currentNode = (Node*)nextPair[1];
        }
        else {
            if (currentNode == *(Node**)(nodeIndex + 0x18)) {
                FUN_00b97aea();
            }
            currentNode = currentNode->next;  // move to next in linked list
        }
    }

    return count;
}