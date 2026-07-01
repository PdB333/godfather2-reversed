// Xbox PDB: EARS_Modules_SimNpc_GetMemory
// FUNC_NAME: PlayerMemory::getMemoryFlagsString
// Address: 0x00790890
// Function: Builds a comma-separated string of active memory event flags from a bitmask at this+0x5c.
//           Uses a string concatenation helper that appends label strings, then copies result into output buffer.

#include <cstring>

// Forward declaration of the string builder helper (FUN_004d4b00)
// It appends a string to a heap-allocated buffer; sets a destroy function pointer.
void appendMemoryFlagString(char** buffer, const char* separator, const char* flagName);

class PlayerMemory {
public:
    uint32_t m_memoryFlags; // +0x5c: bitmask of memory events

    void getMemoryFlagsString(char* outBuffer, size_t bufferSize) {
        char* flagString = nullptr;
        // Initialize local_4 (destroy function) to null; set by appendMemoryFlagString if needed
        // In the binary, local_4 was a function pointer; we assume it's set by the helper.
        // For simplicity, we use a local variable for cleanup.
        // The helper likely uses a global deallocation function pointer.

        if (m_memoryFlags & (1 << 8)) {
            appendMemoryFlagString(&flagString, "", "MEMORY_KILLED_BY_PLAYER");
        }
        if (m_memoryFlags & (1 << 9)) {
            appendMemoryFlagString(&flagString, "", "MEMORY_HURT_BY_PLAYER");
        }
        if (m_memoryFlags & (1 << 10)) {
            appendMemoryFlagString(&flagString, "", "MEMORY_HURT_BY_PLAYER_CAR");
        }
        if (m_memoryFlags & (1 << 11)) {
            appendMemoryFlagString(&flagString, "", "MEMORY_PLAYER_COMPLETED_JOB");
        }
        if (m_memoryFlags & (1 << 12)) {
            appendMemoryFlagString(&flagString, "", "MEMORY_WITNESSED_PLAYER_CRIME");
        }
        if (m_memoryFlags & (1 << 13)) {
            appendMemoryFlagString(&flagString, "", "MEMORY_WITNESS_BRIBED");
        }
        if (m_memoryFlags & (1 << 15)) {
            appendMemoryFlagString(&flagString, "", "MEMORY_WITNESS_INTIMIDATED");
        }

        const char* source = (flagString != nullptr) ? flagString : "";
        strncpy(outBuffer, source, bufferSize);

        if (flagString != nullptr) {
            // Deallocate via the stored function pointer (originally local_4)
            // For reconstruction, we assume a single deallocation function.
            free(flagString); // Simplified; original used a function pointer.
        }
    }
};