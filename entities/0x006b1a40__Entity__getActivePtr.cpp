// FUNC_NAME: Entity::getActivePtr
void* __thiscall Entity::getActivePtr()
{
    void* ptr = *(void**)(this + 0xCC); // +0xCC: pointer to active component/action
    if (*(int*)(this + 0x16C) != 0) {   // +0x16C: flag indicating destruction or invalidity
        ptr = nullptr;
    }
    return ptr;
}