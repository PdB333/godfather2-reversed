// FUNC_NAME: ObjectListManager::removeObjectByIndex
void __thiscall ObjectListManager::removeObjectByIndex(int thisPtr, int objectPtr)
{
    int iVar1 = objectPtr;
    int iVar2;
    int local_4 = thisPtr;
    
    // Compute owner base from the first element's member pointer (+0x3C)
    if (*(int *)(thisPtr + 0x3C) == 0) {
        iVar2 = 0;
    } else {
        iVar2 = *(int *)(thisPtr + 0x3C) - 0x48; // subtract offset to get owning object
    }
    
    // If objectPtr matches the first element's owner, handle specially
    if (objectPtr == iVar2) {
        FUN_006faa40(); // handleFirstElementRemoval
    }
    
    // Get head of the intrusive list node chain (+0x6D4)
    auto currentNode = *(int *)(thisPtr + 0x6D4);
    if (currentNode != 0) {
        while (true) {
            // Node structure: +0x10 = pointer to a member inside the owning object, +0x18 = next node
            int nodeMemberPtr = *(int *)(currentNode + 0x10);
            if (nodeMemberPtr == 0) {
                iVar2 = 0;
            } else {
                iVar2 = nodeMemberPtr - 0x48; // container_of: get owner base
            }
            
            if (iVar1 == iVar2) {
                // Found the node belonging to the object
                FUN_006f9a10(&local_4, &currentNode); // remove this node and possibly execute callback
                return;
            }
            
            // Move to next node
            if (currentNode == 0) {
                currentNode = 0;
            } else {
                currentNode = *(int *)(currentNode + 0x18);
            }
            
            if (currentNode == 0) {
                return; // end of list, object not found
            }
        }
    }
    
    return;
}