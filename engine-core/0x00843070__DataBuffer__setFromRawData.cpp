// FUNC_NAME: DataBuffer::setFromRawData
// Address: 0x00843070
// Role: Loads a data buffer if the provided data starts with the magic 'TOB1' (0x31424f54).
//       Frees any existing buffer and allocates a new one, storing pointer at +0x50, size at +0x54, and valid flag at +0x58.

#include <cstring>

// Magic identifier for TOB1 data block
static const uint32_t kMagicTOB1 = 0x31424f54; // 'TOB1' in little-endian

// Forward declarations of internal allocator/deallocator functions
void* __cdecl allocAligned(size_t size, size_t alignment, int flags); // FUN_005e3bb0
void  __cdecl freeAligned(void* ptr);                                  // FUN_005e3c00

class DataBuffer {
public:
    // +0x50: pointer to raw data buffer
    void* m_data;
    // +0x54: size of the data buffer
    size_t m_size;
    // +0x58: flag indicating buffer is valid (1 = valid)
    uint8_t m_valid;

    // Method to set the buffer from raw data, only if magic matches
    void setFromRawData(int* data, size_t size) {
        // Check magic number at start of data
        if (*data == kMagicTOB1) {
            // Free existing buffer if present
            if (m_data != nullptr) {
                freeAligned(m_data);
                m_data = nullptr;
                m_size = 0;
            }

            // Allocate new buffer with 16-byte alignment
            void* newBuffer = allocAligned(size, 0x10, 0);
            if (newBuffer != nullptr) {
                // Copy the data
                memcpy(newBuffer, data, size);
                m_data = newBuffer;
                m_size = size;
                m_valid = 1;
            }
        }
    }
};