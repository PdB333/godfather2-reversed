// FUNC_NAME: Process::isActive
// Function at 0x004a58a0
// Returns 1 if any child process or task is active, else 0.
// Checked: single active pointer (+0x38), two arrays of fixed-size entries (+0x74, +0x68) with flag at offset 4 (bit 3 = active),
// and an array of object pointers (+0x5c) calling virtual isActive() at vtable+4.

class Process {
public:
    // +0x00 vtable
    // +0x38 Process* m_pActiveChild;         // single pointer, if non-null => active
    // +0x5c Process** m_ppChildProcesses;    // array of Process* (third group)
    // +0x60 int m_numChildProcesses;
    // +0x68 ChildEntry2* m_pChildren2;       // array of 16-byte entries
    // +0x6c int m_numChildren2;
    // +0x74 ChildEntry1* m_pChildren1;       // array of 8-byte entries
    // +0x78 int m_numChildren1;

    // 8-byte child entry structure (first group)
    struct ChildEntry1 {
        char unknown[4];
        char flags;          // +0x04 bit 3 = active
        char pad[3];
    };

    // 16-byte child entry structure (second group)
    struct ChildEntry2 {
        char unknown[4];
        char flags;          // +0x04 bit 3 = active
        char pad[11];
    };

    bool isActive() const {
        // Check single active pointer
        if (m_pActiveChild != nullptr) {
            return true;
        }

        // Check first group (8-byte entries)
        if (m_numChildren1 > 0) {
            for (int i = 0; i < m_numChildren1; i++) {
                if ((m_pChildren1[i].flags & 0x08) != 0) {
                    return true;
                }
            }
        }

        // Check second group (16-byte entries)
        if (m_numChildren2 > 0) {
            for (int i = 0; i < m_numChildren2; i++) {
                if ((m_pChildren2[i].flags & 0x08) != 0) {
                    return true;
                }
            }
        }

        // Check third group: array of Process* – call virtual isActive() at vtable+4
        if (m_numChildProcesses > 0) {
            for (int i = 0; i < m_numChildProcesses; i++) {
                Process* pProc = m_ppChildProcesses[i];
                if (pProc != nullptr) {
                    // Call function at vtable+4 (index 1)
                    bool (Process::*func)() = reinterpret_cast<bool (Process::*)()>(pProc->vtable[1]);
                    if ((pProc->*func)()) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    // Note: vtable assumed to be at +0x00 for each Process object.
    // The first entry is likely destructor or type info, second is isActive().
};

// The exact class name may differ, but the logic is reconstructed from Ghidra output.