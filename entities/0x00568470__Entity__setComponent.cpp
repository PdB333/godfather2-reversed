// FUNC_NAME: Entity::setComponent
// Address: 0x00568470
// Stores a component pointer at +0x34, calls its second vtable function (init/attach) with this,
// and releases previous component(s) if +0x28 or +0x2c are non-null.
void __thiscall Entity::setComponent(void* this, void* component) // param_2 = component interface
{
    // Store component pointer at offset 0x34
    *(void**)((uint32_t)this + 0x34) = component;

    // Call vtable[1] (offset 4) on the component, passing this (the entity) as argument
    // This is typically an attach/initialize method like "setOwner" or "attachTo"
    void** vtable = *(void***)component;
    ((void (*)(void*))vtable[1])(this);

    // If old component references exist at +0x28 or +0x2c, release them
    if (*(uint32_t*)((uint32_t)this + 0x28) != 0 || *(uint32_t*)((uint32_t)this + 0x2c) != 0) {
        // Cleanup old component(s)
        FUN_00568410(0, 0); // likely a release/detach function
    }
}