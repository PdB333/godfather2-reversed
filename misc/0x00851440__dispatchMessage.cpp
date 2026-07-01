// FUNC_NAME: dispatchMessage
void dispatchMessage(uint arg0, uint arg1, uint arg2, uint arg3)
{
    uint sequenceId;
    char packetBuffer[44]; // 44-byte packet header buffer

    // FUN_00471610 - generates a unique sequence or timestamp for the message
    sequenceId = generateSequenceId();

    // FUN_00850be0 - serializes the message payload (from arg2) with the sequence into the buffer
    serializeMessageHeader(arg2, sequenceId, packetBuffer);

    // FUN_00850d00 - sends the constructed packet to the target (arg0, arg1) with extra arg3
    sendPacket(arg0, arg1, packetBuffer, arg3);
    return;
}