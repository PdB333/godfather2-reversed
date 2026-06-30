// FUNC_NAME: UnknownClass::initFields
// Function at 0x005e4220: Initializes a structure with two parameters, zeros out other fields, and sets a flag to 1.
// Structure layout (based on offsets):
//   +0x00: field0 (int)
//   +0x04: field1 (int)
//   +0x08: field2 (int)
//   +0x0C: field3 (int)
//   +0x10: field4 (int)
//   +0x14: field5 (int)
//   +0x18: flagByte (char) — set to 1
//   +0x1C: field7 (int) — set to 0

class UnknownClass {
public:
    int field0;
    int field1;
    int field2;
    int field3;
    int field4;
    int field5;
    char flagByte;
    // implicit 3-byte padding for alignment
    int field7;

    void __thiscall initFields(int param1, int param2) {
        field0 = param1;
        field1 = param2;
        field2 = 0;
        field3 = 0;
        field4 = 0;
        field5 = 0;
        flagByte = 1;
        field7 = 0;
    }
};