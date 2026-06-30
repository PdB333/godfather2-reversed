// FUNC_NAME: String::rfind
int __thiscall String::rfind(int* this, char searchChar, uint startIndex) {
    int size = this[1]; // +0x04: size/length of string
    int result = 0xFFFFFFFF; // default return value (index not found)

    if (size != 0) {
        if (startIndex == 0xFFFFFFFF) {
            startIndex = size - 1; // search from the end
        }
        // Validate startIndex is within bounds
        if (startIndex < (uint)size && (int)startIndex >= 0) {
            int i = (int)startIndex;
            while (*(char*)(*this + i) != searchChar) { // *this is the data pointer (+0x00)
                i--;
                if (i < 0) {
                    return 0xFFFFFFFF; // not found
                }
            }
            result = i; // found at index i
        }
    }
    return result;
}