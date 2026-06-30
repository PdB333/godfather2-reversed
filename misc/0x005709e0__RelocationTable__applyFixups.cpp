// FUNC_NAME: RelocationTable::applyFixups
// Address: 0x005709e0
// Role: Applies base relocation fixups by adding the object base address to relative offsets stored in a null-terminated table.
// The first integer at `this` is a relative offset to the table. The table contains a zero-terminated list of offsets (relative to `this`)
// that point to fields containing relative pointers needing base adjustment. After fixup, the table's first entry is cleared.

struct RelocationTable {
    int offsetToTable; // +0x00: offset from this to start of relocation entry list
};

int RelocationTable::applyFixups() {
    // Compute table base as this + offsetToTable
    int* table = reinterpret_cast<int*>(offsetToTable + reinterpret_cast<int>(this));

    // Iterate over null-terminated list of relocation offsets (relative to this)
    for (int* entry = table; *entry != 0; ++entry) {
        // Offset of the field to fix (relative to this)
        int fieldOffset = *entry;
        // Pointer to the field containing the relative value
        int* fieldPtr = reinterpret_cast<int*>(fieldOffset + reinterpret_cast<int>(this));
        // Add base address to the field's value to make it absolute
        *fieldPtr += reinterpret_cast<int>(this);
    }

    // Zero out first entry (4 bytes) as a flag indicating fixups have been applied
    unsigned char* tableBytes = reinterpret_cast<unsigned char*>(table);
    tableBytes[0] = 0;
    tableBytes[1] = 0;
    tableBytes[2] = 0;
    tableBytes[3] = 0;

    return 1;
}