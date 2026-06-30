// FUNC_NAME: EARS::Framework::Object::initCommon
// Address: 0x0059cae0
// This function initializes common fields for an EARS framework object.
// It sets flags, clears a short field, and writes a magic signature.

void __thiscall EARS::Framework::Object::initCommon(void)
{
    // Assume 'this' pointer is in ECX (passed via EDI in decompiler).
    // Offsets relative to this pointer:
    // +0x00: uint32 m_flags (bitfield)
    // +0x02: uint16 m_unknownShort
    // +0x08: uint32 m_magicSignature

    uint32* flags = (uint32*)this;           // this->m_flags
    uint16* unknownShort = (uint16*)((char*)this + 2); // this->m_unknownShort

    // Clear bits 1-14, set bit 0 (likely enables something)
    *flags = (*flags & 0xFFFF8001) | 0x1;
    // Clear the short at offset 2
    *unknownShort = 0;
    // Set bit 15 in flags (enable another feature)
    *flags |= 0x8000;

    // Call another initialization routine
    FUN_005a0a80();

    // Write a magic signature for object identification (0xBE EF CE EC)
    *(uint32*)((char*)this + 0x20) = 0xBEEFCEEC;
}