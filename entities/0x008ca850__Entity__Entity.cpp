// FUNC_NAME: Entity::Entity
class Entity {
public:
    Entity(unsigned int param2, unsigned int param3);
    // +0x00: vtable pointer (set to 0x00d7bfd8)
};

Entity::Entity(unsigned int param2, unsigned int param3)
{
    // Call base initialization or common constructor
    FUN_008cc760(param2, param3);
    // Set vtable pointer to this class's vtable
    this->vtable = (int*)&PTR_FUN_00d7bfd8; // +0x00
    return this;
}