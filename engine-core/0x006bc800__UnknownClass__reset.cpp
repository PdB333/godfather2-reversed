// FUNC_NAME: UnknownClass::reset
// Function at 0x006bc800: likely a reset/cleanup method that releases a resource and zeroes members.
void __fastcall UnknownClass::reset(UnknownClass* this) // __fastcall with this in ecx
{
    // Free the resource pointed to by m_pResource (offset 0x00)
    FUN_009c8f10(this->m_pResource); // Likely a release/deallocation function
    // Reset all members to their default values
    this->m_pResource = NULL;         // +0x00
    this->field_0x04 = 0;             // +0x04
    this->field_0x08 = 0;             // +0x08
}