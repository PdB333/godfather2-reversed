// FUNC_NAME: ManagerBase::findNodeBySubType
// Address: 0x0071d050
// Search an intrusive linked list for a node whose type ID (stored as encoded value +0x48) matches targetSubType.
// On match, extract associated data via helper FUN_0071cfc0 and write it to outData.
// Returns outData pointer (null if not found, else the same pointer).

int* __thiscall ManagerBase::findNodeBySubType(int* this, int* outData, int targetSubType) {
    int* currentNode = reinterpret_cast<int*>(*this); // +0x00: head of linked list
    *outData = 0;

    if (currentNode == nullptr) {
        return outData;
    }

    while (true) {
        // Node layout: +0x00: data pointer?, +0x04: next pointer, +0x08: encoded type ID
        int encodedType = *(int*)(*currentNode + 8);
        int nodeType;
        if (encodedType == 0) {
            nodeType = 0;
        } else {
            nodeType = encodedType - 0x48; // decode: stored as actualType + 0x48
        }

        if (nodeType == targetSubType) {
            break;
        }

        currentNode = reinterpret_cast<int*>(currentNode[1]); // +0x04: next node
        if (currentNode == nullptr) {
            return outData;
        }
    }

    // Found matching node
    int* foundNode = currentNode; // param_1 after loop
    int* result = reinterpret_cast<int*>(FUN_0071cfc0(&foundNode)); // helper extracts value from node
    *outData = *result;
    return outData;
}