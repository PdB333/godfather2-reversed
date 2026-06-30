// FUNC_NAME: FlaggedDataPair::FlaggedDataPair
void __thiscall FlaggedDataPair::FlaggedDataPair(int* this, int param1, int param2) {
    // Offset 0x00: Field0 = param1
    this[0] = param1;
    // Offset 0x04: Field4 = param2
    this[1] = param2;
    // Offset 0x08 to 0x14: Zero out fields 2-5
    this[2] = 0;
    this[3] = 0;
    this[4] = 0;
    this[5] = 0;
    // Offset 0x18: Byte flag set to 1 (active/valid)
    *(char*)(this + 6) = 1;
    // Offset 0x1C: Field7 set to 0
    this[7] = 0;
}