// FUNC_NAME: VariableManager::setVariable
// Function at 0x00894d00: Updates a variable value, triggers range-based events and registered callbacks.
bool __thiscall VariableManager::setVariable(int thisPtr, VariableRecord* record, int newValue, uint flags)
{
    float oldValue;
    int id;
    int callbackCount;
    int i;
    ushort* strPtr;
    char buffer[20]; // temporary string buffer
    int local_8[2];

    // Check if record is active and manager allows updates
    if ((record->flags & 1) != 0 || (*(byte*)(thisPtr + 0x34) & 2) != 0) {
        return false;
    }

    oldValue = (float)record->value;
    record->value = newValue;

    // If no string processing flag and there's a string pointer, process property name/command list
    if ((flags & 2) == 0 && record->stringPtr != NULL) {
        FUN_00892af0(5); // likely debug/logging
        strPtr = (ushort*)record->stringPtr;
        while (FUN_008948a0(strPtr, buffer) != '\0') {
            strPtr = (ushort*)((int)strPtr + *strPtr); // advance by length prefix
        }
        if (local_8[0] != 0) {
            FUN_004daf90(local_8); // cleanup
        }
    }

    // Check for range-based triggers (always if count > 0)
    if (record->rangeCount != 0) {
        float* rangeArray = (float*)(*(int*)(*(int*)(thisPtr + 0x2c) + 0x20) + record->rangeIndex * 12);
        float* endPtr = rangeArray + record->rangeCount * 3;
        for (; rangeArray < endPtr; rangeArray += 3) {
            float low = rangeArray[0];
            float high = rangeArray[1];
            float triggerData = rangeArray[2];
            // Trigger when old value is outside and new value enters [low, high)
            if (((oldValue < low) || (high <= oldValue)) && (low <= (float)newValue) && ((float)newValue < high)) {
                FUN_00894c90(triggerData); // fire event with callback data
            }
        }
    }

    // Notify registered callbacks for this variable ID
    callbackCount = *(int*)(thisPtr + 0x4c);
    if (callbackCount != 0) {
        id = record->id;
        for (i = 0; i < callbackCount; i++) {
            int* entry = (int*)(*(int*)(thisPtr + 0x48) + i * 8);
            if (entry[0] == id) {
                // Call registered handler (entry[1] is function pointer)
                (*(void(__thiscall**)(int, int))entry[1])(id, newValue);
            }
        }
    }

    return true;
}