// FUNC_NAME: SomeClass::setBooleanProperty
void __thiscall SomeClass::setBooleanProperty(uint propertyHash, bool value)
{
    if (propertyHash == 0x2c2eae66) {
        if (value) {
            // Set bit 0 of flags at offset 0x31
            *(byte *)(this + 0x31) = *(byte *)(this + 0x31) | 1;
        } else {
            // Clear bit 0
            *(byte *)(this + 0x31) = *(byte *)(this + 0x31) & 0xfe;
        }
    }
    // If hash doesn't match, do nothing
}