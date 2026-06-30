// FUNC_NAME: Player::storeAndClearState
void __fastcall Player::storeAndClearState()
{
    // Copy one dword from +0x21c (likely a state flag or timestamp) to +0x424
    *(uint32_t*)(this + 0x424) = *(uint32_t*)(this + 0x21c);

    // Copy 5 uint64 fields from buffer at +0x404 to saved state at +0x3e4
    *(uint64_t*)(this + 0x3e4) = *(uint64_t*)(this + 0x404);
    *(uint64_t*)(this + 0x3ec) = *(uint64_t*)(this + 0x40c);
    *(uint64_t*)(this + 0x3f4) = *(uint64_t*)(this + 0x414);
    *(uint64_t*)(this + 0x3fc) = *(uint64_t*)(this + 0x41c);

    // Clear the source buffer (likely zeros the 5 uint64 fields at +0x404)
    clearStateBuffer(this + 0x404);
}