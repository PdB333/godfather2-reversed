// FUNC_NAME: StringBuffer::parsePathTokens
// Address: 0x0062eff0
// Role: Parses a path string containing '?' marks, splitting into token elements.
// Uses an internal buffer of (type,value) pairs (8 bytes each). Type 4 indicates a string value.
// The '?' characters act as delimiters; each segment before a '?' is stored as a separate token.
// If the previous element wasn't type 4, it attempts conversion before parsing.

class StringBuffer {
public:
    void parsePathTokens() {
        // +0x08: pointer to current write position in buffer (array of 8-byte entries: type, value)
        int* currentEntry = reinterpret_cast<int*>(this->field_0x08);
        int* prevEntry = currentEntry - 2; // each entry is 2 ints (8 bytes)
        char* str = nullptr;

        // Determine if we have a string to parse from the previous element
        if (prevEntry == nullptr) {
            str = nullptr;
        } else if (*prevEntry == 4) {
            // Type 4: value at prevEntry+1 is a pointer to an object with string at +0x10
            str = reinterpret_cast<char*>(*(prevEntry + 1) + 0x10);
        } else {
            // Attempt to convert non-string element to string
            if (FUN_00633990()) {  // conversion succeeded?
                str = reinterpret_cast<char*>(*(prevEntry + 1) + 0x10);
            } else {
                str = nullptr;
            }
            // Check for overflow in secondary buffer (at +0x10)
            if (*(reinterpret_cast<uint32_t*>(this->field_0x10) + 0x20) <=
                *(reinterpret_cast<uint32_t*>(this->field_0x10) + 0x24)) {
                FUN_00627360();  // handle overflow
            }
        }

        // Find first '?' in the string
        char* found = _strchr(str, '?');
        while (true) {
            if (found == nullptr) {
                // No more delimiters; finalize and return
                FUN_00625ca0();  // finalize list?
                FUN_00626460();  // clean up?
                return;
            }

            // Check for stack overflow: too many tokens
            int32_t numTokens = (this->field_0x08 - this->field_0x0C) >> 3;
            if (numTokens + 3 > 0x4000) {
                FUN_00627bd0("stack overflow (%s)", "too many marks in a path component");
                __debugbreak();  // swi(3)
                return;
            }

            // Ensure buffer has enough space for another entry
            if (this->field_0x18 - this->field_0x08 < 0x19) {  // less than 25 bytes left
                int32_t oldCapacity = this->field_0x20;
                int32_t newCapacity = (oldCapacity < 3) ? (oldCapacity + 23) : (oldCapacity * 2);
                int32_t newBuffer = FUN_006279a0(oldCapacity * 8, newCapacity * 8);
                this->field_0x18 = newBuffer + newCapacity * 8 - 0xA8;  // adjust end pointer
                this->field_0x1C = newBuffer;  // new base
                this->field_0x20 = newCapacity;
                FUN_00635b50();  // reinitialize?
            }

            // Update max size in secondary structure (at +0x14)
            uint32_t newSize = this->field_0x08 + 0x18;  // +24 bytes for new entry?
            if (*(reinterpret_cast<uint32_t*>(this->field_0x14) + 4) < newSize) {
                *(reinterpret_cast<uint32_t*>(this->field_0x14) + 4) = newSize;
            }

            // If secondary buffer has space, flush pending data
            if (*(reinterpret_cast<uint32_t*>(this->field_0x10) + 0x20) <=
                *(reinterpret_cast<uint32_t*>(this->field_0x10) + 0x24)) {
                uint32_t uVar6 = FUN_00627290();
                FUN_00626f80();
                FUN_00626fd0(0);
                FUN_00626f80();
                FUN_00627010(uVar6);
                FUN_006270e0();
            }

            // Write new entry: type 4, value from FUN_00638920 (likely substring before '?')
            int* writePtr = reinterpret_cast<int*>(this->field_0x08);
            writePtr[0] = 4;
            writePtr[1] = FUN_00638920();  // get substring token

            // Advance current pointer by 8 bytes
            this->field_0x08 += 8;

            // Copy the new entry to the next slot (duplicates? might be part of token handling)
            int* copyPtr = reinterpret_cast<int*>(this->field_0x08);
            copyPtr[0] = writePtr[0];
            copyPtr[1] = writePtr[1];

            // Advance again (skip the copy)
            this->field_0x08 += 8;

            // Find next '?' in the string (skipping the delimiter)
            found = _strchr(found + 1, '?');
        }
    }

private:
    // Unknown fields, offsets relative to 'this'
    int field_0x08;   // +0x08: current pointer into output buffer (elements)
    int field_0x0C;   // +0x0C: start pointer of output buffer?
    int field_0x10;   // +0x10: pointer to secondary buffer structure
    int field_0x14;   // +0x14: pointer to another structure (size tracking)
    int field_0x18;   // +0x18: end pointer of output buffer
    int field_0x1C;   // +0x1C: base address of output buffer
    int field_0x20;   // +0x20: capacity (number of elements)
};

// Helper functions called (prototypes, not defined here)
void FUN_00633990();
void FUN_00627360();
void FUN_006279a0(int oldSize, int newSize);
void FUN_00635b50();
uint32_t FUN_00627290();
void FUN_00626f80();
void FUN_00626fd0(int arg);
void FUN_00627010(uint32_t arg);
void FUN_006270e0();
int FUN_00638920();
void FUN_00625ca0();
void FUN_00626460();
void FUN_00627bd0(const char* fmt, const char* msg);
void __debugbreak();