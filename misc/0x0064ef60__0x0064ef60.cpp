extern "C" std::uint32_t __thiscall FUN_0064ef60(std::int32_t* this_, std::int32_t* object)
{
    const std::int32_t index =
        (*reinterpret_cast<std::int32_t(__thiscall**)()>(
            *reinterpret_cast<std::int32_t*>(this_) + 0x50
        ))();

    const std::int32_t tableBase =
        (*reinterpret_cast<std::int32_t(__thiscall**)()>(
            *reinterpret_cast<std::int32_t*>(object) + 0x00
        ))();

    const std::uint32_t value = *reinterpret_cast<std::uint32_t*>(
        reinterpret_cast<std::uint8_t*>(reinterpret_cast<void*>(tableBase + 0x10 + index * 4))
    );

    if ((*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1f0) <= value) &&
        (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1b4) == 7)) {
        return value & 0xffffff00;
    }

    (*reinterpret_cast<void(__thiscall**)(std::int32_t*, std::int32_t*)>(
        *reinterpret_cast<std::int32_t*>(object) + 0x18
    ))(object, this_);

    if ((static_cast<std::uint32_t>(_DAT_01223cbc) & 1U) == 0) {
        _DAT_01223cbc = _DAT_01223cbc | 1;
        FUN_0064f120();
        _atexit(reinterpret_cast<_func_4879*>(&LAB_00d513f0));
    }

    std::int32_t* node = DAT_01223cb8;
    _DAT_01223cb0 = _DAT_01223cb0 + 1;

    if (DAT_01223cb8 == nullptr) {
        node = reinterpret_cast<std::int32_t*>(FUN_0065bd60(DAT_01223cb4));
        std::int32_t* freeListHead = DAT_01223cb8;

        if (node != nullptr) {
            node[0] = 0;
            goto acquired_node;
        }

        DAT_01223cb8 = freeListHead;
        node = nullptr;
    } else {
        std::int32_t* next = reinterpret_cast<std::int32_t*>(DAT_01223cb8[0]);

        if (DAT_01223cb8 != nullptr) {
            DAT_01223cb8[0] = 0;
            DAT_01223cb8 = next;
            goto acquired_node;
        }

        DAT_01223cb8 = next;
        node = nullptr;
    }

acquired_node:
    {
        std::int32_t* const previousObject = reinterpret_cast<std::int32_t*>(node[0]);

        if (previousObject != nullptr) {
            std::int32_t* const refCount = previousObject + 2;
            *refCount = *refCount + -1;
            if (*refCount == 0) {
                (*reinterpret_cast<void(__thiscall**)()>(
                    *reinterpret_cast<std::int32_t*>(previousObject) + 8
                ))();
            }
        }
    }

    node[0] = reinterpret_cast<std::int32_t>(object);
    object[2] = object[2] + 1;
    node[2] = 0;

    if (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(reinterpret_cast<void*>(node[0])) + 0x10) == 0) {
        node[1] = *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1e4);
        *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1e4) =
            *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1e4) + 1;

        if (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1cc) == 0) {
            *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1cc) =
                reinterpret_cast<std::int32_t>(node);
            *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1d0) =
                reinterpret_cast<std::int32_t>(node);
            return 1;
        }

        const std::int32_t tail =
            *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1d0);

        *reinterpret_cast<std::int32_t*>(reinterpret_cast<void*>(tail + 8)) =
            reinterpret_cast<std::int32_t>(node);

        *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1d0) =
            reinterpret_cast<std::int32_t>(node);

        return (static_cast<std::uint32_t>(tail) & 0xffffff00) | 1;
    }

    node[1] = -1;

    if (*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1d4) == 0) {
        *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1d4) =
            reinterpret_cast<std::int32_t>(node);
        *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1d8) =
            reinterpret_cast<std::int32_t>(node);
        return 1;
    }

    *reinterpret_cast<std::int32_t*>(reinterpret_cast<void*>(
        *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1d8) + 8
    )) = reinterpret_cast<std::int32_t>(node);

    *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this_) + 0x1d8) =
        reinterpret_cast<std::int32_t>(node);

    return 1;
}