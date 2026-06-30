// FUNC_NAME: ThreadContext::postMessage
void __fastcall ThreadContext::postMessage(void* thisPtr)
{
    // thisPtr points to a ThreadContext object: +0x00 = messageHandle, +0x08 = messageSizeIndex
    int sizeIndex = *(int*)((char*)thisPtr + 8);
    if (sizeIndex >= 0)
    {
        void* threadTls = TlsGetValue(DAT_01139810);
        // Call a function that posts a message to the thread's queue
        // messageHandle = thisPtr[0], size = sizeIndex << 6, messageType = 0x17 (23)
        FUN_00aa26e0(*(undefined4*)thisPtr, sizeIndex << 6, 0x17);
    }
}