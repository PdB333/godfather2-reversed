//FUNC_NAME: ScriptStack::parseCommand
void __thiscall ScriptStack::parseCommand(int thisPtr, char *commandString)
{
    uint *parsedValuePtr;
    char *popSubstring;
    int stackIndex;
    float parsedFloat;
    uint *outParsedValue;

    // Check if global stack base is initialized
    if (g_stackBase != (undefined *)0x0) {
        outParsedValue = (uint *)*in_stack_00000014;
        if (outParsedValue == (uint *)0x0) {
            // Allocate a new ParsedValue structure (12 bytes: flags, value, delta)
            outParsedValue = (uint *)(*g_allocateMemory)(0xc, 0);
            *in_stack_00000014 = outParsedValue;

            // Check if command contains "pop"
            popSubstring = _strstr(commandString, "pop");
            if ((popSubstring == (char *)0x0) || (popSubstring == (char *)0xfffffffd)) {
                // No "pop" found: parse a float value
                *outParsedValue = 0;
                if (parseFloat(commandString) != 0) {
                    *outParsedValue |= 1; // Flag: first value parsed
                }
                parsedFloat = getParsedFloat(commandString);
                outParsedValue[1] = *(uint *)&parsedFloat; // Store float as uint

                // Try to parse a second float (delta)
                if (parseFloat(commandString) != 0) {
                    *outParsedValue |= 4; // Flag: delta parsed
                    parsedFloat = getParsedFloat(commandString);
                    outParsedValue[2] = *(uint *)&(parsedFloat - *(float *)&outParsedValue[1]); // Store difference
                    if (parseFloat(commandString) != 0) {
                        *outParsedValue |= 8; // Flag: additional value? (unused)
                    }
                }
            } else {
                // "pop" command: set flag to 2
                *outParsedValue = 2;
            }
        }

        // Execute based on parsed flags
        if ((*outParsedValue & 2) != 0) {
            // Pop operation: decrement stack index if possible
            if (*(int *)(thisPtr + 0xc10) >= 0) {
                *(int *)(thisPtr + 0xc10) = *(int *)(thisPtr + 0xc10) - 1;
            }
            if (*(int *)(thisPtr + 0xc10) >= 0) {
                // Set global stack pointer to the element at new index
                g_currentStackPtr = (undefined *)(*(int *)(thisPtr + 0xc10) * 0x40 + 0x10 + thisPtr);
                return;
            }
            // Stack underflow: set to base
            g_currentStackPtr = g_stackBase;
            return;
        }

        if ((*outParsedValue & 1) != 0) {
            // Push operation with one value
            stackIndex = *(int *)(thisPtr + 0xc10);
            stackOperation(); // Adjust stack? (called twice)
            stackOperation();
            // Set global stack pointer to the next slot
            g_currentStackPtr = (undefined *)(thisPtr + (stackIndex + 1) * 0x40 + 0x10);
            return;
        }

        // Default: push operation (no flags? or push with delta?)
        *(int *)(thisPtr + 0xc10) = *(int *)(thisPtr + 0xc10) + 1;
        stackOperation();
        stackOperation();
        g_currentStackPtr = (undefined *)(*(int *)(thisPtr + 0xc10) * 0x40 + 0x10 + thisPtr);
    }
}