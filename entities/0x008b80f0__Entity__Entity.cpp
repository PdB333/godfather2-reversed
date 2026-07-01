// FUNC_NAME: Entity::Entity
// Constructor for Entity class at 0x008b80f0.
// Initializes vtable, zeros fields, and stores a reference to the global entity data manager.

void __fastcall Entity::Entity(Entity* this)
{
    // Global pointer to EntityDataManager (or similar)
    void* entityDataManager = *(void**)0x00d5780c;

    // Set vtable pointer (offset +0x00)
    this->vtable = (void**)&PTR_LAB_00d7b410;

    // Initialize fields
    this->field_0x04 = 0; // +0x04
    this->field_0x08 = 0; // +0x08
    this->field_0x0C = entityDataManager; // +0x0C, store reference
    this->field_0x10 = 0; // +0x10
    this->field_0x14 = 0; // +0x14
    this->field_0x18 = 0; // +0x18
    this->field_0x1C = 0; // +0x1C
}