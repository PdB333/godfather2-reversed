// FUNC_NAME: Container20::push_back
// Function address: 0x00657ab0
// Role: Appends a 20-byte element to a dynamic array. The container stores count at +0x00 and array pointer at +0x08.
// Called before increment to possibly check capacity or acquire a lock.

struct Element20 {
    uint64_t field0;   // +0x00
    uint64_t field8;   // +0x08
    uint32_t field10;  // +0x10
};

class Container20 {
public:
    int32_t count;    // +0x00
    int32_t unknown;  // +0x04 (unused in this function)
    Element20* array; // +0x08
};

// External subroutine called at 0x00654620; purpose unclear.
void someInternalFunction();

void Container20::push_back(const Element20& elem) {
    someInternalFunction();

    count++;
    Element20* dest = &array[count - 1];

    if (dest != nullptr) {
        *dest = elem;  // Copy 20 bytes (two uint64_t + one uint32_t)
    }
}