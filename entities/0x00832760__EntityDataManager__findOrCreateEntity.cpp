//FUNC_NAME: EntityDataManager::findOrCreateEntity
// Address: 0x00832760
// Role: Creates or retrieves an entity by GUID, copies transform data, and optionally initializes it.

class EntityDataManager {
public:
    // Virtual function table at +0x14: checks if a GUID is valid
    bool isValidGUID(int* guid); // param_2

    // Pointer to transform data (e.g., matrix or quaternion) stored at +0x08 (param_1[2])
    int* m_transformData; // offset +0x08

    // Method to find or create an entity
    int findOrCreateEntity(int* guid, int* optionalParam); // param_2 = guid, param_3 = optionalParam
};

class Entity {
public:
    // Virtual function table
    // +0x04: virtual function (e.g., setOwner or init)
    virtual void setOwner(int* owner) = 0; // vtable+4

    // Fields (offsets in ints)
    int m_guid[4]; // offsets 7,8,9,10 (28,32,36,40 bytes)
    int m_transform[4]; // offsets 0xf,0x10,0x11,0x12 (60,64,68,72 bytes)
};

// External functions
Entity* findEntityByGUID(int* guid); // FUN_0082d0c0
void* operator new(size_t size); // FUN_009c8f80 (simplified)
Entity* createEntity(); // FUN_008295f0 (constructor/factory)
void registerEntity(Entity* entity); // FUN_00832180 (add to manager)

int EntityDataManager::findOrCreateEntity(int* guid, int* optionalParam) {
    // Check if the GUID is valid via virtual function
    if (!isValidGUID(guid)) {
        return 0;
    }

    bool isNewEntity = true;
    Entity* entity = findEntityByGUID(guid);

    if (entity == nullptr) {
        isNewEntity = false;
        // Allocate memory for a new entity
        void* memory = operator new(0x80); // size 0x80 (128 bytes)
        if (memory != nullptr) {
            entity = createEntity(); // construct entity
            if (entity != nullptr) {
                goto LAB_008327e0;
            }
        }
        return 0;
    }

LAB_008327e0:
    // Copy GUID into entity (offsets 7-10)
    entity->m_guid[0] = guid[0];
    entity->m_guid[1] = guid[1];
    entity->m_guid[2] = guid[2];
    entity->m_guid[3] = guid[3];

    // If this manager has transform data, copy it into entity (offsets 0xf-0x12)
    if (m_transformData != nullptr) {
        entity->m_transform[0] = *(int*)(m_transformData + 0x24); // +0x24 = 36 bytes
        entity->m_transform[1] = *(int*)(m_transformData + 0x28); // +0x28 = 40 bytes
        entity->m_transform[2] = *(int*)(m_transformData + 0x2c); // +0x2c = 44 bytes
        entity->m_transform[3] = *(int*)(m_transformData + 0x30); // +0x30 = 48 bytes
    }

    // If optional parameter provided, call virtual function on entity
    if (optionalParam != nullptr) {
        entity->setOwner(optionalParam); // vtable+4
    }

    // If entity was newly created, register it
    if (!isNewEntity) {
        registerEntity(entity);
    }

    return 1;
}