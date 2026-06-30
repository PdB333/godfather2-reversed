// FUNC_NAME: BitStreamReader::unpack12Byte
bool BitStreamReader::unpack12Byte(uint32_t *outValue1, uint32_t *outValue2, uint32_t *outValue3, uint32_t *outValue4)
{
    // Structure assumed: this[0]=type (1=buffer, 2=stream), 
    // for type 1: this[3]=offset, this[4]=buffer size, this[5]=buffer pointer
    // for type 2: this[4]=read function pointer, this[7]=stream handle
    union {
        uint32_t raw[3];
        struct {
            uint32_t a;
            uint32_t b;
            uint32_t c;
        } fields;
    } temp;
    size_t bytesRead;

    if (this->type == 1) {
        // Direct byte buffer
        int32_t offset = this->bufferOffset;   // +0x0C
        size_t remaining = this->bufferSize - offset; // +0x10 size, +0x14 buffer ptr
        bytesRead = (remaining < 12) ? remaining : 12;
        memcpy(&temp, (void *)(this->bufferPtr + offset), bytesRead);
        this->bufferOffset = offset + bytesRead;
    } else if (this->type == 2) {
        // Stream via function pointer
        bytesRead = this->readFunc(this->streamHandle, &temp, 12);
    } else {
        return false;
    }

    if (bytesRead != 12) {
        return false;
    }

    // Decode third uint32 (temp.c) into two 16‑bit values
    uint32_t highWord = temp.c & 0xFFFF0000;
    uint32_t lowWord = temp.c & 0xFFFF;
    uint32_t decodedHigh;
    if (highWord == 0) {
        // Denormal/special case
        decodedHigh = (temp.c & 0xFFFF) << 8;
        lowWord = 0;
    } else {
        // Extract floating‑point components (custom half‑float decoding)
        decodedHigh = ((temp.c >> 14) & 0x3FF00) + 0x30000 | ((temp.c >> 16) & 0x3F);
        lowWord = temp.c & 0xFFFF;
    }

    // Assign outputs (note parameter order: 1=a, 2=b, 3=decodedHigh, 4=lowWord)
    if (outValue1 != nullptr) *outValue1 = temp.a;
    if (outValue2 != nullptr) *outValue2 = temp.b;
    if (outValue4 != nullptr) *outValue4 = lowWord;
    if (outValue3 != nullptr) *outValue3 = decodedHigh;

    return true;
}