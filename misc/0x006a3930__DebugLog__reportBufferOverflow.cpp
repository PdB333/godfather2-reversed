// FUNC_NAME: DebugLog::reportBufferOverflow
void __thiscall DebugLog::reportBufferOverflow(int thisPtr, int nearValue)
{
    wchar_t buffer[80]; // local_50: buffer for error message

    // Check if an output sink exists (pointer at this+0x4)
    if (*(int *)(thisPtr + 4) != 0)
    {
        // Format the error message: "E02: The text near %d didn't fit in the buffer"
        formatErrorMessage(buffer, L"E02: The text near %d didn't fit in the buffer", nearValue);

        // Call the virtual method at vtable+4 on the sink object
        // The sink is a pointer to an object with a vtable; index 1 is the output method
        (**(void (__thiscall **)(void *, wchar_t *))(**(int **)(thisPtr + 4) + 4))(*(int *)(thisPtr + 4), buffer);
    }
    // No return value
}