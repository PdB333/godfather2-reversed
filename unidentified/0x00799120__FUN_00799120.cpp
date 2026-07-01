// FUNC_NAME: SomeClass::copy12ByteData
void __thiscall copy12ByteData(int this, undefined8* source) {
    // Copy 8 bytes from source to offset 0x2504
    *(undefined8*)(this + 0x2504) = *source;
    // Copy 4 bytes from source+8 (first 4 bytes of second 8-byte element) to offset 0x250c
    *(undefined4*)(this + 0x250c) = *(undefined4*)(source + 1);
}