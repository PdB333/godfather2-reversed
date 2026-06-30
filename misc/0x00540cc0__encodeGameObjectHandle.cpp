// FUNC_NAME: encodeGameObjectHandle
// Function at 0x540cc0 converts an input (likely an index or ID) into an object handle by setting bit 30 and shifting right by 2.
// Used extensively throughout the game for handle encoding (e.g., for objects, entities, network IDs).
uint encodeGameObjectHandle(uint inputId)
{
    // Shift right by 2 to align, then set the 0x40000000 flag (bit 30) identifying this as a valid handle.
    return (inputId >> 2) | 0x40000000;
}