// FUNC_NAME: SimObject::processScriptEvent
int SimObject::processScriptEvent(int eventData) {
    uint entry;
    int *tablePtr;
    int result;
    int index;
    uint actionType;

    // Check conditions:
    // - Either the "active" flag at this+0x08 bit0 is set, or the "health" at this+0x14 is less than 1
    // - AND the "processing" flag at this-0x10 bit0 is clear
    if ((((*(byte *)(this + 0x08) & 1) != 0) || (*(int *)(this + 0x14) < 1)) &&
        ((*(byte *)(this - 0x10) & 1) == 0))
    {
        tablePtr = (int *)(this - 0x18);  // pointer to script action table

        if ((*(uint *)(this - 0x10) & 1) == 0) {
            if ((*(uint *)(this - 0x10) & 2) != 0) {
                // If "updateIndex" flag is set, copy current action pointer from this-0x08 to this-0x0c
                *(int *)(this - 0x0c) = **(int **)(this - 0x08);
            }
            // Calculate index into the action table:
            // index = (currentActionPos - arrayBase) / 4 - 1
            // arrayBase comes from: *(int*)(*(int*)(*(int*)(*tablePtr - 4) + 0xc) + 0xc)
            index = (*(int *)(this - 0x0c) -
                     *(int *)(*(int *)(*(int *)(*tablePtr - 4) + 0xc) + 0xc) >> 2) - 1;
        } else {
            index = -1;
        }

        // Read the action entry at the computed index
        entry = *(uint *)(*(int *)(*(int *)(*(int *)(*tablePtr - 4) + 0xc) + 0xc) + index * 4);
        actionType = entry & 0x3f;  // low 6 bits = action type

        // Handle trigger actions (type 0x19 = PlayAnimation, 0x1a = PlaySound)
        if (actionType == 0x19 || actionType == 0x1a) {
            result = FUN_00633500(tablePtr, (int)entry >> 0x18, eventData);
            return result;
        }
    }
    return 0;
}