// FUNC_NAME: SomeComponent::setDirtyFlag
void SomeComponent::setDirtyFlag(int *self)
{
    // Check primary flag and sub-object pointer
    if ((self[0] != 0) && (self[2] != 0)) {
        // Set bit 0 of byte at offset 0x21 in sub-object
        byte *bytePtr = (byte *)(self[2] + 0x21);
        *bytePtr |= 1;
    }
    return;
}