// FUNC_NAME: TNLConnection::writePacketData
void __fastcall TNLConnection::writePacketData(undefined4 *param_1, undefined4 *param_2, undefined4 *param_3, undefined4 *param_4)
{
    undefined4 *puVar1;
    int iVar2;
    int unaff_ESI;
    
    // Write param_3 (likely sequence number) to current write position
    puVar1 = *(undefined4 **)(unaff_ESI + 8);
    *puVar1 = *param_3;
    puVar1[1] = param_3[1];
    
    // Write param_4 (likely ACK info) to current write position +8
    iVar2 = *(int *)(unaff_ESI + 8);
    *(undefined4 *)(iVar2 + 8) = *param_4;
    *(undefined4 *)(iVar2 + 0xc) = param_4[1];
    
    // Write param_2 (likely packet flags) to current write position +16
    iVar2 = *(int *)(unaff_ESI + 8);
    *(undefined4 *)(iVar2 + 0x10) = *param_2;
    *(undefined4 *)(iVar2 + 0x14) = param_2[1];
    
    // Write param_1 (likely packet data) to current write position +24
    iVar2 = *(int *)(unaff_ESI + 8);
    *(undefined4 *)(iVar2 + 0x18) = *param_1;
    *(undefined4 *)(iVar2 + 0x1c) = param_1[1];
    
    // Check if buffer is full (32 bytes = 0x20 bytes per packet slot)
    if (*(int *)(unaff_ESI + 0x18) - *(int *)(unaff_ESI + 8) < 0x21) {
        FUN_00635c70(); // flushBuffer
    }
    
    // Advance write position by one packet slot (32 bytes)
    *(int *)(unaff_ESI + 8) = *(int *)(unaff_ESI + 8) + 0x20;
    
    FUN_006362d0(); // updatePacketStats
    return;
}