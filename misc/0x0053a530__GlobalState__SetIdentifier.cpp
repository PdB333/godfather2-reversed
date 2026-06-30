// FUNC_NAME: GlobalState::SetIdentifier
void GlobalState::SetIdentifier(uint8_t (*identifier)[16]) // identifier is a pointer to 32 bytes (two 16-byte arrays)
{
    // Copy 32 bytes from identifier to global state arrays
    if (identifier == (uint8_t (*)[16])0) {
        // Clear the stored identifier
        _DAT_0121b950 = (uint8_t [16]){0};
        _DAT_0121b960 = (uint8_t [16]){0};
    } else {
        _DAT_0121b950 = identifier[0];
        _DAT_0121b960 = identifier[1];
    }

    // Conditionally copy 8 bytes from a cached source if certain state matches
    // DAT_012058e8 likely points to a structure, DAT_0121b740 is its base, DAT_0121bbcc is a length/offset
    if ((DAT_012058e8 == &DAT_0121b740) && (DAT_0121b754 == DAT_0121bbcc)) {
        // Copy 8 bytes from the cached source (DAT_0121bb90) to the identifier (starting at _DAT_0121b950)
        FUN_0060ab00(DAT_0121bbcc, DAT_0121bb90, &_DAT_0121b950, 8);
    }
}