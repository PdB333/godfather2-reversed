// FUNC_NAME: DebugLogger::logSourceLine
#include <cstdint>

// Forward declarations of external functions
extern void debugCopyString(char* dest, const char* src);
extern void debugPrintf(const char* format, const char* file, uint32_t line, const char* message);

// Internal structures (offsets known from disassembly)
struct LogData {
    int* somePtr;           // +0x00: pointer to something (maybe vtable)
    int flags;              // +0x08: bit 0 = disable bit (0 means enabled), bit 1 = reset?
    int currentPos;         // +0x0C: current program counter or stored address
    int* bufferPtr;         // +0x10: pointer to a buffer
};

struct SymbolTable {
    int baseAddr;           // +0x0C: base address for line calculation
    uint32_t* lineNumbers;  // +0x14: array of line numbers (or null)
    char** fileNamePtr;     // +0x20: pointer to a pointer to filename string, +0x10 offset gives the actual string
};

void DebugLogger::logSourceLine(const char* message) {
    LogData* pLogData = *reinterpret_cast<LogData**>(reinterpret_cast<uint8_t*>(this) + 0x14);
    if ((pLogData->flags & 1) == 0) {
        if ((pLogData->flags & 2) != 0) {
            pLogData->currentPos = *pLogData->bufferPtr;
        }
        // The somePtr points to an object with a vtable; subtract 4 to get the symbol table pointer
        SymbolTable* pSymbolTable = *reinterpret_cast<SymbolTable**>(
            *reinterpret_cast<int*>(reinterpret_cast<int*>(pLogData->somePtr) - 4) + 0x0C
        );
        int index = ((pLogData->currentPos - pSymbolTable->baseAddr) >> 2) - 1;
        uint32_t lineNumber;
        if (index < 0) {
            lineNumber = 0xFFFFFFFF; // -1 as unsigned
        } else if (pSymbolTable->lineNumbers == nullptr) {
            lineNumber = 0;
        } else {
            lineNumber = pSymbolTable->lineNumbers[index];
        }
        char fileNameBuf[60];
        // fileNamePtr at +0x20, then dereference and add 0x10 to skip some header
        debugCopyString(fileNameBuf, *reinterpret_cast<const char**>(
            reinterpret_cast<uint8_t*>(pSymbolTable) + 0x20
        ) + 0x10);
        debugPrintf("%s:%d: %s", fileNameBuf, lineNumber, message);
    }
}