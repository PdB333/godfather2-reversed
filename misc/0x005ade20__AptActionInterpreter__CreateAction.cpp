// FUNC_NAME: AptActionInterpreter::CreateAction
#include <cstdint>

// Forward declarations for external functions used
extern void FUN_005a0a80(); // global init
extern void FUN_005a0d00(int); // unknown
extern bool FUN_005a3c40(); // condition check
extern void FUN_005a92b0(char** outString); // parse string
extern void FUN_005aba20(void** a, char** b); // string manipulation

// Forward declaration of the allocator/deallocator
extern void* __cdecl operator new(uint32_t size, int a);
extern void __cdecl operator delete(void* ptr);

// Structure for the allocated action (size 0x24)
struct AptAction {
    uint32_t flags;         // +0x00: bit0 and bit15 set initially
    uint16_t flagsHigh;     // +0x02: written as short (overlaps upper 16 bits of flags)
    int32_t field_4;        // +0x04: (index 1)
    int32_t field_8;        // +0x08: (index 2)
    int32_t field_c;        // +0x0c: (index 3)
    int32_t field_10;       // +0x10: (index 4)
    int32_t field_14;       // +0x14: (index 5)
    int32_t field_18;       // +0x18: (index 6)
    int32_t field_1c;       // +0x1c: (index 7)
    uint32_t magic;         // +0x20: set to 0xbeefceec
};

// Class definition (from file AptActionInterpreter.cpp)
class AptActionInterpreter {
public:
    AptAction* __thiscall CreateAction(int nParams);
};

// Assert macro (debug build)
#ifdef _DEBUG
#define ASSERT(cond, msg, file, line) \
    if (!(cond)) { \
        debugAssert(msg, file, line); \
    }
#else
#define ASSERT(cond, msg, file, line)
#endif

// Static flag for one-time assertion (from DAT_01128feb)
extern bool gAssertFlag;

// Implementation of CreateAction
AptAction* __thiscall AptActionInterpreter::CreateAction(int nParams) {
    uint32_t status = 1;

    // Assert that nParams <= 1
    ASSERT(nParams <= 1, "nParams <= 1", "..\\source\\Apt\\AptActionInterpreter.cpp", 0x3c7);

    // Allocate a new AptAction (size 0x24)
    AptAction* action = reinterpret_cast<AptAction*>(operator new(0x24, 0));
    if (action != nullptr) {
        // Initialize flags: set bit0 and clear bits 1-14, then zero upper half, then set bit15
        action->flags = (action->flags & 0xffff8001) | 1;
        *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(action) + 2) = 0;
        action->flags = action->flags | 0x8000;

        // Global initialization call
        FUN_005a0a80();

        // Set magic number
        action->magic = 0xbeefceec;
    }

    // Some secondary initialization
    FUN_005a0d00(0);

    // Conditionally parse a string and perform additional setup
    if (FUN_005a3c40()) {
        char* str = nullptr;
        char* dummy;
        void* addr;
        // Setup for parsing
        addr = &addr; // local_1c point to local_18 (stack variable)
        // dummy initialization to zero
        str = nullptr;
        dummy = nullptr;

        // Parse string from some global context
        FUN_005a92b0(&str);  // str is allocated?

        // Calculate sum of two fields
        int sum = action->field_c + action->field_4;

        // Prepare arguments for string manipulation
        char* end = str + reinterpret_cast<intptr_t>(addr);
        void* arg1 = &addr;
        char* arg2 = end;
        FUN_005aba20(&arg1, &arg2);  // Process the string

        // Reset magic (redundant)
        action->magic = 0xbeefceec;

        // Free the parsed string if it was dynamically allocated
        if (addr != (void*)&addr && addr != nullptr) {
            operator delete(addr);
        }
    }

    return action;
}