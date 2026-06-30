// FUNC_NAME: copyPartialData
void copyPartialData(uint32_t *this, uint32_t *source) {
    this[0] = source[0];
    this[1] = source[1];
    this[2] = source[2];
    this[3] = source[3];
    this[4] = source[4];
    // Skip fields at indices 5, 6, 7 (e.g., padding or unrelated data)
    this[8] = source[8];
    this[9] = source[9];
    this[10] = source[10];
    this[11] = source[11];
    this[12] = source[12];
    this[13] = source[13];
    this[14] = source[14];
    this[15] = source[15];
    this[16] = source[16];
    this[17] = source[17];
    this[18] = source[18];
    this[19] = source[19];
}