// FUNC_NAME: SomeClass::handleData
void __thiscall SomeClass::handleData(int messageHeader) {
    int count;
    int* src;
    int* dst;

    if (messageHeader == 5) {
        // Copy 26 dwords (104 bytes) from the stack-based message to internal buffer
        src = &messageHeader; // source is the stack address of the message header (first dword)
        dst = (int*)(*(int*)(this + 0x4) + 0x3a0c); // destination: pointer at +0x4, then offset +0x3a0c
        count = 0x1a; // 26 iterations
        while (count != 0) {
            *dst = *src;
            src = src + 1;
            dst = dst + 1;
            count = count - 1;
        }
    }
    return;
}