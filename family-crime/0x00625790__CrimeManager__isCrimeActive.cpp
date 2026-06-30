// FUNC_NAME: CrimeManager::isCrimeActive
// Address: 0x00625790
// Role: Checks if a crime entry (index-based) is active and of type 6. Returns true if the entry exists, has type=6, and the target object's byte at +0x6 is non-zero.
// Class fields: m_pEnd at +0x8 (pointer past last entry), m_pData at +0xC (pointer to array of CrimeEntry structs).
// Each CrimeEntry: 8 bytes: int type + void* target (object with a flag at +0x6).

// Helper function: getDefaultEntry() at address 0x00625430, returns a pointer to a default/sentinel CrimeEntry (likely null or static).

struct CrimeEntry {
    int type;       // +0x0
    void* target;   // +0x4
};

class CrimeManager {
public:
    CrimeEntry* m_pEnd;   // +0x8
    CrimeEntry* m_pData;  // +0xC

    // Returns true if the crime at given 1-based index is active (type 6, target flag set).
    bool isCrimeActive(int index);
};

// This function is __thiscall; this pointer is passed in EAX (custom convention), but we use standard member function syntax.
// The original assembler reads this from EAX at entry (in_EAX), which corresponds to 'this'.
bool CrimeManager::isCrimeActive(int index) {
    CrimeEntry* entry;

    if (index < 1) {
        // For index 0 or negative, use a default entry from helper function.
        entry = (CrimeEntry*)FUN_00625430(); // getDefaultEntry()
    } else {
        // Compute entry pointer: 1-based index, so entry = m_pData + (index - 1)
        entry = m_pData + (index - 1);
        // Check bounds: if the computed entry is at or past the end pointer, it's invalid.
        if (m_pEnd <= entry) {
            return false;
        }
    }

    // Check if entry is valid, type is 6, and the target's flag at offset 6 is non-zero.
    if (entry != nullptr && entry->type == 6 && *((char*)entry->target + 6) != 0) {
        return true;
    }
    return false;
}