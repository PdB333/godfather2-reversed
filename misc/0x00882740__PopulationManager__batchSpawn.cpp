// FUNC_NAME: PopulationManager::batchSpawn
// Address: 0x00882740
// This function performs batched spawning of entities. It checks a flag to ensure single execution,
// retrieves a list of entity indices from a slot manager, builds a creation structure with
// defaults from the object (or provided by a virtual method), and calls the engine's spawn function
// for each non-zero index. A virtual callback is invoked after each spawn.

// Declarations for engine functions (actual names unknown, but behavior inferred)
extern int DAT_0112ad8c;      // global singleton or configuration
extern int DAT_01205228;      // global singleton or configuration
extern void* PTR_FUN_00d5dbbc; // pointer to a static function table

extern bool getActiveSpawnIndices(int* outIndices, int maxCount); // FUN_00543390
extern int  getActiveSpawnCount();                                // FUN_00543370
extern void spawnEntityFromData(void* creationData, int entityId, int flag); // FUN_00408bf0
extern void freeTemporaryBuffer(int* buffer);                     // FUN_004daf90

// Structure used to pass creation parameters
struct EntityCreationData {
    int someGlobal1;     // +0x00
    void** funcTablePtr; // +0x04 (pointer to &funcTable)
    int  magic;          // +0x08 (0x537d6f63)
    int  data[3];        // +0x0c (aiStack_28)
    int  flag;           // +0x18 (uStack_14)
    int  value;          // +0x1c (iStack_1c)
    int  zeroField;      // +0x20 (uStack_44)
    int  someGlobal2;    // +0x24 (uStack_10)
    // Note: actual layout may differ due to compiler reordering; this is reconstructed.
};

// Default spawn parameters obtained from object or virtual method
struct SpawnDefaults {
    int field1; // corresponds to local_54 / m_field1c
    int field2; // iStack_58 / m_field1b
    int field3; // iStack_50 / m_field1d
};

class PopulationManager {
public:
    // Virtual function table offsets:
    // +0x30: bool getSpawnDefaults(SpawnDefaults* out) __thiscall
    // +0x34: void onEntitySpawned(int entityIndex) __thiscall

    void batchSpawn() {
        // +0x1e (0x78) flags
        if ((m_flags & 0x10) != 0) {
            return; // Already performed batch spawn
        }

        SpawnDefaults defaults;
        // Virtual call to obtain spawn defaults (may fill the struct)
        bool ok = (**(bool (__thiscall**)(PopulationManager*, SpawnDefaults*))((int*)this)[0x30 / 4])(this, &defaults);
        if (!ok) {
            // Use stored defaults from object fields
            defaults.field1 = m_field1c; // +0x1c (0x70)
            defaults.field2 = m_field1b; // +0x1b (0x6c)
            defaults.field3 = m_field1d; // +0x1d (0x74)
        }

        m_flags |= 0x10; // Set initialized flag

        int entityIndices[4];
        if (!getActiveSpawnIndices(entityIndices, 4)) {
            return;
        }

        int count = getActiveSpawnCount();
        for (int i = 0; i < count; i++) {
            int entityIndex = entityIndices[i];
            if (entityIndex == 0) {
                continue;
            }

            EntityCreationData creationData;
            creationData.someGlobal1 = DAT_0112ad8c;
            creationData.someGlobal2 = DAT_01205228;
            creationData.funcTablePtr = &PTR_FUN_00d5dbbc; // pointer to function table
            creationData.magic = 0x537d6f63;               // magic value
            creationData.data[0] = 0;
            creationData.data[1] = 0;
            creationData.data[2] = defaults.field2;        // iStack_58
            creationData.flag = 1;                         // uStack_14
            creationData.value = defaults.field1;          // iStack_1c (local_54)
            creationData.zeroField = 0;                    // uStack_44

            // Spawn the entity with ID offset +0x3c
            spawnEntityFromData(&creationData, entityIndex + 0x3c, 0);

            // Virtual callback after spawn
            (**(void (__thiscall**)(PopulationManager*, int))((int*)this)[0x34 / 4])(this, entityIndex);

            // Free temporary buffer if allocated by spawn function
            if (creationData.data[0] != 0) {
                freeTemporaryBuffer(creationData.data);
            }
        }
    }

private:
    // Offsets measured from 'this' (each int = 4 bytes)
    // +0x1b (0x6c): field1b
    int m_field1b;
    // +0x1c (0x70): field1c
    int m_field1c;
    // +0x1d (0x74): field1d
    int m_field1d;
    // +0x1e (0x78): flags (bit 4 = 0x10 means batch spawn executed)
    int m_flags;
};