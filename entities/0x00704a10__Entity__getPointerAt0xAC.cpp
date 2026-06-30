// FUNC_NAME: Entity::getPointerAt0xAC
int __thiscall Entity::getPointerAt0xAC()
{
    // +0xAC: pointer to a component or substructure (likely a SimManager, crew component, or state machine)
    return *(int *)((char*)this + 0xAC);
}