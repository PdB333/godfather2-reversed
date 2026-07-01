// FUNC_NAME: Entity::Entity
void __thiscall Entity::Entity(Entity *this) {
    // Set vtable pointer (offset +0x00)
    *reinterpret_cast<void**>(this) = reinterpret_cast<void*>(0x00d825c0); // PTR_FUN_00d825c0
    // Set member at offset 0x214 (param_1[0x85] = 0x85 * 4)
    *reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 0x214) = reinterpret_cast<void*>(0x00d825b0); // PTR_LAB_00d825b0
    // Call base class constructor or initialization
    FUN_004083d0(); // likely Entity::baseInit or similar
    FUN_004c2a80(); // likely another base component init
}