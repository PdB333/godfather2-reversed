extern "C" void __thiscall FUN_0040cf30(int thisPtr, char* source)
{
    if (source != nullptr) {
        _strncpy(reinterpret_cast<char*>(thisPtr + 0x90), source, 0x80);
    }
}