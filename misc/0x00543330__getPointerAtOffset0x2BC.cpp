// FUNC_NAME: getPointerAtOffset0x2BC
// 0x00543330: Returns the pointer stored at offset 0x2BC (700) in the given object.
// This is likely a getter for a component or sub-object (e.g., AI component, state machine).
uint32_t __fastcall getPointerAtOffset0x2BC(void* thisPtr)
{
    return *(uint32_t*)((uint8_t*)thisPtr + 0x2BC);
}