// FUN_005dc510: ModelStreamLoader::loadModel
undefined4 __thiscall ModelStreamLoader::loadModel(int this, int stream) {
    int newObj;
    int parent;
    int parentField1C;
    int *pi;
    undefined4 *pui;
    undefined8 *pu8;
    undefined4 localVal;
    int localInt;
    undefined8 localData;
    undefined4 localFlag;
    int callbackContext[3];
    code *callbackFunc;

    if ((*(int *)(this + 8) != 0) && (*(int *)(this + 4) != 0)) {
        newObj = allocateMemory(0x2c0);
        if (newObj == 0) {
            newObj = 0;
        } else {
            newObj = MetaModelInstance::construct(); // calls FUN_005dcca0
        }
        streamBeginRead(stream);                 // FUN_004d3bc0
        streamSetCallback(callbackContext);      // FUN_004d3e20
        if (callbackContext[0] != 0) {
            (*callbackFunc)(callbackContext[0]); // callback invocation
        }
        // read three values from the stream at offsets 0x20, 0x40, 0x60
        *(undefined4 *)(newObj + 0x2b0) = readDword(stream + 0x20);
        *(int *)(newObj + 0x2b4) = readDword(stream + 0x40);
        *(undefined4 *)(newObj + 0x2b8) = *(undefined4 *)(stream + 0x60);

        parent = *(int *)(this + 0xc);
        if (parent != 0) {
            parentField1C = *(int *)(parent + 0x1c);
            pi = (int *)getModelReference(&stream); // FUN_005df150
            if ((*pi == 0) || (*pi != parent)) {
                assertFail();                    // FUN_00b97aea
            }
            if (pi[1] != parentField1C) {
                pui = (undefined4 *)getModelExtra(&stream); // FUN_005df050
                *(undefined4 *)(newObj + 0x29c) = *pui;
            }
        }
        // read the first value of the stream (offset 0)
        localVal = readDword(stream);            // FUN_004dafd0
        // stack preparation for readChildData
        undefined4 localStack = localVal;
        localInt = newObj;
        pu8 = (undefined8 *)readChildData(*(void **)(this + 8), callbackContext, &localStack); // FUN_005deb50
        localData = *pu8;
        localFlag = *(undefined4 *)(pu8 + 1);
        if ((char)localFlag != '\0') {
            finalizeInit(stream, localVal);      // FUN_005dbc10
            return 1;
        }
        cleanup();                               // FUN_005dcdc0
        deallocateMemory(newObj);                // FUN_009c8eb0
    }
    return 0;
}