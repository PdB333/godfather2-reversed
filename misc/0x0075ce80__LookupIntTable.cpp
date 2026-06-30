// FUNC_NAME: LookupIntTable
// Address: 0x0075ce80
// Purpose: Accesses a 2D int32 array with 8 columns (base at 0x00e51980).
// Returns value at [row][col] where col must be 0..7.
int32_t LookupIntTable(int32_t row, int32_t col) {
    // Base of 2D array: each row is 8 int32s (32 bytes)
    static const int32_t* base = reinterpret_cast<int32_t*>(0x00e51980);
    // Offset: (col + row * 8) * sizeof(int32_t) = (col + row * 8) * 4
    return base[col + row * 8];
}