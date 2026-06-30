// FUNC_NAME: DataNode::readValue
// Address: 0x006a7fd0
// Reads a 32-bit value from a data node if its type field at offset 6 is 2.
// Returns a combined status/value where lower byte = 1 if read succeeded, high 24 bits from read value.
// Struct offsets: +0x00 header pointer, +0x04 data pointer

uint __thiscall DataNode::readValue(DataNode* this, uint32_t* outValue)
{
    // Implicit EAX input from caller (e.g., previous result)
    uint result = in_EAX & 0xffffff00;
    if (this->dataPtr != nullptr && this->header != nullptr && this->header[6] == '\x02') {
        uint32_t val = *this->dataPtr;        // Read the first dword from data pointer
        *outValue = val;
        // Build result: high 24 bits from val>>8, low byte = 1 (success indicator)
        result = (val >> 8) | 0x1;
    }
    return result;
}