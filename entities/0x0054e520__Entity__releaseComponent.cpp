// FUNC_NAME: Entity::releaseComponent
void __fastcall Entity::releaseComponent(void* this)
{
    // Offset +0x1c holds a pointer to a sub-object (component) that needs to be released.
    // The release function is at 0x0054e3d0 (likely IComponent::release or similar).
    ((void (__thiscall *)(void *))0x0054e3d0)(*(void **)((char *)this + 0x1c));
}