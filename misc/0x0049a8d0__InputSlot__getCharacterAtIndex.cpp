// FUNC_NAME: InputSlot::getCharacterAtIndex
// Address: 0x0049a8d0
// Returns the 0-based index-th non-zero, non-0xFF byte from the 4-byte slot data field at offset 0.
// The index is passed in ESI. If not enough valid bytes, returns '\0'.

class InputSlot {
public:
    // +0x00: 4-byte slot identifier/data (e.g., packed controller ID)
    int m_slotData;

    char getCharacterAtIndex(int index) {
        int rawData = m_slotData;
        int validCount = -1; // count of valid bytes seen before current offset

        for (int offset = 0; offset < 4; offset++) {
            char byteVal = *((char*)&rawData + offset);
            // skip null (0x00) and invalid (-1 / 0xFF) bytes
            if (byteVal != '\0' && byteVal != (char)0xFF) {
                validCount++;
                if (validCount == index) {
                    return byteVal;
                }
            }
        }
        return '\0';
    }
};