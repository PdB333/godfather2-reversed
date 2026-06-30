// FUNC_NAME: WideString::assign

// Reconstructed from Ghidra decompilation at 0x004dcc60
// This function appears to be a wide string assignment/copy method.
// It handles self-assignment and manages buffer allocation/release.

struct WideString {
    wchar_t* data;       // +0x00: pointer to wide string data
    uint32_t length;     // +0x04: number of characters (not bytes)
    uint32_t capacity;   // +0x08: allocated capacity in characters
    void (*release)(wchar_t*); // +0x0C: function to release the data buffer
};

// Forward declarations of helper functions (addresses from Ghidra)
uint32_t getGlobalBufferSize(); // FUN_004dc860
void memzero(void* ptr, uint32_t size); // FUN_004dbb10
void freeBuffer(wchar_t* data, uint32_t size); // FUN_004dba00

bool __thiscall WideString::assign(WideString* this, const wchar_t* source, WideString* temp1, WideString* temp2)
{
    bool success = false;

    // Check for self-assignment (this == temp1 or this == temp2)
    if (this == temp1 || this == temp2) {
        // Self-assignment: free current buffer and recursively assign from source
        freeBuffer(this->data, this->length);
        success = assign(source, temp1, temp2); // recursive call with source as new this? (unusual)
        return success;
    }

    // Clear temporary buffers
    if (temp1->data != nullptr) {
        temp1->release(temp1->data);
    }
    temp1->data = nullptr;
    temp1->capacity = 0;
    temp1->length = 0;

    if (temp2->data != nullptr) {
        temp2->release(temp2->data);
    }
    temp2->data = nullptr;
    temp2->capacity = 0;
    temp2->length = 0;

    // If this buffer has data, process it
    if (this->length != 0) {
        uint32_t currentData = reinterpret_cast<uint32_t>(this->data);
        uint32_t globalBufferSize = getGlobalBufferSize();

        if (globalBufferSize != 0) {
            // If current data is before the global buffer, zero the gap
            if (currentData < globalBufferSize) {
                memzero(reinterpret_cast<void*>(currentData), (globalBufferSize - currentData) >> 1);
            }

            // Find the length of the source wide string (null-terminated)
            const wchar_t* src = source;
            while (*src != 0) {
                ++src;
            }
            int32_t srcLen = (src - source); // number of wchar_t characters

            // Calculate destination address after the global buffer
            uint32_t destAddr = globalBufferSize + srcLen * 2; // 2 bytes per wchar_t
            wchar_t* dest = reinterpret_cast<wchar_t*>(destAddr);

            // If the destination already contains data, zero it out
            if (*dest != 0) {
                uint32_t remaining = this->length - ((destAddr - reinterpret_cast<uint32_t>(this->data)) >> 1);
                memzero(dest, remaining);
            }

            success = true;
        }
    }

    return success;
}