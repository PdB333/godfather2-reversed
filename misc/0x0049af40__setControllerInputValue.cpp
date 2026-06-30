// FUNC_NAME: setControllerInputValue
// Function at 0x0049af40: Writes a 4-byte value into the first field of a controller input structure (8 bytes each) indexed by slot.
// Global array at DAT_0110a4b8 likely holds ControllerInput structures for each controller slot.
void setControllerInputValue(int slotIndex, uint32_t* valuePtr)
{
    // Each structure is 8 bytes; write the first field (offset 0)
    *(uint32_t*)((uint8_t*)0x0110a4b8 + slotIndex * 8) = *valuePtr;
}