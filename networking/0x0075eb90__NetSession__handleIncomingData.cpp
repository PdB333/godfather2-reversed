// FUNC_NAME: NetSession::handleIncomingData
void __thiscall NetSession::handleIncomingData(void *this, undefined8 *packetData)
{
    char validationResult;

    // Copy packet header data: first 8 bytes into offset +0x60 (likely a sequence ID or timestamp)
    // Next 4 bytes (at packetData+8) into offset +0x68 (maybe a checksum or sub-type)
    *(undefined8 *)((int)this + 0x60) = *packetData;
    *(undefined4 *)((int)this + 0x68) = *(undefined4 *)(packetData + 1); // +8 bytes offset

    // Validate packet using offset +0x58 (some context/state) and the raw packet data
    validationResult = FUN_009a77c0(*(undefined4 *)((int)this + 0x58), packetData);
    if (validationResult == '\0') {
        // Packet invalid – set flag 0x4000 in status flags at +0xA8
        *(uint *)((int)this + 0xa8) = *(uint *)((int)this + 0xa8) | 0x4000;
        return;
    }
    // Packet valid – set flag 0x8000
    *(uint *)((int)this + 0xa8) = *(uint *)((int)this + 0xa8) | 0x8000;
    return;
}