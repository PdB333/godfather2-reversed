// FUNC_NAME: findAvailableObject (likely a manager method selecting an entity from a linked list that is not in use and within threshold)
bool findAvailableObject(float distanceThreshold) {
    int* headPtr = *(int**)0x011a0ef4; // global head of linked list
    if (headPtr == nullptr) return false;

    int* curNode = headPtr;
    while (true) {
        // Check conditions to skip the node:
        // offset 0x68: state == 1? (active)
        if (curNode[0x1a] == 1) {
            // skip
        }
        // offset 0x08: pointer, then byte at +8 masked with 0x10 (flag bit 4)
        else if ((*(uint8_t*)(curNode[2] + 8) & 0x10) != 0) {
            // skip
        }
        // offset 0x50: float value < input distance
        else if (distanceThreshold < *(float*)(curNode + 0x14)) {
            // skip
        }
        else {
            // Found a node that passes all conditions
            processNode(curNode, 0x5f1ef0); // FUN_005f1ef0
            return true;
        }

        curNode = (int*)*curNode; // next node (offset 0x00)
        if (curNode == nullptr) {
            return false;
        }
    }
}

// Note: The actual call is to FUN_005f1ef0, which likely performs some action on the node.
// Input float in XMM0 is passed as distanceThreshold; the node has fields:
// +0x00: next pointer
// +0x08: pointer to a sub-structure (e.g., behavior data)
// +0x50: float (e.g., activation distance)
// +0x68: integer state (1 = occupied?)