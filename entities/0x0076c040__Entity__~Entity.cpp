// FUNC_NAME: Entity::~Entity
void __thiscall Entity::~Entity(Entity* this)
{
    // Set vtable for most derived destructor
    this->vtable = &PTR_LAB_00d66080;
    // Call static cleanup routine (argument 0 indicates no special context)
    staticCleanup(0);
    // Clear bit 22 (0x400000) in flags field at offset +0x1F58 of a nested structure.
    // The nested structure pointer is at offset +0x5C from this.
    *(uint*)(this->field_0x5C + 0x1F58) &= 0xFFBFFFFF;
    // Switch vtable to base class vtable for destruction chain
    this->vtable = &PTR_LAB_00d63090;
    // Destroy subobject at offset 0x68 if it exists
    if (this->field_0x68 != 0) {
        destroySubobject(this + 0x68);
    }
    // Invoke base class destructor
    Base::~Base();
}