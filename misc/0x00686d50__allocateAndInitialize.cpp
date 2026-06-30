// FUNC_NAME: allocateAndInitialize
undefined4 __thiscall allocateAndInitialize(undefined4 param_1, undefined4 param_2)
{
    int allocatedPtr;
    undefined4 result;
    struct {
        int field_0;  // flags or type
        int field_4;  // alignment?
        int field_8;  // additional flags
    } allocParams;

    allocParams.field_0 = 2;
    allocParams.field_4 = 0x10;  // alignment to 16 bytes
    allocParams.field_8 = 0;

    allocatedPtr = allocateMemory(0x170, &allocParams, param_2);  // size 368 bytes
    if (allocatedPtr != 0) {
        result = initializeObject(param_1);
        return result;
    }
    return 0;
}