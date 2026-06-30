// FUNC_NAME: ObjectFactory::createObject
undefined4 ObjectFactory::createObject(undefined4 param1, undefined4 param2, undefined4 param3)
{
    int allocatedMem;
    undefined4 result;
    
    allocatedMem = FUN_009c8e50(0x48);
    if (allocatedMem != 0) {
        result = FUN_004b4d10(param3);
        return result;
    }
    return 0;
}