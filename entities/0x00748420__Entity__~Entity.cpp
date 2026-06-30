// FUNC_NAME: Entity::~Entity
void __fastcall Entity::destructor(Entity* this)
{
    // Restore vtable pointer to base class (vtable table at PTR_LAB_00d6415c)
    this->vtable = (void**)&PTR_LAB_00d6415c;

    // Call base class destructor (likely Entity::destroyBase)
    Entity::destroyBase();

    // +0x58: pointer to dynamically allocated memory (e.g., a sub-object or data block)
    if (*((void**)this + 0x16) != nullptr) {
        // Delete the pointed-to object and nullify the pointer
        deleteAndNullify((void**)((int*)this + 0x16));
    }

    // Release any remaining resources (e.g., handles, references)
    Entity::releaseResources();

    return;
}