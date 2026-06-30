// FUNC_NAME: Entity::setComponentValue
void __fastcall Entity::setComponentValue(int value)
{
    int* component = *(int**)((char*)this + 0xc0);  // +0xc0: pointer to internal component
    *(int*)((char*)component + 0x10) = value;         // +0x10: target field in component (e.g., state, ID)
}