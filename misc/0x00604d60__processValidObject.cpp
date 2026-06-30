// FUNC_NAME: processValidObject
void processValidObject(int param)
{
    int objectPtr = getObjectPointer(param);  // FUN_00604d20 - fetches object pointer from handle
    if (objectPtr != 0) {
        processObject(objectPtr);  // FUN_004d4300 - performs processing on valid object
    }
}