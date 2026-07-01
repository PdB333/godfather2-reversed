// FUNC_NAME: Entity::Entity
void __thiscall Entity::Entity(Entity* this) {
    // Set primary vtable pointer (likely for Entity base class)
    *this = &PTR_FUN_00d6ff90;

    // Secondary vtable pointers for multiple inheritance or interfaces
    // +0x3C (0xF * 4)
    this->interfaceVtable1 = &PTR_LAB_00d6ff80;
    // +0x48 (0x12 * 4)
    this->interfaceVtable2 = &PTR_LAB_00d6ff7c;

    // Initialize subobject at offset +0x50 (0x14 * 4)
    // This is likely a member object of another class (e.g., TNLConnection or NetObject)
    subobjectConstructor(&this->subObject);  // FUN_004086d0
    subobjectInitialize(&this->subObject);   // FUN_00408310

    // Global initialization call (possibly setting up static data)
    globalInitializer();  // FUN_0046c640
}