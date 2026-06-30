// FUNC_NAME: NodeSerializer::deserializeNode
byte __thiscall NodeSerializer::deserializeNode(void* context, char* nodeBuffer, int* array, undefined4 param_4)
{
    char opcode;
    short* shortArray;
    int* arrayTemp;
    byte result = 0;
    int childCount;
    int index;
    float valueFloat;
    char* valuePtr;
    int intValue;

    // Initial byte is the opcode
    opcode = *nodeBuffer;

    if (opcode == '\t') // 0x09: write zero at given index
    {
        // Data at offset 4 is a pointer to an array of indices (int*)
        int* indexArray = *(int**)(nodeBuffer + 4);
        if (indexArray == 0 || (char)param_4 == '\0')
        {
            index = indexArray[1]; // second index
            if ((uint)array[1] <= (uint)index)
            {
                // Out of bounds – call error handler (likely asserts)
                char* dummy = 0;
                FUN_00591c00(&dummy);
            }
            // Write zero at that index in the output array
            *(undefined4*)(array[0] + index * 4) = 0;
            result = 1;
            goto LAB_00591a72;
        }
        else
        {
            // Push a value from global data (likely a string)
            int* temp = (int*)FUN_0058abc0(array);
            *temp = (int)DAT_00e2b04c;
        }
    }
    else if (opcode == '\x03') // 0x03: write float from function conversion
    {
        // Data at offset 4 is a pointer to an array of shorts
        shortArray = *(short**)(nodeBuffer + 4);
        index = (uint)*shortArray; // first short as index
        if ((uint)array[1] <= index)
        {
            char* dummy = 0;
            FUN_00591c00(&dummy);
        }
        // Call conversion function (reads node and returns int)
        intValue = FUN_0058b2e0(context, nodeBuffer, array);
        *(float*)(array[0] + index * 4) = (float)intValue; // store as float
        // Use second short as another index
        index = (uint)shortArray[1];
        if ((uint)array[1] <= index)
        {
            char* dummy = 0;
            FUN_00591c00(&dummy);
        }
        // Write a global string pointer at that index
        *(char**)(array[0] + index * 4) = (char*)DAT_00e2eff4;
        goto LAB_00591a72;
    }
    else if (opcode == '\x06') // 0x06: push computed value
    {
        intValue = FUN_0058c0b0(context, nodeBuffer, array);
        // Convert int to float and store as pointer? The decompiler shows this cast.
        // Likely FUN_0058c0b0 returns a float in eax, but Ghidra sees int.
        valuePtr = (char*)(float)intValue; // store bits as a pointer
        int* temp = (int*)FUN_0058abc0(array);
        *temp = (int)valuePtr;
        int* temp2 = (int*)FUN_0058abc0(array);
        *temp2 = (int)DAT_00e2eff4; // another global
        // then fall through to assignment? Actually after this, the code does *puVar5 = pcVar10, but that's already set above? We need to re-check flow.
    }
    else if (opcode == '\x14') // 0x14: push linear interpolation result
    {
        FUN_00593700(); // no arguments? Probably initializes something (like a timer)
        // in_XMM0_Da is the return from FUN_00593700? Actually in_XMM0_Da is a global?
        // The decompiler thinks it's a parameter, but it's probably a global float.
        // Compute: in_XMM0_Da * *(float *)(extraout_EDX + 0xc) + *(float *)(extraout_EDX + 8)
        // This is a linear blend between two values.
        valueFloat = g_globalFloat * *(float*)(g_edxValue + 0xc) + *(float*)(g_edxValue + 8);
        int* temp = (int*)FUN_0058abc0(array);
        *temp = *(int*)&valueFloat; // store float as int (bits)
        // pcVar10 set to the same value
        // then fall through
    }
    else
    {
        goto LAB_00591a72; // unknown opcode: skip
    }

    // For opcodes 0x09 (else branch), 0x06, and 0x14, the code sets *puVar5 = pcVar10, but the assignment is already done inside each branch? Actually the decompiler shows that after the if-else, there is a *puVar5 = pcVar10, but puVar5 is set only in those branches. So we incorporate that.

LAB_00591a72:
    childCount = (int)nodeBuffer[1]; // number of child nodes (stored as byte)
    if (childCount > 0)
    {
        char* childPtr = nodeBuffer + 0xc; // children start after 12-byte header
        do
        {
            result |= deserializeNode(context, *(char**)(childPtr), array, param_4);
            childPtr += 4;
            childCount--;
        } while (childCount != 0);
    }
    return result;
}