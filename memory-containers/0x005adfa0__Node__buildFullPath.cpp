// FUNC_NAME: Node::buildFullPath
uint Node::buildFullPath(int param_1, int param_2, uint param_3, int param_4)
{
    char statusFlag;
    uint lengthWritten;
    int tempVar1;
    int tempVar2;
    undefined4 sourceData;
    int newPos;

    // Check global initialization flags
    statusFlag = checkInitialization1();
    if (((statusFlag == '\0') && (statusFlag = checkInitialization2(), statusFlag == '\0')) &&
        (statusFlag = checkInitialization3(), statusFlag == '\0')) {
        errorHandler(); // assert or crash
    }

    // If no parent yet (root node)
    if (*(int *)(param_1 + 0x54) == 0) {
        statusFlag = checkAnotherInit();
        if ((statusFlag == '\0') && (statusFlag = checkInitialization2(), statusFlag == '\0')) {
            errorHandler();
        }
        // Validate param_4 (0 or 1 only)
        if (param_4 == 0) {
            if (*(int *)(param_1 + 0x30) == 0) {
                return 0;
            }
        }
        else if (param_4 != 1) {
            return 0;
        }
        // Write "_level" into buffer at current position
        lengthWritten = stringCopySafely("_level", param_2, param_3);
        if (param_3 <= lengthWritten) {
            errorHandler();
        }
        // Copy the node's name (from +0x30) after "_level"
        newPos = copyFromSource(*(undefined4 *)(param_1 + 0x30), lengthWritten + param_2, param_3 - lengthWritten);
        lengthWritten = lengthWritten + newPos;
    }
    else {
        // Recursively build parent path
        lengthWritten = Node::buildFullPath(*(int *)(param_1 + 0x54), param_2, param_3, param_4);
        if (param_3 - 1 <= lengthWritten) {
            errorHandler();
        }
        // Write separator: '.' if param_4 == 0, '/' if param_4 == 1
        *(char *)(lengthWritten + param_2) = (param_4 == 0) + '.';
        newPos = lengthWritten + 1;

        // If the cached child path pointer (+0x34) is null, build the instance path
        if (*(int *)(param_1 + 0x34) == 0) {
            // Use the node's name pointer from +0x30
            sourceData = *(undefined4 *)(param_1 + 0x30);
            int currentBufferPos = newPos + param_2;
            int written1 = stringCopySafely("instance", currentBufferPos, param_3 - newPos);
            lengthWritten = newPos + written1;
            if (param_3 <= lengthWritten) {
                errorHandler();
            }
            int written2 = copyFromSource(sourceData, lengthWritten + param_2, param_3 - lengthWritten);
            if (param_3 <= lengthWritten + written2) {
                errorHandler();
            }
            // Allocate a new node object (size 0x24) and cache it at +0x34
            int allocResult = (*DAT_0119caf0)(0x24, 0);
            if (allocResult == 0) {
                sourceData = 0;
            }
            else {
                sourceData = allocConstructor(allocResult);
            }
            *(undefined4 *)(param_1 + 0x34) = sourceData;
            initializeNewObject();
            // Find the node by name and register the path
            int foundNode = findObjectByName(currentBufferPos, param_1);
            registerPath(*(undefined4 *)(foundNode + 0xc), currentBufferPos, param_1);
            return lengthWritten + written2;
        }
        // If cached path exists, just append the cached instance name
        int written3 = stringCopySafely(*(undefined4 *)(*(int *)(param_1 + 0x34) + 0xc),
                                        newPos + param_2,
                                        param_3 - newPos);
        lengthWritten = newPos + written3;
    }

    if (param_3 <= lengthWritten) {
        errorHandler();
    }
    return lengthWritten;
}