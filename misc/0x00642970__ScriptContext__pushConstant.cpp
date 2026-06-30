// FUNC_NAME: ScriptContext::pushConstant
int __thiscall ScriptContext::pushConstant(ScriptContext* thisPtr, void* valuePtr) // valuePtr is param_2, in_EAX is the value's type info? Actually in_EAX may be this of value or extra param. We'll assume valuePtr is a pointer to 8-byte value, and the actual value type is encoded in first int of that pointer? But code uses *in_EAX for type. So better to keep as two params: type/value. Since decompiler shows param_2 as undefined4*, we'll treat as a constant descriptor.
{
    int* contextData = thisPtr->data; // *param_1 => pointer to internal block
    int* constantValue; // piVar2
    int constantIndex;
    int type = *(int*)valuePtr; // first field of value descriptor
    float floatValue;

    // Determine constant type and allocate appropriate representation
    if (type == 3) // e.g., float constant
    {
        // Cast to float and check if unchanged (identity check)
        float f = *(float*)((int*)valuePtr + 1);
        if ((float)(int)f == f) // if integer representation equals float, treat as integer? Not sure
        {
            constantValue = (int*)function_getIntegerConstant(); // FUN_00637f10
            goto LABEL_ASSIGN;
        }
    }
    else if (type == 4) // e.g., integer constant
    {
        constantValue = (int*)function_getFloatConstant(); // FUN_00637f90
        goto LABEL_ASSIGN;
    }
    // default: use generic constant allocator
    constantValue = (int*)function_getDefaultConstant(); // FUN_00637ea0

LABEL_ASSIGN:
    // If the constant is a float type (3) we return its float value as int? Actually it returns the index into some table? Hmm.
    if (*constantValue == 3) // type check on returned constant
    {
        return (int)(*(float*)(constantValue + 1)); // return float as int? Possibly return the constant's index?
    }

    // Add constant to the local constant table
    int* tableBuffer = *(int**)(contextData + 2); // +0x08: pointer to constant data buffer
    int capacity = *(int*)(contextData + 10); // +0x28: capacity of table
    if (capacity < thisPtr->constantCount + 1) // check if need to expand
    {
        // Resize constant table
        int newBuffer = function_resizeTable(thisPtr->someId1, tableBuffer, &capacity, 8, "constant table overflow"); // FUN_00627930
        *(int**)(contextData + 2) = (int*)newBuffer; // update buffer pointer
    }
    // Write the constant value (8 bytes) into the table
    int* dest = (int*)(*(int*)(contextData + 2) + thisPtr->constantCount * 8);
    dest[0] = ((int*)valuePtr)[0]; // copy first 4 bytes
    dest[1] = ((int*)valuePtr)[1]; // copy next 4 bytes

    // Update the VM stack/register with the constant index (type 3 = constant table reference?)
    int* reg = (int*)function_writeRegister(thisPtr->someId4, thisPtr->someId1); // FUN_00638020
    reg[0] = 3; // type: constant reference
    reg[1] = (float)thisPtr->constantCount; // store index as float

    int result = thisPtr->constantCount;
    thisPtr->constantCount++;
    return result;
}