// FUNC_NAME: DebugCommandProcessor::processQueue

// Process a queue of debug commands (type 3 = float value, type 4 = read from input)
// Offsets: +0x08 = pointer to end of queue, +0x0C = current pointer in queue
int DebugCommandProcessor::processQueue()
{
    QueueItem* currentItem = *(QueueItem**)((uintptr_t)this + 0x0C);
    QueueItem* endItem = *(QueueItem**)((uintptr_t)this + 0x08);

    // Validate current position
    if (endItem <= currentItem) goto resetFloat;
    if (currentItem == nullptr) goto resetFloat;

    // Handle item type
    if (currentItem->type != 3)
    {
        if (currentItem->type != 4) goto resetFloat;

        float readValue;
        int readResult = readFloatFromInput(&readValue); // FUN_00636850
        if (readResult == 0) goto resetFloat;

        // Create temporary type 3 item with the read value
        QueueItem tempItem;
        tempItem.type = 3;
        tempItem.value = readValue;
        currentItem = &tempItem;
    }

    float value = currentItem->value;

    // Sentinel value triggers an active scan for next printable item
    static const float kSentinelValue = *(float*)0x00e2b05c; // DAT_00e2b05c
    if (value == kSentinelValue)
    {
        do
        {
            currentItem = *(QueueItem**)((uintptr_t)this + 0x0C);

            if ((currentItem < endItem) && (currentItem != nullptr))
            {
                if (currentItem->type == 3) break;
                if (currentItem->type == 4)
                {
                    float temp;
                    int res = readFloatFromInput(&temp);
                    if (res != 0) break;
                }
            }

            debugPrintString("number"); // FUN_00627ac0
resetFloat:
            value = 0.0f;
        } while (true);
    }

    // Round the float to integer and output it
    int intValue = (int)(value + 0.5f); // Rounding approximation (original used FPU control word)
    debugPrintInt(intValue); // FUN_00b9a183
    return 0;
}