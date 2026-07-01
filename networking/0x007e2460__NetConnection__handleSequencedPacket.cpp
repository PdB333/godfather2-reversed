// FUNC_NAME: NetConnection::handleSequencedPacket
void __thiscall NetConnection::handleSequencedPacket(int thisPtr, int packetId)
{
    int* pExpectedNext = (int*)(thisPtr + 0x84); // +0x84: pointer to next expected sequence number or buffer
    int expectedSeq;
    if (*pExpectedNext == 0) {
        expectedSeq = 0;
    } else {
        expectedSeq = *pExpectedNext - 0x48; // subtract packet header size (72 bytes)
    }
    if (packetId == expectedSeq) {
        if (*pExpectedNext != 0) {
            FUN_004daf90(pExpectedNext); // likely frees or resets the expected packet buffer
            *pExpectedNext = 0;
        }
        FUN_00939eb0(); // likely sends an acknowledgement or processes the next packet in the window
    }
}