// FUNC_NAME: EARSObject::checkAndCleanup
// Function at 0x00477b20 - EARSObject::checkAndCleanup
// This method checks whether a child object is still active and cleans up if needed.
// Flags at +0x80: bit 2 (0x04) indicates deletion pending.
// Handle at +0x74: -1 if not used.

class EARSObject {
public:
    // Member offsets (relative to this):
    // +0x3c: m_list - list head for child management (used as container)
    // +0x54: m_pChild - pointer to a child object
    // +0x74: m_handle - resource handle (e.g., sound/animation; -1 if none)
    // +0x80: m_flags - byte flags, bit 2 = m_deletionFlag

    void __thiscall checkAndCleanup() {
        int* pChild = m_pChild;               // offset +0x54
        bool bActive = IsChildActive(pChild); // FUN_00402080

        // If child is no longer active OR this object's deletion flag is set
        if (!bActive || (m_flags & 4) != 0) {
            // Removal: only if deletion flag not already set and child exists
            if ((m_flags & 4) == 0 && pChild != nullptr) {
                RemoveChildFromList(&m_list, pChild); // FUN_00407e60
            }
            // Release handle if one is held
            if (m_handle != -1) {
                ReleaseHandle(); // FUN_00441e00
            }
        }
    }

private:
    // External functions (defined elsewhere)
    static bool IsChildActive(int* pChild);          // FUN_00402080
    static void RemoveChildFromList(void* pList, int* pChild); // FUN_00407e60
    static void ReleaseHandle();                     // FUN_00441e00

    // Placeholder fields (not part of this function's logic, but for completeness)
    char _pad0x3c[0x18];  // up to +0x54
    int* m_pChild;        // offset +0x54
    int _pad0x58[7];      // up to +0x74
    int m_handle;         // offset +0x74
    int _pad0x78[2];      // up to +0x80
    byte m_flags;         // offset +0x80
};