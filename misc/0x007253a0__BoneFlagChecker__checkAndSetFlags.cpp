// FUNC_NAME: BoneFlagChecker::checkAndSetFlags
// Address: 0x007253a0
// This function checks bone hash IDs at four offsets (0x68, 0x6c, 0x70, 0x74) and sets corresponding 
// bits in a flags field (offset 0x134) if the hash matches one of a set of known bone identifiers.
// The bits are: bit0 (1) for offset0x68, bit1 (2) for offset0x70, bit2 (4) for offset0x74, bit3 (8) for offset0x6c.

void __fastcall BoneFlagChecker::checkAndSetFlags(void* thisPtr)
{
    constexpr uint32_t kKnownHash1 = 0x52e7d170;  // -0x6f19da6f == 0x90e62591
    constexpr uint32_t kKnownHash2 = 0x5485e39;
    constexpr uint32_t kKnownHash3 = 0x90e62591;   // -0x6f19da6f as unsigned
    constexpr uint32_t kKnownHash4 = 0xb51ae7e;    // -0x4ae5518a as unsigned
    constexpr uint32_t kKnownHash5 = 0x8f2d9a2e;   // -0x70d265d2 as unsigned
    constexpr uint32_t kKnownHash6 = 0x981799ae;   // -0x67e86652 as unsigned
    constexpr uint32_t kKnownHash7 = 0x53193239;

    // Helper lambda to check if a hash matches any of the known ones
    auto isKnownHash = [](uint32_t hash) -> bool {
        return (hash == kKnownHash1) || (hash == kKnownHash2) || (hash == kKnownHash3) ||
               (hash == kKnownHash4) || (hash == kKnownHash5) || (hash == kKnownHash6) ||
               (hash == kKnownHash7);
    };

    uint32_t* flags = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(thisPtr) + 0x134);
    uint32_t boneHash0 = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(thisPtr) + 0x70);
    uint32_t boneHash1 = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(thisPtr) + 0x68);
    uint32_t boneHash2 = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(thisPtr) + 0x6c);
    uint32_t boneHash3 = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(thisPtr) + 0x74);

    // Check offset +0x70 -> bit1 (0x2)
    if (isKnownHash(boneHash0) && ((*flags & 0x2) == 0))
    {
        *flags |= 0x2;
    }

    // Check offset +0x68 -> bit0 (0x1)
    if (isKnownHash(boneHash1) && ((*flags & 0x1) == 0))
    {
        *flags |= 0x1;
    }

    // Check offset +0x6c -> bit3 (0x8)
    if (isKnownHash(boneHash2) && ((*flags & 0x8) == 0))
    {
        *flags |= 0x8;
    }

    // Check offset +0x74 -> bit2 (0x4)
    if (isKnownHash(boneHash3) && ((*flags & 0x4) == 0))
    {
        *flags |= 0x4;
    }
}