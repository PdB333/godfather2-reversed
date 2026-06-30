// FUNC_NAME: findAndActivateMatchingEntity

//======================================================================
// Address: 0x0064d860
// Role: Scans a linked list of entity nodes for a specific type (stored in
//       global g_targetEntityType) and, if the matching node's active flag
//       is clear, calls an activation function.
//======================================================================

#include <cstdint>

// Global used as the target entity type to search for.
extern int32_t g_targetEntityType; // DAT_01205a20

// Forward declaration
bool performEntityActivation(void); // FUN_00650370

// Represents a node in the entity list.
// Offsets from Ghidra:
//   +0x0  - unknown (maybe larger structure)
//   +0x4  - int32_t m_activeFlag   (0 = not active)
//   +0x0C - EntityNode* m_next
//   +0x14 - int32_t m_type
struct EntityNode {
    int32_t m_unknown[1];   // +0x00
    int32_t m_activeFlag;   // +0x04 (true if active)
    EntityNode* m_next;     // +0x0C
    int32_t m_type;         // +0x14
};

// Represents the container that holds the entity list.
// Offsets from Ghidra:
//   +0x14 - int32_t m_listEmpty   (0 = empty, non‑zero = may contain items)
//   +0x1C - EntityNode* m_head
struct EntityListManager {
    int32_t m_pad1[5];         // +0x00 – +0x13
    int32_t m_listEmpty;       // +0x14
    int32_t m_pad2;            // +0x18 (alignment)
    EntityNode* m_head;        // +0x1C
};

//--------------------------------------------------------------------------
// The decompiled function.
// parameter: container – pointer to an EntityListManager structure.
// returns:   true if the list is empty and we found a matching inactive node
//            and activation succeeded; false otherwise.
//--------------------------------------------------------------------------
bool __fastcall findAndActivateMatchingEntity(EntityListManager* container) {
    // In the original disassembly the first argument (ecx) is unused.
    // We ignore it and treat the second argument (edx) as the container pointer.

    // Initial check: does the container indicate it's empty?
    bool isEmpty = (container->m_listEmpty == 0);

    // Only proceed if the list is empty AND there is a target type defined.
    if (isEmpty && (g_targetType != 0)) {
        bool found = false;
        // Walk the linked list
        for (EntityNode* node = container->m_head; node != nullptr; node = node->m_next) {
            if (node->m_type == g_targetType) {
                // Found a matching node – check its active flag.
                found = (node->m_activeFlag == 0);
                if (!found) {
                    // Node is already active; return false immediately.
                    return false;
                }
                // Node is inactive – try to activate it.
                bool activationResult = performEntityActivation();
                return activationResult;
            }
        }
        // No matching node found; return false (since bVar3 was set to false before the loop)
        return false;
    }
    // If the list is not empty or there is no target type, return the isEmpty value.
    // (isEmpty is true only when m_listEmpty == 0, else false)
    return isEmpty;
}