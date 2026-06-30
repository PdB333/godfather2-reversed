// FUNC_NAME: FourIntStruct::operator==
// Function at 0x00420950: Compares two 16-byte (4 int) structures for equality.
// Offsets: +0x00 = int[0], +0x04 = int[1], +0x08 = int[2], +0x0C = int[3]
bool __thiscall FourIntStruct::operator==(const FourIntStruct& other) const
{
    return (data[0] == other.data[0] &&
            data[1] == other.data[1] &&
            data[2] == other.data[2] &&
            data[3] == other.data[3]);
}