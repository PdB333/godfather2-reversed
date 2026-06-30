int __fastcall FUN_004040d0(int param_1, char* param_2)
{
    char terminator = '\0';
    char* cursor;
    std::uint32_t index;
    int resolvedIndex;
    undefined4* allocatorVtable;
    int resourceHandle;
    std::uint32_t resourceSize;
    int* releaseVtable;
    undefined1* pathBuffer;
    int loadedObject = 0;
    undefined4 allocType;
    undefined4 allocFlags;
    undefined4 allocUnused;
    undefined1* local_14 = nullptr;
    std::uint32_t local_10 = 0;
    void (__cdecl* local_8)(undefined1*) = nullptr;

    FUN_004d4a60(&local_14, 1, &DAT_00e2f0b0);
    FUN_004d5900(1);

    if (param_2 != nullptr) {
        cursor = param_2;
        do {
            terminator = *cursor;
            cursor = cursor + 1;
        } while (terminator != '\0');

        FUN_004d41f0(0, param_2, 0, static_cast<int>(cursor) - static_cast<int>(param_2 + 1));

        index = 0;
        if (local_10 != 0) {
            do {
                if (local_14[index] == '/') {
                    local_14[index] = '\\';
                }
                index = index + 1;
            } while (index < local_10);
        }

        pathBuffer = local_14;
        if (local_14 == nullptr) {
            pathBuffer = &DAT_0120546e;
        }

        if (*reinterpret_cast<code**>(DAT_01223378 + 0x50) != nullptr) {
            (**reinterpret_cast<code***>(DAT_01223378 + 0x50))(pathBuffer, 0);
        }
    }

    pathBuffer = local_14;
    if (local_14 == nullptr) {
        pathBuffer = &DAT_0120546e;
    }

    resolvedIndex = FUN_004015e0(pathBuffer, 1);
    if (resolvedIndex != 0) {
        resourceSize =
            *reinterpret_cast<std::uint32_t*>(
                *reinterpret_cast<int*>(DAT_01223378 + 0x38) + 0xc + resolvedIndex * 0x10);

        if (0xf < resourceSize) {
            allocatorVtable = reinterpret_cast<undefined4*>(FUN_009c8f80());
            allocType = 2;
            allocFlags = 0x800;
            allocUnused = 0;

            resourceHandle = (**reinterpret_cast<code***>(allocatorVtable))(resourceSize, &allocType);
            if (resourceHandle != 0) {
                const std::uint32_t bytesRead =
                    FUN_00401780(resolvedIndex, resourceHandle, resourceSize);

                if ((bytesRead == resourceSize) && ((terminator = FUN_004a8050()), terminator != '\0')) {
                    *reinterpret_cast<short*>(resourceHandle + 0xe) =
                        *reinterpret_cast<short*>(resourceHandle + 0xe) + 1;
                    loadedObject = resourceHandle;
                } else {
                    releaseVtable = reinterpret_cast<int*>(FUN_009c8f80());
                    (**reinterpret_cast<code***>(*releaseVtable + 4))(resourceHandle, 0);
                }
            }
        }

        FUN_004016d0(resolvedIndex);

        if (loadedObject != 0) {
            if (param_2 == nullptr) {
                *reinterpret_cast<std::uint16_t*>(loadedObject + 0xe) =
                    *reinterpret_cast<std::uint16_t*>(loadedObject + 0xe) & 0x7fff;
            } else {
                *reinterpret_cast<std::uint16_t*>(loadedObject + 0xe) =
                    *reinterpret_cast<std::uint16_t*>(loadedObject + 0xe) | 0x8000;
            }

            FUN_00405c70(param_1, loadedObject);

            if (*reinterpret_cast<std::uint32_t*>(param_1 + 0x124) < 0x20) {
                *reinterpret_cast<int*>(
                    param_1 + 0xa4 + *reinterpret_cast<std::uint32_t*>(param_1 + 0x124) * 4) =
                    loadedObject;
                *reinterpret_cast<int*>(param_1 + 0x124) =
                    *reinterpret_cast<int*>(param_1 + 0x124) + 1;
            }
        }
    }

    if (local_14 != nullptr) {
        local_8(local_14);
    }

    return loadedObject;
}