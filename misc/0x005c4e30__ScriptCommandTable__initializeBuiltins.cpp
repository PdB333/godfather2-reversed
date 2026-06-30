// FUNC_NAME: ScriptCommandTable::initializeBuiltins
void ScriptCommandTable::initializeBuiltins(void)
{
    int *stream; // Pointer to stream writer position, stored at gBuffer+0x14
    uint *streamUint; // Same as stream, but used for alignment operations

    // gBuffer is a global data buffer (DAT_01206880)
    stream = *(int **)(gBuffer + 0x14);
    // Write command entry: pointer to command name string (PTR_LAB_01126bb8), then opcode 0xF (15)
    *(void **)(*stream) = &PTR_LAB_01126bb8;
    *stream += 4;
    *(int *)(*stream) = 0xF;
    *stream += 4;

    // Write another command: pointer to next name, then opcode 0x0
    stream = *(int **)(gBuffer + 0x14);
    *(void **)(*stream) = &PTR_LAB_01126b40;
    *stream += 4;
    *(char *)(*stream) = 0;
    // Align stream to 4-byte boundary (round up to next multiple of 4)
    *stream = (*stream + 4) & 0xFFFFFFFC;

    // Write next command: pointer, then opcode 1 (with alignment)
    stream = *(int **)(gBuffer + 0x14);
    *(void **)(*stream) = &PTR_LAB_01126b68;
    *stream += 4;
    // Align and write integer 1
    *(int **)(gBuffer + 0x14) = &PTR_LAB_01126b68; // redundant, actually using stream variable
    streamUint = (uint *)((*stream + 3) & 0xFFFFFFFC);
    *(int **)(gBuffer + 0x14) = (int *)streamUint;
    *streamUint = 1;
    *(int **)(gBuffer + 0x14) += 4;

    // Write next command: pointer, then opcode 1 (byte, aligned)
    stream = *(int **)(gBuffer + 0x14);
    *(void **)(*stream) = &PTR_LAB_01126af0;
    *stream += 4;
    *(char *)(*stream) = 1;
    *stream = (*stream + 4) & 0xFFFFFFFC;

    // Write next command: pointer, then opcode 1 again
    stream = *(int **)(gBuffer + 0x14);
    *(void **)(*stream) = &PTR_LAB_01126cd0;
    *stream += 4;
    *(char *)(*stream) = 1;
    *stream = (*stream + 4) & 0xFFFFFFFC;

    // Write next command: pointer, then opcode 5 (as a 4-byte integer)
    stream = *(int **)(gBuffer + 0x14);
    *(void **)(*stream) = &PTR_LAB_01126b90;
    *stream += 4;
    streamUint = (uint *)(*stream);
    *(char *)(*stream) = 0;
    // Align and write 5
    *stream = (*stream + 4) & 0xFFFFFFFC;
    *(int *)(*stream) = 5;
    *stream += 4;
    *(char *)(*stream) = 0;
    *stream = (*stream + 4) & 0xFFFFFFFC;

    // Write next command: pointer, then opcode 3
    stream = *(int **)(gBuffer + 0x14);
    *(void **)(*stream) = &PTR_LAB_01126ca8;
    *stream += 4;
    // Align and write 3
    *(int **)(gBuffer + 0x14) = (int *)((*stream + 3) & 0xFFFFFFFC);
    **(int **)(gBuffer + 0x14) = 3;
    *(int **)(gBuffer + 0x14) += 4;

    // Write two more pointers (with no opcode? Or just pointers to additional data)
    stream = *(int **)(gBuffer + 0x14);
    *(void **)(*stream) = &PTR_LAB_01126dc0;
    *stream += 4;
    stream = *(int **)(gBuffer + 0x14);
    *(void **)(*stream) = &PTR_LAB_01126de8;
    *stream += 4;

    return;
}