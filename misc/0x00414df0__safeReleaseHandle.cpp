// FUNC_NAME: safeReleaseHandle
void __fastcall safeReleaseHandle(int** ppHandle)
{
    if (*ppHandle != nullptr) {
        // Set field at offset 8 of the object to 0 (likely a refcount or deletion flag)
        *reinterpret_cast<int*>(reinterpret_cast<char*>(*ppHandle) + 8) = 0;
        *ppHandle = nullptr;
    }
}