// FUNC_NAME: SomeClass::setSomeMember
void __thiscall setSomeMember(void* this, int32_t value)
{
    *(int32_t*)((uint8_t*)this + 0x68) = value;
}