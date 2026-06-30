// FUNC_NAME: ObjectData::FlattenValueList
void ObjectData::FlattenValueList(void) {
    // Top-level linked list: nodes with sublist pointers at +0x0C
    int* pTopNode = nullptr;
    // Sublist headers: nodes with first data node pointer at +0x0C
    int* pSubListHead = nullptr;
    // Data nodes: hold actual short values at +0x0C
    int* pDataNode = nullptr;
    int byteOffset = 0;

    do {
        // Advance to next data node if current exists and has a next pointer
        if (pDataNode == nullptr || (pDataNode = *(int**)(pDataNode + 1), pDataNode == nullptr)) {
            // Advance to next sublist header if current exists and has next
            if (pSubListHead == nullptr || (pSubListHead = *(int**)(pSubListHead + 1), pSubListHead == nullptr)) {
                // Advance to next top-level node (lazy initialization on first call)
                if (pTopNode == nullptr) {
                    pTopNode = *(int**)(this + 0x24);    // pointer to first top node
                } else {
                    pTopNode = *(int**)(pTopNode + 1);   // next top node (+0x04)
                }
                if (pTopNode != nullptr) {
                    pSubListHead = *(int**)(pTopNode + 3); // sublist head pointer (+0x0C)
                }
                if (pSubListHead != nullptr) goto FetchDataNode;
            } else {
FetchDataNode:
                pDataNode = *(int**)(pSubListHead + 3); // first data node pointer (+0x0C)
            }
            if (pDataNode == nullptr) return;
        }

        // Read the short value from the data node (+0x0C)
        int value = *(int*)(pDataNode + 3);
        // Write it into the output buffer (base at +0x14)
        *(short*)((char*)*(int**)(this + 0x14) + byteOffset) = (short)value;
        byteOffset += 2;

        // Sentinel value -1 terminates the flattened list
        if (value == -1) return;
    } while (true);
}