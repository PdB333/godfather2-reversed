// FUNC_NAME: Entity::Entity
// Function address: 0x00604000
// Constructor for the base Entity class. Calls the parent class constructor and then initializes entity-specific data.
void __thiscall Entity::Entity(void* this, void* entityInitData, void* extraData)
{
    // Call base class constructor (likely EARSObject or similar)
    FUN_00603d30(this, entityInitData, extraData);
    // Perform entity-specific initialization (e.g., setup from data)
    FUN_00604060(entityInitData);
}