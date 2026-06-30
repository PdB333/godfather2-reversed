// FUNC_NAME: DebugManager::logBufferTrim
void __thiscall DebugManager::logBufferTrim(int someFlag, int trimOffset, int unusedParam) {
    // Check if the flag indicates an invalid state
    if ((someFlag != 0) && (someFlag < 1)) {
        // Trigger assertion failure or error handler
        assertFail();
    }

    // Calculate the new buffer position: move back (trimOffset * 8 + 8) bytes from the current pointer at +0x8
    int newPosition = *(int *)(this + 0x8) - (trimOffset * 8 + 8);
    int localUnused = unusedParam; // Stored but not used in the subsequent call

    // Log the trim operation: format string at LAB_006261e0, new pointer address, and the difference from a limit at +0x1c
    formatOutput(&formatString, &newPosition, newPosition - *(int *)(this + 0x1c));
}