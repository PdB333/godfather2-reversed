// FUNC_NAME: NetworkReliabilityLayer::initialize
void __thiscall NetworkReliabilityLayer::initialize(NetworkReliabilityLayer* this) {
    // +0x193: outgoing buffer (256 bytes) - cleared
    _memset(reinterpret_cast<char*>(this) + 0x64C, 0, 0x100);
    // +0x1d3: incoming buffer (256 bytes) - cleared
    _memset(reinterpret_cast<char*>(this) + 0x74C, 0, 0x100);

    // Global constant (likely initial sequence number or timeout)
    uint32_t baseValue = DAT_00e2b1a4;

    // Initialize sequence/ack fields at the beginning
    this->field_00 = 0;          // +0x00: sendSequence (or similar)
    this->field_04 = 0;          // +0x04: recvSequence
    this->field_08 = baseValue;  // +0x08: sendAck
    this->field_0C = baseValue;  // +0x0C: recvAck
    this->field_10 = baseValue;  // +0x10: maybe sendWindowStart
    this->field_14 = baseValue;  // +0x14: maybe recvWindowStart
    this->field_18 = 0;          // +0x18: flags or mode

    // +0x22: large packet buffer (0x5c0 bytes) - cleared
    _memset(reinterpret_cast<char*>(this) + 0x88, 0, 0x5C0);

    // +0x192: some counter or state
    this->field_0x192 = 0;

    // +0x213 and +0x214: reliability parameters
    if (DAT_012234b4 != 0) {
        // Global pointer exists, fetch a value from it
        uint32_t extraParam = *(uint32_t*)(DAT_012234b4 + 4);
        this->field_0x214 = 0x200000;          // Max reliable packet size? window size?
        this->field_0x213 = extraParam;        // Some threshold or ID
    } else {
        this->field_0x214 = 0x200000;
        this->field_0x213 = 0;
    }
}