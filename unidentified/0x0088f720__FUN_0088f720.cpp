// FUNC_NAME: SomeClass::releaseStreamHandle
void __fastcall SomeClass::releaseStreamHandle(int thisPtr)
{
    // Check if stream object pointer at offset 0x1CC is non-null
    if (*(void**)(thisPtr + 0x1CC) != nullptr)
    {
        // Release the stream object (calls destructor or decrement reference)
        ReleaseStreamObject(*(void**)(thisPtr + 0x1CC));
        // Clear the pointer and reset the flag/counter at offset 0x1C8
        *(void**)(thisPtr + 0x1CC) = nullptr;
        *(short*)(thisPtr + 0x1C8) = 0;
    }
}