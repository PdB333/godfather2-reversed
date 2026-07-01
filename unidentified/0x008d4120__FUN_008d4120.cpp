// FUNC_NAME: SomeClass::shutdown
void __fastcall SomeClass::shutdown(int thisPtr)
{
    if (*(char*)(thisPtr + 0x81) != '\0') {
        SoundManager::shutdown((void*)0x0112f9d0); // +0x81: m_bInitialized flag
        *(char*)(thisPtr + 0x81) = 0;
    }
}