// FUNC_NAME: NetPacketHeader::initializeFromArgs
class NetPacketHeader {
public:
    uint32_t field0;      // +0x00
    uint32_t hash;        // +0x04 - truncated hash (bits [31:22])
    float timeOrParam;    // +0x08 - passed via XMM0
    uint32_t param3;      // +0x0C
    uint32_t param2;      // +0x10
    uint32_t param4;      // +0x14

    __thiscall void initializeFromArgs(uint32_t arg1, uint32_t arg2, uint32_t arg3, float fValue, uint32_t regValue) {
        // Note: real signature used __fastcall with EAX as this, ECX as arg1? Actually the decompiler shows four params but we reconstruct as member.
        // Parameters are reordered: param_4 -> field5, param_2->field4, param_3->field3, in_XMM0_Da->field2, unaff_EDI->field0.
        field5 = arg3;          // param_4
        field2 = fValue;        // in_XMM0_Da
        field0 = regValue;      // unaff_EDI
        field3 = arg1;          // param_3 (arg1)
        field4 = arg2;          // param_2 (arg2)

        // Hash computation over the local stack frame (likely the function's local data for integrity check)
        uint32_t hashVal = 0;
        byte* ptr = reinterpret_cast<byte*>(&field0);  // start from stack base (approx)
        byte* end = reinterpret_cast<byte*>(_AddressOfReturnAddress()); // until return address? This is guess.
        // Original loop: pbVar2 = &stack0xfffffff4; while (pbVar2 < &stack0x00000000) { ... }
        // In real code, this likely hashes a fixed-size structure or the whole stack.
        while (ptr < end) {
            hashVal = hashVal * 0x1003f + *ptr;
            ptr++;
        }
        field1 = hashVal >> 22;  // store top 10 bits
    }
};