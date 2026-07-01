// FUNC_NAME: ComponentBase::initSubobjects
void __thiscall ComponentBase::initSubobjects(uint32_t param)
{
    // Initialize first subobject at offset 0x10 with the passed parameter
    subobjectInit(param, reinterpret_cast<char*>(this) + 0x10);
    // Initialize second subobject at offset 0x18 with default
    subobjectDefaultInit(reinterpret_cast<char*>(this) + 0x18);
}