// FUNC_NAME: KeyPair::compareTo

int __thiscall KeyPair::compareTo(const KeyPair* other) const
{
    // Assert that this->first is non-zero and matches other->first
    if (first == 0 || first != other->first)
    {
        assertionFailed(); // FUN_00b97aea - likely an assertion/error handler
    }
    // Return a combined value: high 24 bits are (second >> 8), low 8 bits indicate equality of second
    return ((second >> 8) & 0xFFFFFF) << 8 | (second == other->second ? 1 : 0);
}