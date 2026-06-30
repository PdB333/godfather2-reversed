// FUNC_NAME: InlineBufferClass::~InlineBufferClass
void __thiscall InlineBufferClass_Destructor(void) {
    char *bufferPtr;
    char localBuffer[16];

    FUN_005a0a00(in_EAX);  // deinitialize base/members
    FUN_005a1060();         // global cleanup

    // Small-string optimization: free heap buffer if not inline
    if (bufferPtr != localBuffer && bufferPtr != (char *)0x0) {
        ((void (*)(char *))DAT_0119caf4)(bufferPtr);  // operator delete
    }
}