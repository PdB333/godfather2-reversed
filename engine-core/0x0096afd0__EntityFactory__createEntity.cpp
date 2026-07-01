// FUNC_NAME: EntityFactory::createEntity
// Address: 0x0096afd0
// This factory function allocates a new Entity object (size 0x60) and initializes it
// based on a data interface obtained from param_2 (likely a data source or template ID).
// param_1 is a pointer to a manager/owner object (e.g., EntityDataManager) that provides
// a parent container or context. The function compares the entity type against a sibling
// or parent's type to decide whether to clone or create a new independent entity.

class Entity {
public:
    // Offsets from this:
    // +0x10: int m_status;          // 2 = default? 1/3 based on conditions
    // +0x14: int m_type;            // 3 or 4 (depends on interface bool)
    // +0x20: char m_name[0x30];     // copied from interface (null-terminated at +0x4f)
    // +0x50: int m_field50;
    // +0x54: int m_field54;
    // +0x58: bool m_isSibling;       // true if same parent type
    // +0x59: char m_field59;
    // +0x5c: int m_typeId;          // type ID from interface
};

// Interface that provides data for entity creation (abstract base)
class IEntityDataInterface {
public:
    virtual const char* getString() = 0;                // vtable+4
    virtual int getTypeId() = 0;                       // vtable+0xc
    virtual bool isSomeFlag() = 0;                     // vtable+0x18
};

// Class representing the parent context (e.g., EntityDataManager)
class EntityManager {
public:
    // +0x0c: IEntityDataInterface* (or a wrapper)
    IEntityDataInterface* getParentInterface();         // vtable+8 used in code
    // +0x378: int m_parentTypeId;   // -1 if none
    // +0x37c: uint m_flags;         // bit 2 for some flag
};

// Forward declarations of helper functions
IEntityDataInterface* getDataInterface(void* param2);   // FUN_00568340 wrapper
void* allocateMemory(size_t size);                     // FUN_009c8e50 (0x60)
void initializeEntityFields(Entity* entity);           // FUN_008a2dd0 (zeros some fields)
void setEntityParentFeatures(Entity* entity);          // FUN_00969880 (sets parent-specific fields)

// Actual function
Entity* EntityFactory::createEntity(EntityManager* manager, void* param2)
{
    IEntityDataInterface* dataInterface = getDataInterface(param2);
    
    // Allocate new entity memory
    Entity* newEntity = static_cast<Entity*>(allocateMemory(0x60));
    if (newEntity == nullptr) {
        return nullptr;
    }
    
    // Initialize basic fields to zero
    initializeEntityFields(newEntity);
    newEntity->m_field50 = 0;
    newEntity->m_field54 = 0;
    newEntity->m_isSibling = false;
    newEntity->m_field59 = '\0';
    newEntity->m_typeId = 0;
    
    // Get type ID from interface
    int typeId = dataInterface->getTypeId();            // vtable+0xc
    newEntity->m_typeId = typeId;
    
    // Compare type ID with parent's type (from manager's parent interface)
    IEntityDataInterface* parentInterface = nullptr;
    if (manager->getParentInterface()) {
        parentInterface = manager->getParentInterface();
    }
    int parentTypeId = (parentInterface != nullptr) ? parentInterface->getTypeId() : 0;
    
    if (newEntity->m_typeId == parentTypeId) {
        // Same type as parent: inherit some features (clone)
        setEntityParentFeatures(newEntity);
        
        int status = 2; // default
        if (((manager->m_flags >> 2) & 1) == 0 && manager->m_parentTypeId != -1 &&
            newEntity->m_type != 2) {
            status = (manager->m_parentTypeId != 0) ? 3 : 1; // actually 1 or 3, formula: (uint)(m_parentTypeId != 0) * 2 + 1
        }
        newEntity->m_status = status;
        return newEntity;
    }
    
    // Different type: copy name from interface
    const char* source = dataInterface->getString();    // vtable+4
    strncpy_s(newEntity->m_name, sizeof(newEntity->m_name), source, 0x30);
    newEntity->m_name[0x2f] = '\0';                     // ensure null termination (+0x4f)
    
    // Determine if this entity is a sibling (same parent type)
    bool isSibling = false;
    if (manager->getParentInterface() != nullptr) {
        int parentIfType = manager->getParentInterface()->getTypeId();
        isSibling = (dataInterface->getTypeId() == parentIfType);
    }
    newEntity->m_isSibling = isSibling;
    
    // Re-read type ID (redundant but present in original)
    newEntity->m_typeId = dataInterface->getTypeId();
    
    // Set type field based on interface bool (from vtable+0x18)
    bool specialFlag = dataInterface->isSomeFlag();
    newEntity->m_type = 4 - (specialFlag ? 1 : 0);      // 3 if flag true, else 4
    
    return newEntity;
}