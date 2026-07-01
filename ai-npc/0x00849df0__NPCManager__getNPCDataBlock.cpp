// FUNC_NAME: NPCManager::getNPCDataBlock
// Reconstructed from Ghidra address 0x00849df0
// Description: Given an NPC ID, returns a pointer to its data block at offset 0x5c,
// or a global default pointer if not found.

#include <cstdint>

// Forward declaration of the helper function that converts an ID to an index.
// At 0x00849a70, likely: int idToIndex(uint32_t id)
int idToIndex(uint32_t id);

// Global default data block (address 0x01218244 in the original binary)
static uint32_t g_defaultDataBlock = 0;

class NPCManager {
public:
    // This function is __thiscall, corresponds to the decompiled FUN_00849df0
    uint32_t* getNPCDataBlock(uint32_t npcId) {
        int index;
        if (npcId != 0) {
            index = idToIndex(npcId);
            if (index >= 0) {
                // m_pDataArray is at this+0x10, points to an array of pointers to NPC objects.
                uint32_t** arrayPtr = reinterpret_cast<uint32_t**>(this + 0x10);
                uint32_t* npcObject = arrayPtr[index];
                if (npcObject != nullptr) {
                    // Return pointer to offset +0x5c within the NPC object.
                    return reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(npcObject) + 0x5c);
                }
            }
        }
        // Fallback: return address of global default data block.
        return &g_defaultDataBlock;
    }

private:
    // Structure fields (guessed)
    // +0x00: vtable pointer (4 bytes)
    // +0x04: ... other fields ...
    // +0x10: uint32_t** m_pDataArray; // array of NPC object pointers
};