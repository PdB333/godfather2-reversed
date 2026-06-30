// FUNC_NAME: NetReflectable::registerNetworkLayout
uint NetReflectable::registerNetworkLayout()
{
    // Global archive singleton used for network serialization setup
    // DAT_01205590 points to a global Archive object (likely a singleton)
    Archive* archive = *(Archive**)DAT_01205590;
    void* thisPtr = reinterpret_cast<void*>(in_EAX); // 'this' pointer passed in EAX

    // Begin registration of a new network object type with a type identifier (0x5980cb)
    archive->beginClass(0x5980cb); // vtable+0x10 call; identifier is likely a function pointer or RTTI

    // Register fields with their offsets and default zero values
    archive->addField(static_cast<char*>(thisPtr) + 2, 0);               // +0x02: short field (size 2)
    archive->addField(static_cast<char*>(thisPtr) + 4, 0, 4);            // +0x04: int field, write zero via local buffer
    archive->addField(static_cast<char*>(thisPtr) + 8, nullptr, 4);      // +0x08: int field, write zero via local buffer (pointer to null)

    // Return the total byte size of the network-relevant fields (0x0C = 12 bytes)
    return 0xC;
}