// FUNC_NAME: SerializationBuffer::writeParameterEntries
void SerializationBuffer::writeParameterEntries(void)
{
    uint *pWritePos;
    int iVar1;
    int *pAligned;
    undefined4 *puVar4;

    iVar1 = g_pStreamBuffer;
    // Write pointer to string "PTR_LAB_01126bb8" (likely parameter name)
    **(undefined4 **)(g_pStreamBuffer + 0x14) = &PTR_LAB_01126bb8;
    *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4;
    // Write value 0xf (15)
    **(undefined4 **)(iVar1 + 0x14) = 0xf;
    *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4;

    iVar1 = g_pStreamBuffer;
    // Write another parameter name
    **(undefined4 **)(g_pStreamBuffer + 0x14) = &PTR_LAB_01126be0;
    *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4;
    // Align to 4-byte boundary, write 0 (default value?)
    pAligned = (int *)(iVar1 + 0x14);
    puVar4 = (undefined4 *)(*(int *)(iVar1 + 0x14) + 3U & 0xfffffffc);
    *pAligned = (int)puVar4;
    *puVar4 = 0;
    *pAligned = *pAligned + 4;

    iVar1 = g_pStreamBuffer;
    // Write parameter name
    **(undefined4 **)(g_pStreamBuffer + 0x14) = &PTR_LAB_01126b68;
    *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4;
    // Align, write 1
    pAligned = (int *)(iVar1 + 0x14);
    puVar4 = (undefined4 *)(*(int *)(iVar1 + 0x14) + 3U & 0xfffffffc);
    *pAligned = (int)puVar4;
    *puVar4 = 1;
    *pAligned = *pAligned + 4;

    iVar1 = g_pStreamBuffer;
    // Write parameter name
    **(undefined4 **)(g_pStreamBuffer + 0x14) = &PTR_LAB_01126cd0;
    *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4;
    // Write byte 0, then align
    **(undefined1 **)(iVar1 + 0x14) = 0;
    *(uint *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4U & 0xfffffffc;

    iVar1 = g_pStreamBuffer;
    // Write parameter name
    **(undefined4 **)(g_pStreamBuffer + 0x14) = &PTR_LAB_01126af0;
    *(int *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4;
    // Write byte 0, align
    **(undefined1 **)(iVar1 + 0x14) = 0;
    *(uint *)(iVar1 + 0x14) = *(int *)(iVar1 + 0x14) + 4U & 0xfffffffc;

    pWritePos = (uint *)(g_pStreamBuffer + 0x14);
    // Write parameter name
    **(undefined4 **)(g_pStreamBuffer + 0x14) = &PTR_LAB_01126b90;
    *pWritePos = *pWritePos + 4;
    // Write byte 0, align, then write 5, then byte 0, align
    *(undefined1 *)*pWritePos = 0;
    puVar4 = (undefined4 *)(*pWritePos + 4 & 0xfffffffc);
    *pWritePos = (uint)puVar4;
    *puVar4 = 5;
    *pWritePos = *pWritePos + 4;
    *(undefined1 *)*pWritePos = 0;
    *pWritePos = *pWritePos + 4 & 0xfffffffc;

    return;
}