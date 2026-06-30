// FUNC_NAME: LuaState::resolveVariable
char* LuaState::resolveVariable(int* state, uint nameHash, int** outValue)
{
    byte flags;
    int tablePtr;
    int index;
    int resolvedValue;
    uint result;

    flags = *(byte*)(state + 2);
    while ((flags & 1) == 0) {
        tablePtr = *(int*)(*(int*)(*state + -4) + 0xc); // +0x0C: current table pointer
        if ((state[2] & 1U) == 0) {
            if ((state[2] & 2U) != 0) {
                state[3] = *(int*)state[4]; // +0x0C: local variable slot
            }
            index = (state[3] - *(int*)(*(int*)(*(int*)(*state + -4) + 0xc) + 0xc) >> 2) + -1; // Calculate stack index
        }
        else {
            index = -1;
        }
        resolvedValue = FUN_006384a0(nameHash + 1); // Check if name is a reserved word
        *outValue = resolvedValue;
        if (resolvedValue != 0) {
            return "local";
        }
        result = FUN_00633100(tablePtr, index, nameHash); // Lookup in table
        switch(result & 0x3f) {
        case 0: // Not found, try upvalue
            nameHash = (int)result >> 0xf & 0x1ff;
            if ((int)result >> 0x18 <= (int)nameHash) {
                return (char*)0x0;
            }
            flags = *(byte*)(state + 2);
            break;
        default:
            goto switchD_0063357f_caseD_1;
        case 5: // Global variable
            *outValue = *(int*)(*(int*)(tablePtr + 8) + 4 + ((int)result >> 6 & 0x3ffffU) * 8) + 0x10;
            return "global";
        case 6: // Field access
            resolvedValue = FUN_006334e0(); // Get field offset
            *outValue = resolvedValue;
            return "field";
        case 0xb: // Method call
            resolvedValue = FUN_006334e0(); // Get method pointer
            *outValue = resolvedValue;
            return "method";
        }
    }
switchD_0063357f_caseD_1:
    return (char*)0x0;
}