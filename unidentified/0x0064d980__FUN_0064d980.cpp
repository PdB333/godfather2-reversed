extern "C" void __fastcall FUN_0064d980(std::int32_t* entry, std::int32_t* refCountedObject)
{
    if (refCountedObject != nullptr) {
        refCountedObject[2] = refCountedObject[2] + 1;
    }

    if (((*reinterpret_cast<std::uint32_t*>(
              reinterpret_cast<std::uint8_t*>(entry) + 0x30
          ) >> 1) & 1U) == 0) {
        if (DAT_01205a24 == 0) {
            for (std::int32_t node = *reinterpret_cast<std::int32_t*>(
                     reinterpret_cast<std::uint8_t*>(entry) + 0x1c
                 );
                 node != 0;
                 node = *reinterpret_cast<std::int32_t*>(
                     reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::intptr_t>(node)) + 0x0c
                 )) {
                if ((
                        *reinterpret_cast<std::uint8_t*>(
                            reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::intptr_t>(node)) + 0x20
                        ) & 0x3c
                    ) == 0) {
                    FUN_0064ef60(refCountedObject);
                }
            }
        } else {
            FUN_0064ef60(refCountedObject);
        }
    } else {
        FUN_0064ef60(refCountedObject);
    }

    if (refCountedObject != nullptr) {
        std::int32_t* const refCount = refCountedObject + 2;
        *refCount = *refCount + -1;
        if (*refCount == 0) {
            reinterpret_cast<void(__thiscall*)(void*)>(
                *reinterpret_cast<std::uint32_t*>(refCountedObject) + 8
            )(refCountedObject);
            return;
        }
    }

    return;
}