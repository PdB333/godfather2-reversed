// FUNC_NAME: ResourceManager::readStreamBlock
void __fastcall ResourceManager::readStreamBlock(ResourceManager* this)
{
    int index = this->streamIndex; // +0x08
    if (index >= 0)
    {
        void* tlsData = TlsGetValue(g_tlsSlot); // DAT_01139810
        // Hypothetical function that copies stream data, size = index << 4 (16 bytes per unit), with flag 0x17
        FUN_00aa26e0(this->buffer, index << 4, 0x17);
    }
    return;
}