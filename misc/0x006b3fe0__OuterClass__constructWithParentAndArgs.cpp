// FUNC_NAME: OuterClass::constructWithParentAndArgs
void __thiscall OuterClass::constructWithParentAndArgs(void* pThis, void* pParent, uint32_t arg3, uint32_t arg4, char arg5)
{
    // Allocate memory for inner object of size 0x44 bytes
    void* pInner = operatorNew(0x44);
    void* pInnerConstructed;
    if (pInner == nullptr) {
        pInnerConstructed = nullptr;
    } else {
        pInnerConstructed = InnerClass::constructor(pThis, pParent, arg3, arg4, arg5);
    }
    // Store pointer to inner object at offset 0xFC
    *(void**)((uint8_t*)pThis + 0xFC) = pInnerConstructed;

    // Copy value from parent+0x54 to this+0x44
    *(uint32_t*)((uint8_t*)pThis + 0x44) = *(uint32_t*)((uint8_t*)pParent + 0x54);

    // Clear bit 23 of flags at offset 0x34
    *(uint32_t*)((uint8_t*)pThis + 0x34) &= 0xFF7FFFFF;

    // Post-initialization call
    PostInitialize();

    // Debug/logging if class ID matches and flag is zero
    if (*(uint32_t*)((uint8_t*)pThis + 0x40) == 0x637B907 && arg5 == '\0') {
        DebugLogMessage(0x19);  // log message ID 0x19
        DebugMessageData msgData;
        msgData.field0 = DAT_0112a608;  // some global data
        msgData.field4 = 0;
        msgData.field8_byte = arg5;
        DebugPrintf(&msgData, 0);
    }
}