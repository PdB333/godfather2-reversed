// FUNC_NAME: ShaderConstantManager::addConstantData
// Address: 0x0063e460
// This function adds a constant entry to the shader constant table, handling overflow and component data.

void __thiscall ShaderConstantManager::addConstantData(void* thisPtr, int* constantDesc)
{
    // Internal constant table data structure at +0x1c
    int* tableData = *(int**)((int)thisPtr + 0x1c);
    int* internalTable = (int*)*tableData; // Points to ConstantTableInternal

    // Check if constant table capacity is insufficient
    if (internalTable[0x34 / 4] < tableData[0x2c / 4] + 1) // capacity vs count+1
    {
        // Reallocate: allocator at +0x20, old pointer at internalTable+0x10, capacity pointer at internalTable+0x34
        int* newBuffer = (int*)FUN_00627930(*(void**)((int)thisPtr + 0x20),
                                            *(void**)(internalTable + 0x10 / 4),
                                            (int*)(internalTable + 0x34 / 4),
                                            4, "constant table overflow");
        internalTable[0x10 / 4] = (int)newBuffer;
    }

    // Store the constant value (first int of constantDesc)
    int* dataArray = (int*)internalTable[0x10 / 4];
    int currentIndex = tableData[0x2c / 4];
    int* dataPtr = dataArray + currentIndex;
    *dataPtr = *constantDesc;
    tableData[0x2c / 4] = currentIndex + 1; // Increment count

    // Encode constant index and opcode (0x22) and send to command stream
    int packedCmd = (currentIndex * 0x40) | 0x22;
    int* cmdBuffer = (int*)tableData[0x0c / 4]; // command buffer pointer
    int cmdResult = FUN_006438e0(packedCmd, *(void**)(cmdBuffer + 8 / 4)); // append command

    // Write output results (assumed to be in EAX register, represented as local array)
    int* output = (int*)__builtin_ia32_read_eflags(); // Placeholder - in decompiler it's in_EAX
    output[0] = 10; // command type?
    output[1] = cmdResult;
    output[3] = -1;
    output[4] = -1;

    // Process component data if present (count at offset 0x44 of constantDesc)
    int componentCount = *(char*)(*constantDesc + 0x44);
    if (componentCount != 0)
    {
        int* componentIter = constantDesc + 0xf; // components start at offset 0x3C
        for (int i = 0; i < componentCount; i++)
        {
            // Encode component: if previous type != 5 add flag 4, shift value left 0xf
            int prevType = componentIter[-1];
            int value = componentIter[0];
            int flags = (prevType != 5) ? 4 : 0;
            int componentCmd = flags | (value << 0xf);
            FUN_006438e0(componentCmd, *(void**)(cmdBuffer + 8 / 4));
            componentIter += 5; // each component is 20 bytes (5 ints)
        }
    }
}