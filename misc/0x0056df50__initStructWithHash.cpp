// FUNC_NAME: initStructWithHash
void __fastcall initStructWithHash(StructWithHash* this, int paramA, int paramB, int paramC)
{
    // Store register values and parameters into the structure
    this->field0 = unaff_EDI;          // +0x00: value of EDI at call time
    this->field2 = in_XMM0_Da;         // +0x08: float value from XMM0
    this->field3 = paramC;             // +0x0C
    this->field4 = paramB;             // +0x10
    this->field5 = paramA;             // +0x14

    // Compute a hash over the stack area starting at the first stack parameter
    // (likely paramA, paramB, paramC) up to the end of the stack frame.
    uint hash = 0;
    byte* pb = (byte*)&paramA;         // &stack0xfffffff4 in decompiler
    do {
        hash = hash * 0x1003f + (uint)*pb;
        pb++;
    } while (pb < (byte*)&this);       // &stack0x00000000 approximates end of stack frame

    this->hash = hash >> 0x16;         // +0x04: store top 10 bits as hash
}