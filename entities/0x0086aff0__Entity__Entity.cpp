//FUNC_NAME: Entity::Entity
// Function address: 0x0086aff0
// Role: Constructor for Entity class – sets vtable pointer and calls base class constructor

void __fastcall Entity::Entity(Entity* this)
{
    // Set vtable pointer (offset +0x00) to the Entity vtable
    this->vtable = (void**)&PTR_LAB_00d75d0c;
    // Call base class (EARSObject) constructor
    EARSObject::EARSObject();
}