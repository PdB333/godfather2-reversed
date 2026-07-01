// FUNC_NAME: Entity::iterateComponents
void __thiscall Entity::iterateComponents(void *this, uint param_2)
{
    // +0x9c: pointer to array of component pointers (Component**)
    // +0xa0: count of components (int)
    int componentCount = *(int *)((char *)this + 0xa0);
    for (int i = componentCount - 1; i >= 0; --i)
    {
        Component *component = *(Component **)(*(int *)((char *)this + 0x9c) + i * 4);
        // Calls a function on each component, passing the entity and the parameter
        FUN_008c3a10(component, this, param_2);
    }
}