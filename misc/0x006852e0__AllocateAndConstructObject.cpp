// FUNC_NAME: AllocateAndConstructObject
undefined4 AllocateAndConstructObject(undefined4 thisArg, undefined4 param)
{
    int allocResult;
    undefined4 retVal;
    undefined4 allocDesc[3];
    
    allocDesc[0] = 2;          // Allocation type (heap)
    allocDesc[1] = 0x10;       // Alignment
    allocDesc[2] = 0;          // Flags
    allocResult = FUN_0043b980(0xb0, allocDesc, param); // Allocate 176 bytes
    if (allocResult != 0) {
        retVal = FUN_006b75c0(thisArg); // Call constructor/initializer on allocated memory
        return retVal;
    }
    return 0;
}