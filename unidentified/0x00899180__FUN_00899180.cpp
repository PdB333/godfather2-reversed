// FUNC_NAME: SomeClass::copyData
void __fastcall copyData(void* thisPtr)
{
    *(uint32_t *)((char *)thisPtr + 400) = *(uint32_t *)((char *)thisPtr + 0x188);
    *(uint32_t *)((char *)thisPtr + 0x194) = *(uint32_t *)((char *)thisPtr + 0x18c);
}