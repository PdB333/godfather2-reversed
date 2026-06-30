// FUNC_NAME: PacketHashState::updateHash
void __thiscall PacketHashState::updateHash(uint inputValue, uint* outputBuffer)
{
    uint hash0 = this->hash0; // +0x00
    uint hash1 = this->hash1; // +0x04
    uint hash2 = this->hash2; // +0x08
    uint hash3 = this->hash3; // +0x0C

    uint byteVal = inputValue & 0xFF;
    uint acc0 = hash0 * 0x1003F + byteVal;
    uint acc1 = hash1 * 0x1003F + byteVal;

    // Process remaining bytes of inputValue (assumes 3-byte value or length < 0x1000000)
    uint shifted = inputValue;
    if (byteVal < shifted) {
        do {
            shifted >>= 8;
            byteVal = shifted & 0xFF;
            acc0 = acc0 * 0x1003F + byteVal;
            acc1 = acc1 * 0x1003F + byteVal;
        } while (byteVal < shifted);
    }

    // Combine and store results
    outputBuffer[0] = (hash0 ^ acc0) & 0xFFFFFF ^ hash0; // Low 24-bit mixing
    outputBuffer[1] = acc1;
    outputBuffer[2] = hash2; // Copied unchanged
    outputBuffer[3] = hash3;
}