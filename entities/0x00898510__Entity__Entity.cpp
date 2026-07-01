//FUNC_NAME: Entity::Entity
Entity* __thiscall Entity::Entity(Entity* this, int initParam)
{
    // Call base class constructor (likely EARS::Framework::Object or similar)
    BaseClassConstructor(initParam);
    
    // Set primary vtable pointer for this class
    this->vtable = (void*)&PTR_FUN_00d77b78;
    
    // Set secondary vtable pointers for multiple inheritance / interfaces
    this->field_0x3C = &PTR_LAB_00d77b68; // +0x3C (offset 0x0F * 4)
    this->field_0x48 = &PTR_LAB_00d77b64; // +0x48 (offset 0x12 * 4)
    this->field_0x50 = &PTR_LAB_00d77b00; // +0x50 (offset 0x14 * 4)
    
    return this;
}