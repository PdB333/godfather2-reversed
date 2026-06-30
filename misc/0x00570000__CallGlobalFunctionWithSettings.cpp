// FUNC_NAME: CallGlobalFunctionWithSettings
void CallGlobalFunctionWithSettings(void* this_ptr)
{
    // Stack structure: likely a small configuration struct (size 12 bytes)
    int32_t fieldA = 2;          // +0x00: Possibly an enum or command type
    int32_t fieldB = 0x10;       // +0x04: Some size or count
    int32_t fieldC = 0;          // +0x08: Flags or padding

    // Global function pointer stored at 0x0120556c; called with this and the settings struct
    (*(void (**)(void*, void*))DAT_0120556c)(this_ptr, &fieldA);
}