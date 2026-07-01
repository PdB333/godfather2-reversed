// FUNC_NAME: Allocator::allocateObject
// Function address: 0x0081ca60
// Role: Allocates a fixed-size block (44 bytes) via virtual allocator, initializes first two fields, and calls a constructor.

class Allocator {
public:
    // +0x00: vtable pointer
    // +0x04: m_buffer (pre-allocated buffer or nullptr)
    void* m_buffer; // offset 0x04

    // Virtual function at vtable index 0: allocate(size, buffer) -> void*
    virtual void* allocate(uint32_t size, void* buffer) = 0;

    // This function
    void* allocateObject(uint32_t arg) {
        void* buffer = m_buffer; // param_1[1]
        uint32_t stackBuffer[3] = {0, 0, 0}; // local_c, local_8, local_4 (all zero)
        if (buffer == nullptr) {
            buffer = stackBuffer; // use stack buffer as fallback
        }

        // Call virtual allocator with size 0x2c (44 bytes)
        void* allocated = allocate(0x2c, buffer);

        if (allocated != nullptr) {
            *(uint32_t*)allocated = stackBuffer[2]; // set first field to 0 (local_4)
        }
        if ((uint8_t*)allocated + 4 != nullptr) { // check for null on offset 4
            *(uint32_t*)((uint8_t*)allocated + 4) = (uint32_t)_ReturnAddress(); // store return address for debugging
        }
        if ((int32_t)allocated != -8) { // sentinel check (0xfffffff8)
            constructObject(arg); // FUN_0081ac90 - likely a constructor
        }
        return allocated;
    }

    void constructObject(uint32_t arg); // defined elsewhere
};