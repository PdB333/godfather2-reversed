// FUNC_NAME: EntityManager::getObjectByID

// Global data:
// g_entityCount (DAT_01205594) - number of slots
// g_entityArray (DAT_0119c6d0) - array of object pointers
// g_managerVtable (DAT_01205590) - pointer to some manager class vtable (entry +4 is a creation callback)

class EntityManager {
public:
    // Searches for an object with the given ID.
    // Creates a new object in empty slots (via manager vtable callback) before checking.
    // Returns pointer to the found object, or 0 if not found.
    static int getObjectByID(int objectID)
    {
        int i = 0;
        if (0 < g_entityCount) {
            do {
                if (g_entityArray[i] == 0) {
                    // Slot empty – call the creation function from the manager vtable
                    // (offset +4 in the vtable)
                    void (*createFunc)() = *(void (**)())(*g_managerVtable + 4);
                    createFunc();
                }
                // Check if this object has the requested ID (ID stored at offset +8)
                if (*(int*)(g_entityArray[i] + 8) == objectID) {
                    return g_entityArray[i];
                }
                i = i + 1;
            } while (i < g_entityCount);
        }
        return 0;
    }
};

// External definitions for global data
extern int g_entityCount;              // DAT_01205594
extern int* g_entityArray;             // DAT_0119c6d0
extern int** g_managerVtable;          // DAT_01205590