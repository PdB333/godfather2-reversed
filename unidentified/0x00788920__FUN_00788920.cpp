// FUNC_NAME: UnknownClass::addNodeToList

void __thiscall UnknownClass::addNodeToList(int* thisPtr, int* nodePtr, char triggerFlag)
{
    int dataPtr;
    float value;

    // Get data pointer from node's second field
    dataPtr = getDataPointer(nodePtr[1]);

    // If list is empty, use first value; otherwise use second value
    if (*thisPtr == 0) {
        value = *(float*)(dataPtr + 8);
    } else {
        value = *(float*)(dataPtr + 0xC);
    }

    // Accumulate values into counters at this+0x1C and this+0x20
    thisPtr[7] = (int)(value + (float)thisPtr[7]);
    thisPtr[8] = (int)(*(float*)(dataPtr + 0x10) + (float)thisPtr[8]);

    // Clear node's next pointer
    *nodePtr = 0;

    // Link node at end of list (tail pointer in thisPtr[1])
    if ((int*)thisPtr[1] == (int*)0x0) {
        *thisPtr = (int)nodePtr;           // head = node
    } else {
        *(int*)thisPtr[1] = (int)nodePtr;  // old tail->next = node
    }
    thisPtr[1] = (int)nodePtr;             // tail = node

    if (triggerFlag != '\0') {
        triggerListUpdate();
    }
}