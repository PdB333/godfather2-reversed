// FUNC_NAME: EntityDataManager::loadEntitiesFromSceneData
// Address: 0x0054a9a0
// Role: Loads entities from a scene data structure into the game world, storing entity handles in an output vector.

struct AllocFlags {
    int type;       // +0x00: allocation type
    int alignment;  // +0x04: alignment requirement
    int pool;       // +0x08: memory pool index
};

struct EntityHandleVector {
    uint* data;     // +0x0C: pointer to array of entity handles
    int count;      // +0x10: number of handles stored
    int capacity;   // +0x14: total capacity of the array
};

// Global pointer to the game manager singleton
extern void* g_pGameManager; // DAT_01223480

// Forward declarations of internal functions
uint __fastcall allocEntity(int size, AllocFlags* flags); // FUN_009c8ed0
void __fastcall growHandleVector(int newCapacity);         // FUN_0054aee0
void __fastcall initEntityFromData(int entityData, int sceneData, int param3, int param4, int param5); // FUN_00556ab0
void __fastcall logEvent(int eventId, int context, int signExt); // FUN_009f01f0
void __fastcall markEntityProcessed(int entity, int flag);        // FUN_009e6ff0
void __fastcall finalizeListA(uint handle);                       // FUN_009e7450
void __fastcall finalizeListB(uint handle);                       // FUN_009ebe70
void __fastcall finalizeListC(uint handle);                       // FUN_009eace0

void __fastcall EntityDataManager::loadEntitiesFromSceneData(
    void* unused,          // param_1: unused (probably ECX register residue)
    EntityHandleVector* outVector, // param_2: output container for entity handles
    void* sceneData,       // param_3: hierarchical scene data structure
    char bMarkAsPrimary,   // param_4: if !=0, marks entity as primary
    int loggingContext)    // param_5: context identifier for logging
{
    // Check if game manager is initialized
    if (*(int*)((int)g_pGameManager + 0x24) == 0) {
        return;
    }

    // Get the main entity list from scene data
    // sceneData structure: +0x08 points to a container with:
    //   +0x08: array of entity data pointers
    //   +0x0C: count of entities in that array
    int entityListContainer = *(int*)((int)sceneData + 8);
    int entityCount = *(int*)(entityListContainer + 0xC);
    int entityArray = *(int*)(entityListContainer + 8);

    // Process each entity data entry
    for (int i = 0; i < entityCount; i++) {
        int entityData = *(int*)(entityArray + i * 4); // pointer to entity data

        // Set up allocation flags: type=2, alignment=0x10, pool=0
        AllocFlags allocFlags;
        allocFlags.type = 2;
        allocFlags.alignment = 0x10;
        allocFlags.pool = 0;

        // Allocate new entity object (size 0x70 bytes)
        uint newEntity = allocEntity(0x70, &allocFlags);
        if (newEntity == 0) {
            newEntity = 0; // redundant, but keep original logic
        } else {
            // Clear several fields of the new entity
            uint* entityFields = (uint*)newEntity;
            entityFields[0x48/4] = 0; // offset 0x48
            entityFields[0x4C/4] = 0; // offset 0x4C
            entityFields[0x50/4] = 0; // offset 0x50
            entityFields[0x54/4] = 0; // offset 0x54
            entityFields[0x58/4] = 0; // offset 0x58
            entityFields[0x5C/4] = 0; // offset 0x5C
            entityFields[0x40/4] = 0; // offset 0x40
            entityFields[0x44/4] = 0; // offset 0x44
            entityFields[0x60/4] = 0; // offset 0x60
            entityFields[0x64/4] = 0; // offset 0x64
            entityFields[0x68/4] = 0; // offset 0x68
        }

        // Ensure the output vector has capacity to add the new handle
        if (outVector->count == outVector->capacity) {
            int newCapacity = (outVector->capacity == 0) ? 1 : (outVector->capacity * 2);
            growHandleVector(newCapacity); // This function likely reallocs the handle array
        }
        uint* handleSlot = (uint*)(outVector->data + outVector->count * 4);
        outVector->count++;
        if (handleSlot != 0) {
            *handleSlot = newEntity;
        }

        // Initialize entity data from scene data (likely fills entity from data)
        initEntityFromData(entityData, sceneData, 0, 1, 0xFFFFFFFF);

        // Log event: 0x2003 (some game event), with context and sign extension of context
        logEvent(0x2003, loggingContext, loggingContext >> 0x1F);

        // If the bMarkAsPrimary flag is set, assign a special ID to the entity
        if (bMarkAsPrimary != 0) {
            *(int*)(newEntity + 0x4C) = 0x3E1; // 1009 decimal
        }

        // Pack the entity handle: shift right by 2, combine with high flags (0xC0000000)
        // This creates a packed identifier (likely for game object system)
        *(uint*)(entityData + 0x2C) = (newEntity >> 2) | 0xC0000000;

        // Mark this entity data as processed (flag = 1)
        markEntityProcessed(entityData, 1);
    }

    // Process additional lists within the scene data container
    // List at offset 0x2C: count at +0x30, array at +0x2C
    int count1 = *(int*)(entityListContainer + 0x30);
    int array1 = *(int*)(entityListContainer + 0x2C);
    for (int j = 0; j < count1; j++) {
        finalizeListA(*(uint*)(array1 + j * 4));
    }

    // List at offset 0x14: count at +0x18, array at +0x14
    int count2 = *(int*)(entityListContainer + 0x18);
    int array2 = *(int*)(entityListContainer + 0x14);
    for (int k = 0; k < count2; k++) {
        finalizeListB(*(uint*)(array2 + k * 4));
    }

    // List at offset 0x20: count at +0x24, array at +0x20
    int count3 = *(int*)(entityListContainer + 0x24);
    int array3 = *(int*)(entityListContainer + 0x20);
    for (int m = 0; m < count3; m++) {
        finalizeListC(*(uint*)(array3 + m * 4));
    }
}