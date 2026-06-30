// FUNC_NAME: Object::isActive
bool __fastcall Object::isActive(Object* this)
{
    // Check if both the vtable pointer (offset 0x00) and the component pointer (offset 0x08) are non-null
    if (this->vtable != 0 && this->componentPtr != 0)
    {
        return true;
    }
    return false;
}