// FUNC_NAME: Entity::Entity
// Function address: 0x008805e0
// Role: Constructor for Entity base class. Sets vtable and calls initialization functions.

void __thiscall Entity::Entity(Entity *this)
{
    // Set vtable pointer to the class's vtable
    this->vtable = (void**)&PTR_FUN_00d76ad4;
    // Call base class initialization
    this->initBase();
    // Call member initialization
    this->initMembers();
}