// FUNC_NAME: Entity::Entity
void __thiscall Entity::Entity(Entity *this)
{
    // Set base vtable at +0x00
    *(void**)this = (void*)0x00d5eb60;
    // Set vtable for first interface at +0x3C (0x0F * 4)
    *(void**)((char*)this + 0x3C) = (void*)0x00d5eb50;
    // Set vtable for second interface at +0x48 (0x12 * 4)
    *(void**)((char*)this + 0x48) = (void*)0x00d5eb4c;

    // Construct sub-object at +0x58 (0x16 * 4)
    SUBOBJECT_CONSTRUCTOR(this + 0x16);
    // Reset three consecutive sub-objects at +0x58, +0x60, +0x68
    SUBOBJECT_RESET(this + 0x16);
    SUBOBJECT_RESET(this + 0x18);
    SUBOBJECT_RESET(this + 0x1A);

    // Global one-time initialization
    GLOBAL_INIT();
}