// FUNC_NAME: EntityFactory::createGameObject

bool EntityFactory::createGameObject(void* thisPtr, int dataSource)
{
    int sourceManager;
    int newObject;
    int tmp;
    int* handlePtr;
    undefined4* dwordPtr;
    undefined8* resultStruct;
    undefined4 localVal;
    int stackInt;
    undefined8 result2;
    undefined4 result3;
    int outBuffer[3];               // likely GUID or resource identifier
    code* funcPtr;                  // uninitialized in decompilation (bug?)

    sourceManager = dataSource;
    if ((*(int*)((char*)thisPtr + 8) != 0) && (*(int*)((char*)thisPtr + 4) != 0)) {
        // Allocate memory for new object (size 0x2c0 = 704 bytes)
        tmp = allocateObjectMemory(0x2c0);
        if (tmp == 0) {
            newObject = 0;
        } else {
            newObject = constructNewObject();   // likely passes tmp as this? Decompiler shows no arg
        }
        // Initialize data source reading
        initSource(dataSource);
        extractIdentifier(outBuffer);
        if (outBuffer[0] != 0) {
            (*funcPtr)(outBuffer[0]);       // suspicious - funcPtr uninitialized
        }
        // Read fields from data source at offsets 0x20, 0x40, 0x60
        *(int*)(newObject + 0x2b0) = readDwordFromOffset(dataSource + 0x20);
        *(int*)(newObject + 0x2b4) = readDwordFromOffset(dataSource + 0x40);
        *(int*)(newObject + 0x2b8) = *(int*)(dataSource + 0x60);

        sourceManager = *(int*)((char*)thisPtr + 0xc);
        if (sourceManager != 0) {
            stackInt = *(int*)(sourceManager + 0x1c);
            handlePtr = (int*)lookupObjectByPointer(&dataSource);  // &dataSource may be wrong
            if ((*handlePtr == 0) || (*handlePtr != sourceManager)) {
                assertionFailure();
            }
            if (handlePtr[1] != stackInt) {
                dwordPtr = (undefined4*)getObjectHandle(&dataSource);
                *(int*)(newObject + 0x29c) = *dwordPtr;
            }
        }
        // Read the primary handle from dataSource start
        localVal = readDwordFromOffset(dataSource);
        stackInt = newObject;
        resultStruct = (undefined8*)registerObjectWithManager(*(int*)((char*)thisPtr + 8), outBuffer, &localVal);
        result2 = *resultStruct;
        result3 = *(undefined4*)(resultStruct + 1);
        if ((char)result3 != '\0') {
            finalizeCreation(dataSource, localVal);
            return true;
        }
        cleanupAfterFailure();
        freeMemory(newObject);
    }
    return false;
}