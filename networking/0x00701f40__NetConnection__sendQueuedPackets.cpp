// FUNC_NAME: NetConnection::sendQueuedPackets
void __fastcall NetConnection::sendQueuedPackets(int thisPtr)
{
    char gameActive;
    int iVar3;
    uint uVar4;
    uint uVar5;
    uint uVar6;

    gameActive = isGameActive();
    if ((gameActive != '\0') && (*(int *)(thisPtr + 0x2d0) != 0)) {
        iVar3 = getSendAvailableSize(*(undefined4 *)(thisPtr + 0x334));
        if (iVar3 + *(int *)(thisPtr + 0x328) != 0) {
            uVar4 = getSendAvailableSize(*(undefined4 *)(thisPtr + 0x334));
            uVar5 = *(uint *)(thisPtr + 0x32c);   // Send window size (e.g., 32 packets)
            uVar6 = uVar5;
            if (uVar4 <= uVar5) {
                uVar6 = uVar4;
            }
            uVar5 = uVar5 - *(int *)(thisPtr + 0x328); // Remaining window capacity
            if (uVar5 <= uVar6) {
                uVar6 = uVar5;
            }
            if ((*(uint *)(thisPtr + 0x2d8) >> 5 & 1) == 0) { // Check if send throttled (bit5)
                sendDataChunk(*(undefined4 *)(thisPtr + 0x334), uVar6);
            }
            // Call a virtual method (e.g., onSendProgress) with constant 0x20
            (*(void (__fastcall **)(int, uint))(*(int *)(thisPtr + 0x58) + 0x28))(0x20);
            *(int *)(thisPtr + 0x328) = *(int *)(thisPtr + 0x328) + uVar6;
            if (*(int **)(thisPtr + 0x2d4) != (int *)0x0) {
                // Call completion callback's virtual function at offset 4 (e.g., onComplete)
                (**(code **)(**(int **)(thisPtr + 0x2d4) + 4))();
                return;
            }
        }
    }
    return;
}