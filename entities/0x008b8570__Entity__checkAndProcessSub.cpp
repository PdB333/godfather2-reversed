// FUNC_NAME: Entity::checkAndProcessSub
uint __fastcall Entity::checkAndProcessSub(Entity* this)
{
    // Virtual call at vtable +0xC0: returns a float (e.g., some timer, health, or progress).
    // The bitwise representation of the float is also captured as an integer (uVar1 in decompiler).
    float value = this->vptr->getValue(); // offset 0xC0
    uint result = *(uint*)&value; // treat float bits as integer for the mask

    // Check if the float value is positive and the sub-component at offset 0x210 exists.
    // +0x84 in param_1 (this) = 0x84 * 4 = 0x210 bytes offset.
    if (value > 0.0f && this->componentPtr != nullptr) // componentPtr stored at 0x210
    {
        // Virtual call at vtable +0x1C on the sub-component.
        result = this->componentPtr->vptr->execute(); // offset 0x1C
    }

    // Mask off the low byte (bits 7-0) of the result.
    // This could be clearing a flag, status bits, or error code.
    return result & 0xFFFFFF00;
}