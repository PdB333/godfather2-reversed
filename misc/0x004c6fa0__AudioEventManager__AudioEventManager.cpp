// FUNC_NAME: AudioEventManager::AudioEventManager

#include <cstdint>

// Function at 0x004c6fa0
// Constructor for AudioEventManager class.
// Initializes internal arrays based on counts stored at offsets 0x98 and 0xA0,
// sets vtable pointers, and allocates memory for two arrays.

class AudioEventManager {
public:
    // Fields (offsets in bytes from this)
    // +0x00: uint32_t m_initialized; // set to 1
    // +0x04: (start of array data? or pointer to something)
    // +0x08: (unknown)
    // +0x24: offset 0x24*4 = 0x90: pointer to something (pointing to +0x04)
    // +0x25: offset 0x25*4 = 0x94: uint32_t? set to 0
    // +0x26: offset 0x26*4 = 0x98: uint32_t m_firstCount
    // +0x27: offset 0x27*4 = 0x9C: uint32_t* m_firstArray
    // +0x28: offset 0x28*4 = 0xA0: uint32_t m_secondCount
    // +0x29: offset 0x29*4 = 0xA4: uint32_t* m_secondArray
    // +0x2A: offset 0x2A*4 = 0xA8: uint32_t m_param

    // Constructor
    void __thiscall Constructor(uint32_t param)
    {
        uint32_t* firstCountPtr; // unaff_ESI + 0x26
        uint32_t firstCount;     // unaff_ESI[0x26]
        uint32_t secondCount;    // *puVar1 = unaff_ESI[0x28]
        uint32_t firstArraySize;
        uint32_t secondArraySize;

        // Set up vtable for first embedded object
        void** vtable1 = (void**)&PTR_LAB_00e3653c;
        FUN_0049f960(FUN_0049ead0, &vtable1);  // likely sets vtable pointer

        // Set up vtable for second embedded object
        void** vtable2 = (void**)&PTR_LAB_00e36548;
        secondCountPtr = this + 0x28;
        FUN_0049f960(FUN_0049eb20, &vtable2);

        // Allocate arrays if both counts are non-zero
        firstCount = *(this + 0x26);
        secondCount = *secondCountPtr;
        if (firstCount != 0 && secondCount != 0)
        {
            firstArraySize = firstCount * 0x50;  // 80 bytes per entry
            uint32_t allocSize = ~((int32_t)((int64_t)firstArraySize >> 32) != 0) | firstArraySize;
            *(this + 0x27) = (uint32_t)FUN_009c8e80(allocSize);

            secondArraySize = secondCount * 0x1c; // 28 bytes per entry
            uint32_t allocSize2 = ~((int32_t)((int64_t)secondArraySize >> 32) != 0) | secondArraySize;
            *(this + 0x29) = (uint32_t)FUN_009c8e80(allocSize2);

            // Third vtable setup for additional embedded object
            void** vtable3 = (void**)&PTR_LAB_00e36560;
            uint32_t local30 = 0;
            uint32_t local2c = 0;
            FUN_0049f960(FUN_0049ead0, &vtable3);

            // Initialize more fields
            *(this + 0x01) = 0;
            *(this + 0x02) = 0;
            *(this + 0x24) = this + 0x04; // set pointer to itself + 4
            *(this + 0x25) = 0;
            *(this + 0x00) = 1; // mark initialized
        }

        // Store parameter into field at offset 0xA8
        *(this + 0x2A) = param;
    }
};