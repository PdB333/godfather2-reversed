// FUNC_NAME: SomeClass::getMatchStatus
// Function at 0x007012f0
// Returns a 32-bit value: high 24 bits are (m_field0x328 & 0xFFFFFF00), low bit indicates whether m_field0x328 == m_field0x32c.
// Used as a status check comparing two fields for equality while preserving the upper bits of the first field.
//
// Fields:
// +0x328: likely an identifier, state, or sequence number
// +0x32c: expected value to compare against

int __fastcall SomeClass::getMatchStatus(void) const
{
    int field0x328 = *(int *)((uint)this + 0x328);
    int field0x32c = *(int *)((uint)this + 0x32c);
    return (field0x328 & 0xFFFFFF00) | (field0x328 == field0x32c);
}