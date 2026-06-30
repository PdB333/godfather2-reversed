extern "C" void __thiscall FUN_006503b0(std::int32_t* this_, std::int32_t* entry)
{
    auto* const self = reinterpret_cast<std::uint8_t*>(this_);
    auto* const candidate = reinterpret_cast<std::uint8_t*>(entry);

    auto** const freeList = *reinterpret_cast<std::int32_t***>(self + 0x1fc);
    auto** const bucketTable = *reinterpret_cast<std::int32_t***>(self + 0x218);

    if ((*reinterpret_cast<char*>(self + 0x209) != '\0') &&
        (freeList != nullptr) &&
        (((*reinterpret_cast<std::uint32_t*>(candidate + 0x30) >> 3) & 1) != 0) &&
        ((((*reinterpret_cast<std::uint32_t*>(candidate + 0x30) >> 2) & 1) == 0) ||
         (*reinterpret_cast<std::int32_t*>(self + 0x124) != 0))) {

        const std::uint32_t bucketIndex =
            (reinterpret_cast<std::uintptr_t>(entry) / 0x34) & 0x3ff;

        auto* bucketEntry = bucketTable[bucketIndex];
        while (bucketEntry != nullptr) {
            if (bucketEntry[0] == reinterpret_cast<std::int32_t>(entry)) {
                bucketEntry[8] = bucketEntry[8] | 1;
                return;
            }

            bucketEntry = reinterpret_cast<std::int32_t*>(bucketEntry[6]);
        }

        if (*reinterpret_cast<std::int32_t*>(self + 0x204) != 0x400) {
            auto* const newEntry =
                freeList[*reinterpret_cast<std::int32_t*>(self + 0x204)];

            FUN_0064f3f0(newEntry);
            newEntry[1] = -1;
            FUN_0064d4a0(newEntry);

            newEntry[8] = 5;
            newEntry[0] = reinterpret_cast<std::int32_t>(entry);
            newEntry[2] = 0;
            newEntry[7] = 0;
            newEntry[5] = reinterpret_cast<std::int32_t>(this_);
            newEntry[3] = *reinterpret_cast<std::int32_t*>(candidate + 0x1c);

            if (*reinterpret_cast<std::int32_t*>(candidate + 0x1c) != 0) {
                *reinterpret_cast<std::int32_t**>(
                    reinterpret_cast<std::uint8_t*>(
                        *reinterpret_cast<std::int32_t*>(candidate + 0x1c)
                    ) + 0x10
                ) = newEntry;
            }

            newEntry[4] = 0;
            *reinterpret_cast<std::int32_t**>(candidate + 0x1c) = newEntry;

            newEntry[6] = reinterpret_cast<std::int32_t>(bucketTable[bucketIndex]);
            bucketTable[bucketIndex] = newEntry;
        }
    }
}