// FUNC_NAME: GameObject::setFlagBit4
// Function address: 0x004a56e0
// Sets bit 4 (0x10) in the 16-bit flags field at offset +0x80.
// This likely marks the object as needing an update or similar action.
void __thiscall GameObject::setFlagBit4()
{
    // Set bit 4 (0x10) in the 16-bit flags at offset +0x80
    *(uint16_t*)((uintptr_t)this + 0x80) |= 0x10;
}