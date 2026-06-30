// FUNC_NAME: Entity::Entity
void __fastcall Entity::Entity(Entity *this)
{
    // Set three vtable pointers for multiple inheritance (EARS framework)
    this->vfptr = (void**)&PTR_FUN_00d5e618;             // +0x00: primary vtable
    this->vfptr2 = (void**)&PTR_LAB_00d5e608;            // +0x3C: secondary vtable
    this->vfptr3 = (void**)&PTR_LAB_00d5e604;            // +0x48: tertiary vtable

    // Initialize sub-object at offset 0x64 (likely a component or base)
    sub_4086d0((Component*)((uint8_t*)this + 0x64));     // component constructor
    sub_408310((Component*)((uint8_t*)this + 0x64));     // component post‑init

    // Global engine initialization (one‑time per module)
    GameEngine::Init();
}