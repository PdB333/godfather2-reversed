// FUNC_NAME: AIComponent::setState
// Function address: 0x00549ac0
// Role: Sets a byte field at offset 0x11 in the sub-object pointed to by this+0x18

void __thiscall AIComponent::setState(int this, uint8_t state)
{
    // Write state byte to sub-object at this+0x18, offset 0x11
    *(uint8_t*)(*(int*)(this + 0x18) + 0x11) = state;
}