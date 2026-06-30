// FUNC_NAME: CharacterAppearanceBuilder::processCommand
int CharacterAppearanceBuilder::processCommand() {
    int *pCmdRead = *(int **)(this + 0x0C); // current read pointer into command buffer
    int resultHandle = 0;

    // Validate current read pointer: must be in valid range and have type 4 or 3
    if (((*(int **)(this + 0x08) <= pCmdRead) || (pCmdRead == (int *)0x0)) ||
        ((*pCmdRead != 4 && (*pCmdRead != 3)))) {
        goto LAB_00436cfe;
    }

    int dataPtr = 0;
    if ((pCmdRead < *(int **)(this + 0x08)) && (pCmdRead != (int *)0x0)) {
        if (*pCmdRead == 4) {
            // Type 4: data is a direct pointer (offset 0x10 bytes into a structure)
            dataPtr = pCmdRead[1] + 0x10;
        } else {
            // Type 3: resolve pointer through a lookup function (e.g., hash table)
            int lookupResult = FUN_00633990(this);
            if (lookupResult == 0) {
                dataPtr = 0;
            } else {
                dataPtr = pCmdRead[1] + 0x10;
            }
            // Check if output buffer has overflowed
            if (*(uint *)(*(int *)(this + 0x10) + 0x20) <= *(uint *)(*(int *)(this + 0x10) + 0x24)) {
                FUN_00627360(); // perhaps a buffer overflow handler
            }
        }
    } else {
        dataPtr = 0;
    }

    // Prepare output command buffer (8 bytes)
    int outputBuffer[2]; // aligned to 8 bytes? Actually 8 ints but we only use some
    int outputCmd[8] = {0}; // initialize to zero; corresponds to local_28..local_c

    // Read additional command from offset +0x18 of current command (type 1 check)
    int *pCmd = (int *)(*(int *)(this + 0x0C) + 0x18);
    if (((pCmd < *(int **)(this + 0x08)) && (pCmd != (int *)0x0)) &&
        (*pCmd == 1) &&
        ((pCmd < *(int **)(this + 0x08) && (pCmd != (int *)0x0))) &&
        ((*pCmd != 0 && ((*pCmd != 1 || (*(int *)(*(int *)(this + 0x0C) + 0x1C) != 0)))))) {
        outputCmd[3] = 1; // local_1c = 1
    }

    // Read another command at +0x28 (type 3 or 4 with color validation)
    pCmd = (int *)(*(int *)(this + 0x0C) + 0x28);
    if (((pCmd < *(int **)(this + 0x08)) && (pCmd != (int *)0x0)) &&
        ((*pCmd == 3 || (*pCmd == 4 && (FUN_00636850(&outputCmd[4]) != 0))))) {
        float floatVal = (float)FUN_006259b0(this, 6); // get a color/weight value
        outputCmd[4] = (int)ROUND(floatVal); // store as integer (maybe color component)
    }

    // Build the result object from the data pointer and output command block
    resultHandle = 0;
    if (dataPtr != 0) {
        FUN_005dbc10(dataPtr); // probably load/setup resource
        FUN_004dafd0(dataPtr); // maybe parse or initialize
        resultHandle = FUN_005e49d0(gAppearanceManager, &outputCmd[4]); // create object from command data
    }
    if (resultHandle == 0) goto LAB_00436cfe;

    // Apply global appearance to the new object
    FUN_005e67c0(resultHandle, gDefaultAppearance);

    // Read a command at offset +0x10 of current (type 3 or 4) and set float parameter
    pCmd = (int *)(*(int *)(this + 0x0C) + 0x10);
    if (((pCmd < *(int **)(this + 0x08)) && (pCmd != (int *)0x0)) &&
        ((*pCmd == 3 || (*pCmd == 4 && (FUN_00636850(&outputCmd[4]) != 0))))) {
        float floatVal = (float)FUN_006259b0(this, 3);
        FUN_005e6750(resultHandle, floatVal); // set some parameter (e.g., scale)
    }

    // Read a command at offset +0x20 (type 7 or 2) and set a resource reference
    int currentCmdRead = *(int *)(this + 0x0C);
    pCmd = (int *)(currentCmdRead + 0x20);
    if (((pCmd < *(int **)(this + 0x08)) && (pCmd != (int *)0x0)) &&
        ((*pCmd == 7 || (*pCmd == 2))) &&
        ((pCmd < *(int **)(this + 0x08) && (pCmd != (int *)0x0)))) {
        int resourceData;
        if (*pCmd == 2) {
            resourceData = *(int *)(currentCmdRead + 0x24);
        } else {
            if (*pCmd != 7) goto LAB_00436cb0;
            resourceData = *(int *)(currentCmdRead + 0x24) + 0x10;
        }
        if (resourceData != 0) {
            FUN_005e6580(resultHandle, resourceData); // attach resource to object
        }
    }

LAB_00436cb0:
    // Read a command at offset +0x08 (type 3 or 4) and set another float
    pCmd = (int *)(*(int *)(this + 0x0C) + 8);
    if (((pCmd < *(int **)(this + 0x08)) && (pCmd != (int *)0x0)) &&
        ((*pCmd == 3 || (*pCmd == 4 && (FUN_00636850(&outputCmd[4]) != 0))))) {
        float floatVal = (float)FUN_006259b0(this, 2);
        FUN_005e6700(resultHandle, floatVal); // set another parameter (e.g., rotation)
    }

LAB_00436cfe:
    // Write output command (type 2) and advance write pointer
    int *pCmdWrite = *(int **)(this + 0x08);
    pCmdWrite[0] = 2; // command type: result
    pCmdWrite[1] = resultHandle;
    *(int *)(this + 0x08) = (int)(pCmdWrite + 2); // advance by 8 bytes

    return 1;
}