// FUNC_NAME: NetSession::validatePacketHeader
// Function address: 0x00578770
// Role: Validates a packet header's sequence number or version against internal state.

void __thiscall validatePacketHeader(int *configData)
{
    int localSeq = *(int *)((int)this + 0x18); // +0x18: local sequence number / version
    int remoteVal;

    // Check flag at configData+0xB (bit 0x20) and minimum value at configData[0]
    if ((*(byte *)(configData + 0xB) & 0x20) == 0 || *configData < 2) {
        remoteVal = configData[5]; // +0x14: use first remote value
    } else {
        remoteVal = configData[7]; // +0x1C: use second remote value
    }

    FUN_00579870(); // likely a global update or logging function
    bool isMatching = (localSeq == remoteVal);
    FUN_00579450(this, tempBuffer); // param1=this, param2=20-byte scratch buffer
}