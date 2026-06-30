// FUNC_NAME: StreamBuffer::write4Dwords
void StreamBuffer::write4Dwords(int param_1, undefined4 *param_2)
{
    // TLS access pattern: FS:[0x2C] -> TLS array, first slot -> global data, offset 8 -> buffer base
    // Then add 0x40 + this->field_0x10 (offset into buffer)
    undefined4 *puVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    int unaff_FS_OFFSET;

    uVar2 = param_2[1];
    uVar3 = param_2[2];
    uVar4 = param_2[3];
    puVar1 = (undefined4 *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x40 + *(int *)(param_1 + 0x10));
    *puVar1 = *param_2;
    puVar1[1] = uVar2;
    puVar1[2] = uVar3;
    puVar1[3] = uVar4;
    return;
}