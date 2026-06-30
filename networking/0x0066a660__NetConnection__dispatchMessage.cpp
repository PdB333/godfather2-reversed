// FUNC_NAME: NetConnection::dispatchMessage
void NetConnection::dispatchMessage(int* messageTypePtr, int packetBuffer)
{
    int messageType = *messageTypePtr;
    if (messageType > 399) {
        // High range (>399): likely system or control packets
        FUN_0066b250(messageTypePtr, packetBuffer);
        *(int*)(packetBuffer + 8) = 0; // Clear field at +0x08
        return;
    }
    if (messageType > 0x7e) {
        // Mid range (127-399): e.g., game state updates
        FUN_006683b0(messageTypePtr, packetBuffer);
        *(int*)(packetBuffer + 8) = 0;
        return;
    }
    // Low range: condition effectively messageType < 0x80 (due to multiplication check)
    if ((messageType * 2 + 1 < 0x200) && (messageType < 0x80)) {
        FUN_00665500(messageTypePtr, packetBuffer);
        *(int*)(packetBuffer + 8) = 0;
        return;
    }
    // Fallback (should not be reached based on above ranges)
    FUN_0066c6d0(messageTypePtr, packetBuffer);
    *(int*)(packetBuffer + 8) = 0;
}