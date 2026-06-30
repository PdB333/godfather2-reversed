// FUNC_NAME: GameplayDebugger::debugUpdateSelectedObject

void __fastcall GameplayDebugger::debugUpdateSelectedObject(int thisPtr)
{
    int *selectedObject;
    char debugString[12];
    int objectHash;
    int scriptContext;
    int tempPtr;
    char conditionFlag;

    // Check if there is a selected object pointer at offset 0x24c4
    if (*(int *)(thisPtr + 0x24c4) != 0)
    {
        selectedObject = (int *)(*(int *)(thisPtr + 0x24c4) - 0x48); // Adjust for embedded object offset
        if (selectedObject != (int *)0x0)
        {
            // Check flag at offset 0x1f58 bit 22 (0x400000) – indicates debug output already done this frame
            if ((*(uint *)(thisPtr + 0x1f58) >> 0x16 & 1) == 0)
            {
                // Get debug name string from the selected object and print it
                GameplayDebugger::getObjectDebugName(debugString, selectedObject);
                GameplayDebugger::printDebugString(debugString);
                *(uint *)(thisPtr + 0x1f58) |= 0x400000; // Set flag to avoid repeating
            }

            // Check another object pointer at offset 0x74c
            if ((*(int *)(thisPtr + 0x74c) != 0) && (*(int *)(thisPtr + 0x74c) != 0x48))
            {
                if (*(int *)(thisPtr + 0x74c) == 0)
                    tempPtr = 0;
                else
                    tempPtr = *(int *)(thisPtr + 0x74c) - 0x48;

                // Check byte at offset 0x1a8 (possibly a flag to enable debug callback)
                if (*(char *)(tempPtr + 0x1a8) != '\x01')
                {
                    if (*(int *)(thisPtr + 0x74c) == 0)
                        tempPtr = 0;
                    else
                        tempPtr = *(int *)(thisPtr + 0x74c) - 0x48;
                    // Check bit 2 at offset 0x1d0
                    if ((*(uint *)(tempPtr + 0x1d0) >> 2 & 1) == 0)
                        goto LAB_0072baf5;
                }

                // Compare hash at offset 0x1ed4 with constant 0x637b907 (likely a script function ID)
                if (*(int *)(thisPtr + 0x1ed4) == 0x637b907)
                {
                    scriptContext = ScriptManager::getScriptContext(1);
                    // Call script function with hash 0x637b907
                    ScriptManager::callFunctionByHash(0x637b907, scriptContext, 1);
                }
                else
                {
                    objectHash = 0;
                    // Call a virtual method on the selected object (vtable+0x10) with argument 0x55859efa
                    conditionFlag = (*(char (__thiscall **)(int *, int *))(*(int *)selectedObject + 0x10))(0x55859efa, &objectHash);
                    if (((conditionFlag == '\0') || (objectHash == 0)) || (*(int *)(objectHash + 0x1ed4) != 0x637b907))
                        goto LAB_0072baf5;

                    // Retrieve the hash from this object and call the script
                    scriptContext = ScriptManager::getScriptContext(1);
                    ScriptManager::callFunctionByHash(*(int *)(thisPtr + 0x1ed4), scriptContext, 1);
                }
            }
        }
    }

LAB_0072baf5:
    // Cleanup debug state
    DebugManager::popDebugState();
    // Clear the debug output flag (bit 22)
    *(uint *)(thisPtr + 0x1f58) &= 0xffbfffff;
    return;
}