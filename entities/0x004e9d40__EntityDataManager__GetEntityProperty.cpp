// FUNC_NAME: EntityDataManager::GetEntityProperty
int EntityDataManager::GetEntityProperty(uint index)
{
    // Global initialization flag (DAT_010c265c)
    static int s_initFlag = -1;
    // Global manager pointer (DAT_012233a0)
    static ManagerStruct* s_manager = reinterpret_cast<ManagerStruct*>(0x012233a0);

    // Check if system is initialized and index is valid
    if (s_initFlag == -1 && static_cast<int>(index) >= 0 && index < s_manager->count)
    {
        // Get entity pointer from array at offset +0x4
        EntityBase* entity = s_manager->entityArray[index];
        if (entity != nullptr)
        {
            // Call virtual function at vtable+0x0C (likely returns an object)
            SomeObject* obj = reinterpret_cast<SomeObject*>(entity->GetSomeObject());
            if (obj != nullptr)
            {
                // Call virtual function at vtable+0x58 (returns int property)
                return obj->GetProperty();
            }
        }
    }
    // Return initialization flag (usually -1 if not initialized)
    return s_initFlag;
}

// Structure definitions (offsets relative to base)
struct ManagerStruct
{
    /* +0x00 */ int unknown0;
    /* +0x04 */ EntityBase** entityArray;  // array of pointers
    /* +0x08 */ int unknown8;
    /* +0x0C */ uint count;                // number of entities
};

struct EntityBase
{
    /* +0x00 */ void** vtable;
    // Virtual function at vtable+0x0C: returns SomeObject*
    // Virtual function at vtable+0x58: returns int (property)
};

struct SomeObject
{
    /* +0x00 */ void** vtable;
    // Virtual function at vtable+0x58: returns int
};