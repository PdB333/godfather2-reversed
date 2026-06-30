// FUNC_NAME: Entity::setCustomData
// Function at 0x006b3c40: Setter for a sub-object (offset +0x84) with a 4-byte value.
void __thiscall Entity::setCustomData(Entity* thisPtr, uint32_t value)
{
    // Call the inner function that operates on the sub-object at offset 0x84
    // FUN_006b3b60 likely performs assignment or initialization on that sub-object
    FUN_006b3b60(/* subObject */ (int)(thisPtr) + 0x84, value);
}