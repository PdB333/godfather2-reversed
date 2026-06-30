// FUNC_NAME: Reader::bufferedRead
void __fastcall Reader::bufferedRead(int count)
{
    // Fallback buffer pointer at offset +4 in this object
    void* fallback = *(void**)((char*)this + 4);
    // Local fallback buffer (three DWORDs = 12 bytes)
    uint localBuffer[3];
    void* buffer;
    if (fallback == nullptr)
    {
        buffer = &localBuffer;
    }
    else
    {
        buffer = fallback;
    }
    // Call the first virtual function (vtable[0]) with size = count * 0x28 (40 bytes per element)
    void (*firstVFunc)(int, void*) = (void (*)(int, void*))(*((void***)this)[0]);
    firstVFunc(count * 0x28, buffer);
}