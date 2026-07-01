// FUNC_NAME: HandleManager::resolveHandle
// Address: 0x008d08a0
// This function resolves a handle from resource IDs and manages a linked list node.
// It checks if any of four resource IDs (at +0x78..+0x84) are active.
// If so, it looks up a resource by hash (0xb7d515f0) and updates the head node pointer at +0x90.
// Returns a handle that encodes validity and offset.

#include <cstdint>

class HandleManager {
public:
    // Offsets:
    // +0x78: m_resourceIds[4] (uint32)
    // +0x90: m_headNode (Node*)
    // +0x94: m_prevNext (Node*)

    uint32_t m_resourceIds[4];      // +0x78
    void* m_headNode;               // +0x90
    void* m_prevNext;               // +0x94

    // External functions (assumed)
    int getFirstActiveResourceId(uint32_t* array, int unused); // FUN_00445ff0
    char findResourceByHash(int resourceId, uint32_t hash, uint32_t* outHandle); // FUN_004480d0
    void freeNode(void** nodePtr); // FUN_004daf90

    uint32_t resolveHandle() {
        // Check if any resource ID is non-zero
        if (m_resourceIds[0] != 0 || m_resourceIds[1] != 0 || 
            m_resourceIds[2] != 0 || m_resourceIds[3] != 0) {
            uint32_t handle = 0;
            uint32_t localHandle = reinterpret_cast<uint32_t>(this); // Actually used as output
            int resourceId = getFirstActiveResourceId(m_resourceIds, 0);
            if (resourceId != 0) {
                char found = findResourceByHash(resourceId, 0xb7d515f0, &localHandle);
                handle = (found != 0) ? localHandle : 0;
            }

            // Compute new node pointer (node base = handle + 0x48)
            void* newNode = (handle != 0) ? reinterpret_cast<void*>(handle + 0x48) : nullptr;

            // Update head node if different
            if (m_headNode != newNode) {
                if (m_headNode != nullptr) {
                    freeNode(&m_headNode);
                }
                m_headNode = newNode;
                if (newNode != nullptr) {
                    // Save old next pointer of the new node into m_prevNext
                    m_prevNext = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(newNode) + 4);
                    // Set new node's next to point to the head pointer location
                    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(newNode) + 4) = &m_headNode;
                }
            }
        }

        // Return handle based on head node
        if (m_headNode != nullptr) {
            uintptr_t offset = reinterpret_cast<uintptr_t>(m_headNode) - 0x48;
            // Encode: low 24 bits = offset >> 8, high 8 bits = (offset != 0)
            return (static_cast<uint32_t>(offset >> 8) & 0x00FFFFFF) | ((offset != 0) ? 0xFF000000 : 0);
        }
        return 0;
    }
};