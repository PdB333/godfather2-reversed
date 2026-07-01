// FUNC_NAME: UnknownClass::getFieldAt0x80
int __fastcall UnknownClass::getFieldAt0x80() const
{
    // Returns the address of the field at offset 0x80 from this object.
    return reinterpret_cast<int>(this) + 0x80;
}