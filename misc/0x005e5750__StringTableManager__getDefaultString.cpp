// FUNC_NAME: StringTableManager::getDefaultString
uint StringTableManager::getDefaultString(void)
{
    uint result;
    undefined4 *nodePtr;
    uint keyByte;
    uint keyInt;

    result = gStringTableManager; // DAT_01223514
    keyByte = 0;
    keyInt = 0;
    nodePtr = (undefined4 *)lookupNode(gStringTableManager, &keyByte); // FUN_005f0600
    if (nodePtr != (undefined4 *)0x0) {
        result = extractValue(result, *nodePtr); // FUN_005f0680
        return result;
    }
    return 0;
}