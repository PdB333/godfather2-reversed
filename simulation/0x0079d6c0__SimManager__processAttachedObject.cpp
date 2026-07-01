// FUNC_NAME: SimManager::processAttachedObject
void __thiscall SimManager::processAttachedObject(int thisPtr, int object)
{
    int *pNode = (int *)(thisPtr + 0x24b4);  // +0x24b4: m_pObjectNode (pointer to embedded node in object)
    int newNode;
    
    if (object == 0) {
        newNode = 0;
    } else {
        newNode = object + 0x48;   // node is at offset 0x48 in the object
    }
    
    if (*pNode != newNode) {
        if (*pNode != 0) {
            FUN_004daf90(pNode);    // likely release previous node from list
        }
        *pNode = newNode;
        if (newNode != 0) {
            *(int *)(thisPtr + 0x24b8) = *(int *)(newNode + 4);  // +0x24b8: m_pPrevNodePtr (backlink from node)
            *(int **)(newNode + 4) = pNode;  // set node's prev pointer to our m_pObjectNode address
        }
    }
    
    if (*pNode != 0) {
        int baseObj = *pNode - 0x48;  // recover object pointer from node
        // check flag at object+0x1d4 (bit 0)
        if ((*(byte *)(baseObj + 0x1d4) & 1) != 0) {
            FUN_00703f70(pNode);    // likely remove object from active list
            char cVar = FUN_00481620();  // maybe global input/state check
            if (cVar != '\0') {
                int otherNode;
                if (*(int *)(thisPtr + 0x24bc) == 0) {
                    otherNode = 0;
                } else {
                    otherNode = *(int *)(thisPtr + 0x24bc) - 0x48;  // recover other object
                }
                FUN_0093b6a0(otherNode, 0);  // clear flag on other object (or deactivate)
            }
        }
    }
    
    // check object flag at 0x1a8
    if (*(char *)(object + 0x1a8) == '\x01') {
        FUN_007014d0(0);   // play sound effect (e.g., on completion)
    }
    
    FUN_00800780(object);  // call object's update routine (virtual)
}