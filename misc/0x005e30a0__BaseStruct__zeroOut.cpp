// FUNC_NAME: BaseStruct::zeroOut
// Function address: 0x005e30a0
// Role: Zeros out 8 consecutive 32-bit fields (32 bytes). Likely a constructor or reset method.
// Assignment order follows original: field at offset 0x1C (index 7) is cleared before offset 0x18 (index 6).

struct BaseStruct {
    int32_t field0;   // +0x00
    int32_t field4;   // +0x04
    int32_t field8;   // +0x08
    int32_t field12;  // +0x0C
    int32_t field16;  // +0x10
    int32_t field20;  // +0x14
    int32_t field24;  // +0x18
    int32_t field28;  // +0x1C
};

void __thiscall BaseStruct::zeroOut() {
    field0 = 0;
    field4 = 0;
    field8 = 0;
    field12 = 0;
    field16 = 0;
    field20 = 0;
    field28 = 0; // +0x1C
    field24 = 0; // +0x18
}