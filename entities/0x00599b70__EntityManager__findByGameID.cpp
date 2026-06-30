// FUNC_NAME: EntityManager::findByGameID

// 0x00599b70 - Searches for an entity matching a game ID. The manager stores active slot indices 
// (bytes) at +0x9c, with a count at +0x9a. For each active slot, it retrieves the entity from an 
// internal table (+0x1bc) and checks the entity's ID field at +0x74. If the slot's type array 
// (at table+0x30) is not -2, a global engine callback is triggered (likely a debug or notification hook).

class EntityManager {
public:
    int __thiscall findByGameID(int gameID);
private:
    // +0x9a: number of active slots
    unsigned char m_activeSlotCount;
    // +0x9c: byte array of slot indices (size at least m_activeSlotCount)
    unsigned char m_slotIndices[256];   // approximate max size
    // +0x1bc: pointer to internal entity table
    EntityTable* m_entityTable;
};

struct EntityTable {
    int* m_typeArray;       // +0x30: array of type IDs (or status) per slot
    Entity** m_entityArray; // +0x2c: array of entity pointers per slot
};

struct Entity {
    // +0x74: unique game ID
    int m_gameID;
};

// Global engine object (address 0x01205590)
extern void* gEngine; // DAT_01205590

int EntityManager::findByGameID(int gameID) {
    if (m_activeSlotCount != 0) {
        for (int i = 0; i < (int)m_activeSlotCount; i++) {
            unsigned char slotIndex = m_slotIndices[i];
            int type = m_entityTable->m_typeArray[slotIndex];
            if (type != -2) {
                // Call a function stored at offset 4 of the global engine object
                void (*func)(void) = *(void(**)(void))((int)(*(int*)gEngine) + 4);
                func();
            }
            Entity* entity = m_entityTable->m_entityArray[slotIndex];
            if (entity->m_gameID == gameID) {
                return (int)entity; // return as integer (pointer)
            }
        }
    }
    return 0; // null
}