// FUNC_NAME: SimObject::activate
// Function address: 0x008cab30
// Sets activation flag and potentially calls additional initialization routines

void __thiscall SimObject::activate(void)
{
    // Set bit 0 of flags at offset +0x14 (m_flags)
    *(byte *)(this + 0x14) = *(byte *)(this + 0x14) | 1;

    // Call common activation function
    FUN_004b6140();

    // If bit 1 (0x2) is set, perform secondary initialization
    if ((*(byte *)(this + 0x14) & 2) != 0) {
        FUN_004b6330();
    }
}