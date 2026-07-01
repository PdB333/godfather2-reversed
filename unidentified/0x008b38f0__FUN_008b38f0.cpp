// FUNC_NAME: SomeClass::releaseAndClearResources
void __fastcall SomeClass::releaseAndClearResources(void)
{
    // Release resource pointed to by first member (offset 0x00)
    this->releaseResource(reinterpret_cast<void*>(this->pResource));
    this->pResource = nullptr;                  // +0x00
    this->someCount = 0;                         // +0x04
    this->someFlags = 0;                         // +0x08
}