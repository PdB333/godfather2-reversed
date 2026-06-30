// FUNC_NAME: AptDisplayListNode::removeFromList
void AptDisplayListNode::removeFromList()
{
    // Debug assertion: this must not be null
    if (this == nullptr) {
        // Assertion: "pItem != 0" at ..\source\Apt\AptDisplayList.cpp line 100
        const char* condition = "pItem != 0";
        const char* file = "..\\source\\Apt\\AptDisplayList.cpp";
        int line = 100;
        int severity = 2;
        bool* assertFlag = &DAT_0112900f; // global assert enable flag
        if (*assertFlag != '\0') {
            int* threadData = *(int**)(*(int**)(__readfsdword(0x2c)) + 0x30);
            uint result = 1;
            if (threadData != nullptr) {
                result = (**(code**)(*threadData + 8))(&condition, condition);
            }
            if ((result & 2) != 0) {
                *assertFlag = 0;
            }
            if ((threadData != nullptr) || (severity == 4)) {
                if ((result & 1) != 0 || (severity == 0 || severity == 1)) {
                    // Trigger debug break
                    __debugbreak();
                }
            }
        }
    }

    // Unlink this node from the doubly linked list
    if (this->pPrev != nullptr) {
        // Assert: pItem->pPrev->pNext == pItem
        if (this->pPrev->pNext != this) {
            const char* condition = "pItem->pPrev->pNext == pItem";
            const char* file = "..\\source\\Apt\\AptDisplayList.cpp";
            int line = 0x68;
            int severity = 2;
            bool* assertFlag = &DAT_01129010;
            FUN_0059bf00(); // assertion failure handler
        }
        this->pPrev->pNext = this->pNext;
    }

    if (this->pNext != nullptr) {
        // Assert: pItem->pNext->pPrev == pItem
        if (this->pNext->pPrev != this) {
            const char* condition = "pItem->pNext->pPrev == pItem";
            const char* file = "..\\source\\Apt\\AptDisplayList.cpp";
            int line = 0x6d;
            int severity = 2;
            bool* assertFlag = &DAT_01129011;
            FUN_0059bf00(); // assertion failure handler
        }
        this->pNext->pPrev = this->pPrev;
    }

    // Clear this node's links
    this->pPrev = nullptr;
    this->pNext = nullptr;
}