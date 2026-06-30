// FUNC_NAME: EAStreamManager::processLoadRequests
void __thiscall EAStreamManager::processLoadRequests(void* thisPtr, int param2)
{
    char isDone;
    int state;
    int tempPtr;
    int* listHead;
    int currentSlot;

    tempPtr = param2;
    beginIteration(param2);
    setHash(tempPtr, 0x5576abcd);
    isDone = isIterationDone();
    do {
        if (isDone != '\0') {
            return;
        }
        getCurrentItem();
        state = getNextState();
        switch(state) {
        case 0:
            currentSlot = thisPtr + 0x68;
            tempPtr = currentSlot;
            getCurrentItem(currentSlot);
            advanceItem(tempPtr);
            {
                int handle = getObjectFromSlot(tempPtr, 0);
                param2 = 0;
                isDone = resolveHandleByHash(handle, 0x55859efa, &param2);
                if ((isDone != '\0') && (param2 != 0)) {
                    listHead = (int*)(thisPtr + 0x78);
                    goto LINK_SLOT;
                }
            }
            break;
        case 1:
            currentSlot = thisPtr + 0x58;
            tempPtr = currentSlot;
            getCurrentItem(currentSlot);
            advanceItem(tempPtr);
            {
                int handle = getObjectFromSlot(tempPtr, 0);
                param2 = 0;
                isDone = resolveHandleByHash(handle, 0x55859efa, &param2);
                if ((isDone != '\0') && (param2 != 0)) {
                    listHead = (int*)(thisPtr + 0x80);
                    goto LINK_SLOT;
                }
            }
            break;
        case 2:
            tempPtr = getCurrentItem();
            *(int*)(thisPtr + 0x90) = *(int*)(tempPtr + 8);
            *(unsigned int*)(thisPtr + 0x94) |= 0x80000;
            break;
        case 3:
            *(unsigned int*)(thisPtr + 0x94) = 0;
            tempPtr = getCurrentItem();
            *(unsigned int*)(thisPtr + 0x94) |= 1 << ((byte)*(int*)(tempPtr + 8) & 0x1f);
            break;
        }
        endIteration();
        isDone = isIterationDone();
    } while( true );

LINK_SLOT:
    tempPtr = param2;
    currentSlot = param2 + 0x48;
    if (*listHead != currentSlot) {
        if (*listHead != 0) {
            freeListItem(listHead);
        }
        *listHead = currentSlot;
        if (currentSlot != 0) {
            listHead[1] = *(int*)(param2 + 0x4c);
            *(int**)(param2 + 0x4c) = listHead;
        }
    }
}