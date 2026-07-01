// FUNC_NAME: ObjectDetectionComponent::refreshDetectedEntityIDs
// Address: 0x0095bc80
// Reconstructs internal entity ID list from global entity manager, preserving the previously selected index if the entity is still present.

#include <cstdint>

class ObjectDetectionComponent {
public:
    void refreshDetectedEntityIDs();

private:
    // Global singleton pointer to the entity manager (e.g., NPCManager, EntityDataManager)
    static void* ms_entityManager;  // DAT_0112a590

    // Internal array of entity IDs (dynamic)
    int* m_entityIdArray;       // +0x58
    int  m_entityCount;         // +0x5c
    int  m_arrayCapacity;       // +0x60
    int  m_selectedIndex;       // +0x8c  // index of currently targeted/selected entity, -1 if none

    // Helper: reallocate array to new capacity (updates m_entityIdArray)
    void reallocateArray(int newCapacity);
};

// External function: checks if an entity passes some condition (e.g., line-of-sight, distance)
extern bool entityPassesCondition(void* entity);  // FUN_0084a510

void ObjectDetectionComponent::refreshDetectedEntityIDs()
{
    void* mgr = ms_entityManager;  // global manager pointer
    int previousSelectedId = -1;

    if (m_selectedIndex != -1) {
        // Save the ID of the previously selected entity if index is valid
        if (m_entityIdArray && m_selectedIndex >= 0 && m_selectedIndex < m_entityCount) {
            previousSelectedId = m_entityIdArray[m_selectedIndex];
        }
    }

    // Reset selection and clear the list
    m_selectedIndex = -1;
    if (m_entityCount != 0) {
        m_entityCount = 0;
    }

    unsigned int totalEntities = *(unsigned int*)((uint8_t*)mgr + 0xc);  // count of entities in manager
    void** entityPtrArray = *(void***)((uint8_t*)mgr + 0x8);            // array of entity pointers

    for (unsigned int i = 0; i < totalEntities; ++i) {
        void* entity = entityPtrArray[i];
        if (entity != nullptr && entityPassesCondition(entity)) {
            int entityId = *(int*)*(void**)entity;  // First field in entity struct is ID

            // Check if we need to grow the array
            if (m_entityCount == m_arrayCapacity) {
                int newCapacity = (m_arrayCapacity == 0) ? 1 : (m_arrayCapacity * 2);
                reallocateArray(newCapacity);
                // After reallocation, m_entityIdArray is updated
            }

            int* insertPos = &m_entityIdArray[m_entityCount];
            m_entityCount++;
            *insertPos = entityId;

            // Preserve the previously selected index if this ID matches
            if (previousSelectedId == entityId) {
                m_selectedIndex = m_entityCount - 1;
            }
        }
    }

    // Ensure selection is valid: if list is non-empty and selected index is out-of-bounds or invalid, reset to first element
    if (m_entityCount > 0 && (m_selectedIndex >= m_entityCount || m_selectedIndex == -1)) {
        m_selectedIndex = 0;
    }
}