// FUNC_NAME: AptActionInterpreter::createInstance
// Address: 0x005adc90
// Role: Factory function to create an AptActionInterpreter object with initial setup and optional execution

#include <cstdint>

class AptActionInterpreter {
public:
    uint32_t flags;      // +0x00: bit0 = some flag, bit15 = another flag
    // uint16_t field2;  // +0x02: zeroed
    // ... padding / other fields up to +0x20
    uint32_t magic;      // +0x20: sentinel value 0xBEEFCEEC

    // Static factory method
    static AptActionInterpreter* createInstance(int param2);
};

// Forward declarations of internal init functions (likely members of AptActionInterpreter or related)
namespace AptInternal {
    void initBase();                          // FUN_005a0a80
    void reset(int value);                    // FUN_005a0d00
    bool checkCondition();                    // FUN_005a3c40
    void parseAction(void* buffer);           // FUN_005a92b0
    void executeAction(void* buffer);         // FUN_005b1390
    void cleanupAction(void* buffer);         // FUN_005a0a00
    void finalize();                          // FUN_005a1060
}

// Global allocation/deallocation function pointers (from import table)
extern void* (*g_allocate)(size_t size, int flags);   // DAT_0119caf0
extern void  (*g_deallocate)(void* ptr);               // DAT_0119caf4

AptActionInterpreter* AptActionInterpreter::createInstance(int param2) {
    // Debug assertion: "nParams <= 1" from AptActionInterpreter.cpp line 944
    if (param2 >= 2) {
        // Assertion macro with file and line info
        const char* assertMsg = "nParams <= 1";
        const char* assertFile = "..\\source\\Apt\\AptActionInterpreter.cpp";
        int assertLine = 0x3b0; // 944 decimal

        // Standard EA assert checking (from FS register chain)
        int* assertData = *(int**)(**(int**)(__readfsdword(0x2C) + 0x30) + 0x30); // FS[0x2C] -> TIB data
        uint32_t assertResult = 1;
        char* globalAssertFlag = &DAT_01128fea; // global assert enable flag
        if (assertData == nullptr) {
            if ((assertResult & 2) != 0) {
                *globalAssertFlag = 0;
            }
        } else {
            assertResult = (**(code**)(*assertData + 8))(&assertMsg, assertMsg); // invoke assert handler
            if (*(undefined1**)&assertMsg_data != nullptr) {
                if ((assertResult & 2) != 0) {
                    *globalAssertFlag = 0;
                }
            }
        }
        // Additional check to trigger breakpoint if conditions met
        if ((assertData != nullptr || (int)assertMsg_data != 4) &&
            ((assertResult & 1) != 0 || ((int)assertMsg_data == 0 || (int)assertMsg_data == 1))) {
            volatile int* crash = nullptr;
            *crash = 0; // intentional crash
        }
    }

    // Allocate memory for the object: 0x24 bytes (36 bytes)
    AptActionInterpreter* obj = static_cast<AptActionInterpreter*>(g_allocate(0x24, 0));
    if (obj == nullptr) {
        return nullptr;
    }

    // Initialize flags
    obj->flags = (obj->flags & 0xFFFF8001) | 1;   // clear bits 1-14, set bit 0
    *(uint16_t*)((uint8_t*)obj + 2) = 0;          // zero the second halfword (bits 16-31)
    obj->flags |= 0x8000;                           // set bit 15

    // Call base initialization
    AptInternal::initBase();

    // Set sentinel magic at offset 0x20
    obj->magic = 0xBEEFCEEC;

    // Reset internal state
    AptInternal::reset(0);

    // Check condition
    if (AptInternal::checkCondition()) {
        // Buffer for action parsing
        char* actionBuffer = nullptr;
        char* actionBufferEnd = nullptr;
        uint64_t actionData = 0;
        uint64_t extraData = 0;

        // Parse and execute action
        AptInternal::parseAction(&actionBuffer);
        AptInternal::executeAction(&actionBuffer);
        AptInternal::cleanupAction(&actionBuffer);
        AptInternal::finalize();

        // Free buffer if it was allocated separately (not on stack)
        if ((void*)actionBuffer != &actionData && (void*)actionBuffer != nullptr) {
            g_deallocate(actionBuffer);
        }
    }

    return obj;
}