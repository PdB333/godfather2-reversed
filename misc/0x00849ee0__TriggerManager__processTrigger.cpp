// FUNC_NAME: TriggerManager::processTrigger
// Address: 0x00849ee0
// Role: Validates a trigger ID and, if a corresponding handler exists, executes it with given data.
// Class: TriggerManager (inferred) - manages an array of trigger handlers at offset +0x10.

void __thiscall TriggerManager::processTrigger(void* thisPtr, int triggerID, void* data)
{
    int index;

    if (triggerID != 0)
    {
        index = FUN_00849a70(triggerID);  // Convert trigger ID to handler index
        if ((index >= 0) && (**(int**)(*(int*)((char*)thisPtr + 0x10) + index * 4) != 0))
        {
            FUN_008496a0(data);  // Execute the handler with provided data
        }
    }
    return;
}