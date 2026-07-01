// FUNC_NAME: Entity::Entity

class Entity {
    // Constructor (FUN_008deae0)
    Entity* __thiscall constructor(Entity* this, int param);
};

Entity* __thiscall Entity::constructor(Entity* this, int param) {
    // Call base class constructor with the provided parameter
    this->baseConstructor(param); // FUN_008ded10

    // Set primary virtual function table pointer (offset +0x00)
    this->vtable = &PTR_FUN_00d7f1c0;

    // Set secondary vtable pointers for multiple inheritance / interfaces
    this->vtableA = &PTR_LAB_00d7f1b0;   // +0x3C
    this->vtableB = &PTR_LAB_00d7f1ac;   // +0x48
    this->vtableC = &PTR_LAB_00d7f1a8;   // +0x50
    this->vtableD = &PTR_LAB_00d7f148;   // +0x54
    this->vtableE = &PTR_LAB_00d7f0e0;   // +0x58

    // Initialize additional member fields
    this->field_0x210 = 0;            // +0x84 (four bytes)
    this->field_0x214 = -1;           // +0x85 (four bytes)

    return this;
}