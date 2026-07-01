// FUNC_NAME: Entity::Entity
// Address: 0x0082a400
// Constructor for Entity. Initializes main vtable and secondary vtable (likely for an interface or component), then calls base class constructor and additional initialization.

void __thiscall Entity::Entity(Entity* this) {
    // Set primary vtable at offset 0x0
    *(void***)this = (void**)&PTR_FUN_00d73790;
    // Call base class constructor (probably at 0x0082a3c0)
    FUN_0082a3c0();
    // Set secondary vtable at offset 0xC (interface/component vtable)
    *(void***)((char*)this + 0xC) = (void**)&PTR_LAB_00e32854;
    // Additional initialization (likely at 0x00821f60)
    FUN_00821f60();
}