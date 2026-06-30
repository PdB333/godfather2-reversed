// FUNC_NAME: EARS::Object::getObjectType
// Address: 0x006252f0
// Returns the 32-bit object type identifier stored at offset +0x4 from the object base.
uint32_t __thiscall EARS::Object::getObjectType(EARS::Object* this)
{
    return *(uint32_t*)((uint8_t*)this + 4);
}