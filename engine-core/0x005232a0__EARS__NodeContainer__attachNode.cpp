// FUNC_NAME: EARS::NodeContainer::attachNode
void __thiscall NodeContainer::attachNode(undefined4 data, undefined4 unusedParam, int nodePtr, char enableFlag) {
    // Offsets:
    // +0x450: m_byte1 (char)
    // +0x451: m_byte2 (char)
    // +0x454: m_data (undefined4)
    // +0x458: m_headPtr (int*)
    // +0x45c: m_nextRef (int) - stores the old next of the new head
    // +0x460: m_flags (unsigned short)
    // +0x462: m_shortField (unsigned short)
    // +0x464: m_subObject (subobject of unknown type)

    this->m_flags = 0;
    if (enableFlag != '\0') {
        this->m_flags |= 1;
    }
    this->m_data = data;

    int* headPtrAddr = &this->m_headPtr;
    int newHead;
    if (nodePtr == 0) {
        newHead = 0;
    } else {
        newHead = nodePtr + 4;
    }

    if (*headPtrAddr != newHead) {
        if (*headPtrAddr != 0) {
            releaseHead(headPtrAddr);  // Remove the old head from the list
        }
        *headPtrAddr = newHead;
        if (newHead != 0) {
            // Save the old next pointer of the new head and make it point back to the head pointer address
            this->m_nextRef = *(int*)(newHead + 4);
            *(int**)(newHead + 4) = headPtrAddr;
        }
    }

    this->m_shortField = 0;
    this->m_byte1 = 0;
    initSubObject(&this->m_subObject);  // Initialize the sub-object

    if (this->m_byte2 == '\0') {
        initNode(nodePtr);  // Initialize the node itself
    }
}