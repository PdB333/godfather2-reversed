// FUNC_NAME: BaseObject::setField
// Takes a pointer to a 32-bit field and sets it to the given value.
// This is a simple setter, likely used by many subclasses.
// Function address: 0x004b7f30
void __thiscall BaseObject::setField(uint32_t* this, uint32_t value)
{
    *this = value;
}