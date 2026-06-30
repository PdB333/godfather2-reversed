// FUNC_NAME: AptValue::assertTypeId
// Function address: 0x005abbf0
// Asserts that the object type tag equals 0x800B. Returns 1 if true, otherwise triggers debug break and returns 0.
// Source: c:\packages001_pc\apt\0.19.optimized\source\apt\_AptValue.h (line 420)

// Based on Ghidra decompilation of EA EARS engine debug assertion mechanism.
// The function checks if 'this' is non-null, then tests whether the first 32-bit field (type ID) equals 0x800B.
// If the assertion fails, it calls a debug reporting function and triggers a breakpoint (via int 3).

#include <cstdint>

// Forward declaration of internal debug reporting function (signature approximated)
typedef int (*DebugReportFunc)(const char* file, const char* sourceName, int line, int unknown, const char* expression);

// Global debug flag referenced in assertion logic
extern char DEBUG_FLAG_01128fd2;

class AptValue {
public:
    // First field: type identifier tag
    uint32_t typeTag; // offset +0x00

    // Checks if the object is of type 0x800B.
    // Returns 1 if type matches, otherwise triggers debug assertion and returns 0.
    int assertTypeId() {
        // If 'this' is null, trigger assertion failure
        if (this == nullptr) {
            // Prepare assertion context (debug information)
            const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
            const char* sourceName = "apt\\_AptValue.h"; // approximate
            int line = 0x1a4; // 420
            int unknown = 2;
            const char* expression = "??? ASSERT EXPRESSION ???"; // place holder, original expression string likely different

            // Check global debug flag
            if (DEBUG_FLAG_01128fd2 != '\0') {
                // Obtain the debug report function pointer from the thread's exception handler chain (MSVC-specific)
                // This is a common pattern in EA's debug assertion macros.
                struct TEB {
                    void* exceptionList; // offset 0x00
                    void* stackBase;
                    void* stackLimit;
                    void* subSystemTib;
                    // ...
                };
                // FS:[0x2C] points to the thread's TEB (Thread Environment Block)
                // The debug report function is stored at an offset within the exception handler chain.
                // This code is highly compiler- and platform-specific.
                void** pTEB = (void**)__readfsdword(0x2C);
                void** pExceptionList = (void**)(*pTEB); // dereference to get the first handler
                void** pDebugFuncPtr = (void**)(*(int*)pExceptionList + 0x30); // offset +0x30
                DebugReportFunc reportFunc = (DebugReportFunc)(*pDebugFuncPtr);

                // Call the debug report function (returns a status code)
                if (reportFunc != nullptr) {
                    int result = reportFunc(file, sourceName, line, unknown, expression);
                    // If the report function indicates termination, break into debugger
                    if ((result & 1) != 0 || (unknown == 0 || unknown == 1)) {
                        // Trigger a breakpoint (int 3) and then likely call a function (unusual pattern)
                        // The original code probably had __debugbreak() or similar.
                        __debugbreak();
                        // The swi(3) instruction is interpreted as a call to a function in the decompilation;
                        // actual behavior is to pause execution.
                        // Return whatever the debug function returns (often 0)
                        return 0;
                    }
                }
                // Clear the debug flag if needed
                if (DEBUG_FLAG_01128fd2 != '\0' && (result & 2) != 0) {
                    DEBUG_FLAG_01128fd2 = 0;
                }
            }
        }

        // Check the type tag: must be 0x800B (lower 15 bits = 0xB, bit 15 set)
        // This is a specific type identifier used by the Apt library.
        if ((this->typeTag & 0x7FFF) == 0x0B && (this->typeTag & 0x8000) != 0) {
            return 1; // Type matches
        }
        return 0; // Type does not match
    }
};