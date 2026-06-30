// FUNC_NAME: ProcessCallbackQueues
// Address: 0x006911b0
// Processes two callback queues (queue1 at offset 0x564, queue2 at offset 0x565) 
// Each queue has a current index (DAT_00e50698, DAT_00e50650) and an array (64 slots).
// Iterates backward to find the highest-priority callback (non-zero entry) and dispatches it.

void ProcessCallbackQueues(void)
{
    char queue1State = *(char *)(DAT_012233b4 + 0x564);
    char queue2State = *(char *)(DAT_012233b4 + 0x565);
    int callbackValue;
    int *queuePtr;
    int queueIndex;

    // Process first queue (queue1) if not in idle state (0x12) and index valid
    if ((queue1State != 0x12) && (DAT_00e50698 != -1) &&
        ((&DAT_00e50658)[DAT_00e50698] != 0))
    {
        callbackValue = 0;
        // Iterate backwards from current index, find the last non-zero callback
        for (; (DAT_00e50698 != -1) && (queuePtr = &DAT_00e50658 + DAT_00e50698, *queuePtr != 0);
             DAT_00e50698 = DAT_00e50698 - 1)
        {
            callbackValue = *queuePtr;
        }
        // Get the associated object from the global instance using queue1 state
        queuePtr = (int *)FUN_00411070(*(char *)(DAT_012233b4 + 0x564));
        // Call vtable function at index 2 (offset 8) on that object
        (**(code **)(*queuePtr + 8))(callbackValue);
    }

    // Process second queue (queue2) similarly
    if ((*(char *)(DAT_012233b4 + 0x565) != 0x12) && (DAT_00e50650 != -1) &&
        ((&DAT_00e50610)[DAT_00e50650] != 0))
    {
        callbackValue = 0;
        for (; (DAT_00e50650 != -1) && (queuePtr = &DAT_00e50610 + DAT_00e50650, *queuePtr != 0);
             DAT_00e50650 = DAT_00e50650 - 1)
        {
            callbackValue = *queuePtr;
        }
        queuePtr = (int *)FUN_00411070(*(char *)(DAT_012233b4 + 0x565));
        (**(code **)(*queuePtr + 8))(callbackValue);
    }
    return;
}