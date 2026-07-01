// FUNC_NAME: isValidTypeId
bool isValidTypeId(int typeId)
{
    // Check if typeId is non-zero and matches one of the three known type IDs
    // Known type IDs: 0x4ecfbe13, 0x332d5a20, 0x26fbf813 (latter is -0xd9047ed)
    if (typeId == 0)
        return false;
    if (typeId == 0x4ecfbe13 || typeId == 0x332d5a20 || typeId == 0x26fbf813)
        return true;
    return false;
}