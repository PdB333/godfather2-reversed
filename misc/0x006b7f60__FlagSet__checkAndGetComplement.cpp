//FUNC_NAME: FlagSet::checkAndGetComplement

// Function at 0x006b7f60
// Checks if all bits in requestedFlags are set in m_requiredFlags (offset +0x14).
// If not, returns requestedFlags with low byte cleared (error indicator).
// If yes, computes complement = ~requestedFlags & m_availableFlags (offset +0x18).
// Returns a value where the low byte is 1 if complement == m_availableFlags (i.e., no overlap),
// and the upper 24 bits are the high 24 bits of complement.

uint __thiscall FlagSet::checkAndGetComplement(uint requestedFlags)
{
    uint complement;

    // Check if all required flags are present
    if ((m_requiredFlags & requestedFlags) != m_requiredFlags) {
        // Not all required flags set; return error with low byte cleared
        return requestedFlags & 0xffffff00;
    }

    // Compute flags in m_availableFlags that are not in requestedFlags
    complement = ~requestedFlags & m_availableFlags;

    // Return: upper 24 bits = complement >> 8, low byte = (complement == m_availableFlags)
    return ((complement >> 8) << 8) | (complement == m_availableFlags);
}