// FUNC_NAME: SomeObject::setBoolFlag
// Address: 0x00509020
// Sets or clears bit 0 of the flags field at offset +0x8 based on enable flag.
void __thiscall SomeObject::setBoolFlag(char enable)
{
    uint32_t* flags = (uint32_t*)(this + 0x8);
    if (enable != '\0') {
        *flags |= 1;
    } else {
        *flags &= ~1;
    }
}