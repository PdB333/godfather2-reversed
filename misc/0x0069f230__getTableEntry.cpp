// FUNC_NAME: getTableEntry
uint getTableEntry(int index, int row)
{
    row = row * 0x14;
    if (index == 0) {
        return (uint)(byte)(&DAT_00e50bd0)[row];
    }
    if (index == 1) {
        return (uint)(byte)(&DAT_00e50bd1)[row];
    }
    if (index == 2) {
        return (uint)(byte)(&DAT_00e50bd2)[row];
    }
    if (index == 3) {
        return (uint)(byte)(&DAT_00e50bd3)[row];
    }
    if (index == 4) {
        return (uint)(byte)(&DAT_00e50bd4)[row];
    }
    if (index == 5) {
        return (uint)(byte)(&DAT_00e50bd5)[row];
    }
    if (index == 6) {
        return (uint)(byte)(&DAT_00e50bd6)[row];
    }
    if (index == 7) {
        return (uint)(byte)(&DAT_00e50bd7)[row];
    }
    if (index == 8) {
        return (uint)(byte)(&DAT_00e50bd8)[row];
    }
    if (index == 9) {
        return (uint)(byte)(&DAT_00e50bd9)[row];
    }
    if (index == 10) {
        return *(uint *)(&DAT_00e50bdc + row);
    }
    if (index == 0xb) {
        return *(uint *)(&DAT_00e50be0 + row);
    }
    return 0;
}