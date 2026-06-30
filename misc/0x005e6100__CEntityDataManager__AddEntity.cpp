// FUNC_NAME: CEntityDataManager::AddEntity
#include <cstring>

// Forward declarations for external functions
int HashString(int param);  // FUN_005e5100
void DebugNotify();         // FUN_005dbc10

// Global constant (from DAT_00e2b1a4)
extern int g_DefaultValue;

class CEntityDataManager {
public:
    // Offset 0x603C: pointer to an array of slot structures (each 0x74 bytes)
    // The array is used to track entities, with a maximum of 512 slots (0x200).
    int* m_pSlotArray;  // +0x603C in the class layout

    /*
     * Adds an entity to the manager's slot pool.
     * The slot index is expected to be passed in the EDI register (slotIndex parameter).
     * Returns a pointer to the slot structure if successful, or nullptr otherwise.
     *
     * Parameters:
     *   pObject   - pointer to the entity object being added
     *   unused    - ignored (second parameter)
     *   nameParam - parameter used to generate an ID/hash via HashString()
     *   slotIndex - index into the slot array (must be < 0x200)
     */
    int* AddEntity(int* pObject, int unused, int nameParam, int slotIndex) {
        int* pSlot = nullptr;

        // Validate array exists and index is within range
        if (m_pSlotArray != nullptr && slotIndex < 0x200) {
            pSlot = reinterpret_cast<int*>(
                reinterpret_cast<char*>(m_pSlotArray) + slotIndex * 0x74);

            if (pSlot != nullptr) {
                // If slot is empty, initialize it
                if (*pSlot == 0) {
                    memset(pSlot, 0, 0x74);

                    // Set byte at offset 0x58 to 0xFF (likely a status flag)
                    *reinterpret_cast<unsigned char*>(pSlot + 0x16) = 0xFF;

                    // Clear int at offset 0x5C
                    pSlot[0x17] = 0;

                    // Set two ints at 0x60 and 0x64 to the global default value
                    pSlot[0x18] = g_DefaultValue;
                    pSlot[0x19] = g_DefaultValue;

                    // Store the name/hash ID
                    pSlot[1] = HashString(nameParam);

                    // Store the entity pointer
                    *pSlot = reinterpret_cast<int>(pObject);
                }

                // Ensure the object's type byte at offset 5 is set to 0x10 if zero
                if (reinterpret_cast<char*>(pObject)[5] == '\0') {
                    reinterpret_cast<char*>(pObject)[5] = 0x10;
                }
            }
        }

        DebugNotify();
        return pSlot;
    }
};