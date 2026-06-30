// FUNC_NAME: EARSObject::get64BitId
// Address: 0x0051d730
// Returns a 64-bit identifier based on object type and fields.
// This is used in various engine subsystems (timestamps, sorting, ghost IDs).
// The object layout (assuming __thiscall, this in ECX):
//   +0x00: uint32_t m_type   (type discriminator)
//   +0x04: uint32_t m_idLow  (low 32 bits of identifier)
//   +0x08: uint32_t m_idHigh (high 32 bits of identifier, only lower 16 bits used in most cases)

uint64_t EARSObject::get64BitId()
{
    uint32_t type = this->m_type;
    uint32_t highPart = 0;
    uint32_t lowPart = 0;

    switch (type)
    {
    case 0:
        return 0; // Invalid / null object

    case 3:
        highPart = 0x10000; // Flag bit set in high part for this type
        // Fall through to cases 1,2,4

    case 1:
    case 2:
    case 4:
        // Combined 64-bit: high = (highPart | (m_idHigh & 0xFFFF)), low = m_idLow
        return ((uint64_t)(highPart | (this->m_idHigh & 0xFFFF)) << 32) | (uint64_t)(this->m_idLow);

    case 5:
        lowPart = this->m_idLow; // Fall through to default

    default:
        return (uint64_t)lowPart; // For type 5 returns m_idLow, for others returns 0

    case 7:
        return 0x8000000000000000ULL; // Special sentinel (negative if signed)
    }
}