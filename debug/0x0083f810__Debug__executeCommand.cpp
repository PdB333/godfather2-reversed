// FUNC_NAME: Debug::executeCommand
undefined1 __thiscall Debug::executeCommand(int thisPtr, int commandId, int pathString) {
    int pathHandle;
    uint* hashResultPtr;
    int hashData;
    int pathArray[2];
    undefined4 dummy;

    if (commandId == 0) {
        return 0;
    }

    // Resolve the path string into a handle
    ResolvePath(pathArray, pathString);
    pathHandle = pathArray[0];

    // If path is valid but IsPathValid returns false, abort
    if ((pathHandle != 0) && (IsPathValid(pathHandle, dummy) == '\0')) {
        return 0;
    }

    // Check debug override flag at +0x14c (bit 0)
    if ((*(byte*)(thisPtr + 0x14c) & 1) != 0) {
        int local_14 = 0;
        hashResultPtr = nullptr;

        // Look up hash 0xee654334 from the path's short at offset 8
        char result = GetHashValue(*(short*)(pathString + 8), 0xee654334, &local_14);
        if (result != '\0') {
            uint flags = 0;
            if ((hashResultPtr != nullptr) && (local_14 != 0) && (*(char*)(local_14 + 6) == '\x02')) {
                flags = *hashResultPtr;
            }
            // If flag bit 2 is not set, abort
            if ((flags & 4) == 0) {
                return 0;
            }
        }
    }

    // Execute the command action
    undefined1 result = ExecuteAction(commandId, pathString);

    // Cleanup path handle if allocated
    if (pathHandle != 0) {
        FreePath(pathArray);
    }

    return result;
}