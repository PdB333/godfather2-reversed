// FUNC_NAME: EventManager::processEventQueue

int * __fastcall EventManager::processEventQueue(int *this)
{
    int *nodePtr;
    int64_t timeData;
    char isActive;
    int tempInt;
    double tempDouble;
    int64_t stackTimeData;
    float stackDelta;
    int stackNode;
    int stackPrevPtr;
    int stackCurrent;
    byte arrayBuffer[12];
    int listHead[2];
    int listTail;
    
    // Check if the event manager is active (virtual function at vtable+0x28c)
    isActive = (**(code **)(*this + 0x28c))();
    if (isActive != 0) {
        // Get current time data (likely from a time manager singleton)
        tempInt = getTimeData(); // FUN_00471610
        timeData = *(int64_t *)(tempInt + 0x30); // current time (int64)
        stackDelta = *(float *)(tempInt + 0x38); // delta time?
        
        // Check if a new event should be spawned based on timing conditions
        // Conditions: if no last time stored, or time difference exceeds threshold (after wrapping)
        if ((((this[0x6ff] == 0) ||
             (stackTimeData._0_4_ = (float)timeData,
             DAT_00e44948 < (float)((uint)((float)stackTimeData - (float)this[0x700]) & DAT_00e44680)))
            || (stackTimeData._4_4_ = (float)((uint64_t)timeData >> 32),
               DAT_00e44948 < (float)((uint)(stackTimeData._4_4_ - (float)this[0x701]) & DAT_00e44680)))
           || (DAT_00e44948 < (float)((uint)(stackDelta - (float)this[0x702]) & DAT_00e44680))) {
            // Allocate a new event node (32 bytes)
            stackTimeData = timeData;
            allocate(DAT_00d62bd4, 0x20); // FUN_006a84c0 - memory allocation
            stackTimeData = CONCAT44(stackTimeData._4_4_ + _DAT_00d723c0, (float)stackTimeData);
            copyData(&stackTimeData, arrayBuffer, DAT_00d62bd4); // FUN_005fcf80 - copy into buffer
            
            // Save current list head for later restoration
            stackNode = this[0x6fc]; // head node pointer
            nodePtr = this + 0x6fc; // address of head pointer
            stackPrevPtr = 0;
            if (stackNode != 0) {
                stackPrevPtr = *(int *)(stackNode + 4); // prev pointer of head
                *(int **)(stackNode + 4) = &stackNode; // circular list? might be wrong
            }
            stackCurrent = this[0x6fe]; // tail pointer?
            
            // Insert the new node into the linked list (singly/doubly linked)
            if ((nodePtr != (int *)listHead) && (*nodePtr != listHead[0])) {
                if (*nodePtr != 0) {
                    freeNode(nodePtr); // FUN_004daf90 - free old node
                }
                *nodePtr = listHead[0];
                if (listHead[0] != 0) {
                    this[0x6fd] = *(int *)(listHead[0] + 4);
                    *(int **)(listHead[0] + 4) = nodePtr;
                }
            }
            this[0x6fe] = listTail; // update tail
            
            // Store timestamp information
            this[0x700] = (int)stackTimeData; // low part of time
            this[0x701] = (int)(stackTimeData >> 32); // high part
            this[0x6ff] = DAT_01205224; // some global ID/counter
            this[0x702] = (int)stackDelta; // delta
            
            // Clean up previous head if it existed
            if (stackNode != 0) {
                freeNode(&stackNode); // FUN_004daf90
            }
            updateTime(); // FUN_006a8530 - update internal time tracking
        }
        return this + 0x6fc; // return pointer to event list head
    }
    // If not active, clear the event queue
    if (this[0x6fc] != 0) {
        freeNode(this + 0x6fc); // FUN_004daf90
        this[0x6fc] = 0;
    }
    this[0x6fe] = 0;
    return this + 0x6fc;
}