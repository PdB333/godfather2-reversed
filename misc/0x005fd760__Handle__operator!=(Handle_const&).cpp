// FUNC_NAME: Handle::operator!=(Handle const&)
// Function address: 0x005fd760
// Role: Inequality comparison for a handle structure.
// Structure fields: 
//   +0x00: m_type (int) - type identifier (0 = null/invalid)
//   +0x04: unknown (int) - not used in comparison
//   +0x08: m_id (int) - resource/index ID, only compared when m_type != 0

bool __thiscall Handle::operator!=(Handle const& other) const
{
    // Two handles are considered equal if:
    // - Their type fields match, AND
    // - Either both types are zero (null handles) OR their ID fields match.
    // The function returns true if they are NOT equal.
    bool isEqual = false;

    if ((m_type == other.m_type) &&
        ((m_type == 0) || (m_id == other.m_id))) {
        isEqual = true;
    }

    return !isEqual;
}