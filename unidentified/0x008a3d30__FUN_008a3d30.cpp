// FUNC_NAME: UnknownClass::setFlagBit10
// Function address: 0x008a3d30
// Role: Sets or clears bit 10 (0x400) in the flags field at offset 0x37c.
// This is a simple setter for a boolean flag, likely part of a bitfield.

void __thiscall UnknownClass::setFlagBit10(bool enable)
{
    uint* flags = reinterpret_cast<uint*>(reinterpret_cast<uintptr_t>(this) + 0x37c);
    if (enable)
    {
        *flags |= 0x400; // Set bit 10
    }
    else
    {
        *flags &= ~0x400; // Clear bit 10
    }
}