// FUNC_NAME: BitStream::readAndInvokeCallback
// Function address: 0x00942cd0
// Reads three uint32 values from the internal buffer (offset +0x18) and invokes a callback function.

// Assume the existence of a helper function that reads data from the buffer into a variable.
extern void FUN_0049c470(void* dest, uint32_t size, uint32_t count);

class BitStream {
public:
    // +0x18: Current read position in the buffer (pointer to uint32_t)
    uint32_t* m_readPos;

    // Reads three arguments and calls the provided callback.
    // callbackPtr points to a function pointer that will be invoked with (arg1, arg2, arg3).
    void readAndInvokeCallback(void (*callbackPtr)(uint32_t, uint32_t, uint32_t)) {
        // Save current buffer position (this pointer is preserved in a local variable)
        uint32_t* currentPos = m_readPos;

        // Read first argument
        uint32_t arg1 = *currentPos;
        m_readPos = currentPos + 1;

        // Read second argument into the stack variable using the helper.
        // The helper reads 4 bytes (size=4) from the buffer (conceptually 4 times? Actually count=4 may be something else).
        // This overwrites the local buffer position variable, mimicking the original code.
        uint32_t arg2;
        FUN_0049c470(&arg2, 4, 4);

        // Read third argument from the current buffer position (after helper's updates)
        uint32_t* posAfterHelper = m_readPos;
        uint32_t arg3 = *posAfterHelper;
        m_readPos = posAfterHelper + 1;

        // Call the callback with the three deserialized arguments
        if (callbackPtr) {
            (*callbackPtr)(arg1, arg2, arg3);
        }
    }
};