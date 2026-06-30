extern "C" void __fastcall FUN_004084d0(std::uint32_t* const param_1, const std::uint16_t param_2, void* const unaff_ESI)
{
    struct MessageEntry {
        MessageEntry* next;
        std::uint32_t field_04;
        std::uint32_t field_08;
        std::uint32_t owner;
        std::uint32_t messageId;
        std::uint16_t refCount;
        std::uint16_t field_16;
    };

    struct MessagePool {
        std::uint32_t field_00;
        std::uint32_t field_04;
        MessageEntry* freeList;
        std::uint32_t allocArg0;
        std::uint32_t allocArg1;
        std::int32_t activeCount;
        std::uint32_t lowWatermark;
        void* allocator;
    };

    using AllocatorVtable = void*;
    using AllocatorObject = AllocatorVtable*;
    using AllocateFn = void* (__thiscall*)(AllocatorObject, std::uint32_t, std::uint32_t);

    auto* const object = static_cast<std::uint8_t*>(unaff_ESI);
    const auto poolBase = DAT_012051fc;
    auto* const pool = reinterpret_cast<MessagePool*>(poolBase);

    MessageEntry* entry = pool->freeList;
    if (entry == nullptr) {
        if (*reinterpret_cast<AllocatorObject**>(poolBase + 0x1c) != nullptr) {
            auto* const allocatorObject = *reinterpret_cast<AllocatorObject**>(poolBase + 0x1c);
            entry = reinterpret_cast<MessageEntry*>(
                (*reinterpret_cast<AllocateFn*>(reinterpret_cast<std::uint8_t*>(*allocatorObject) + 4))(
                    allocatorObject,
                    *reinterpret_cast<std::uint32_t*>(poolBase + 0x0c),
                    *reinterpret_cast<std::uint32_t*>(poolBase + 0x10)));
            goto LAB_0040850b;
        }
    }
    else {
        const std::uint32_t nextFree = *reinterpret_cast<std::uint32_t*>(entry);

        *reinterpret_cast<std::int32_t*>(poolBase + 0x14) =
            *reinterpret_cast<std::int32_t*>(poolBase + 0x14) + -1;
        *reinterpret_cast<std::uint32_t*>(poolBase + 8) = nextFree;

        if (*reinterpret_cast<std::uint32_t*>(poolBase + 0x14) <
            *reinterpret_cast<std::uint32_t*>(poolBase + 0x18)) {
            *reinterpret_cast<std::uint32_t*>(poolBase + 0x18) =
                *reinterpret_cast<std::uint32_t*>(poolBase + 0x14);
        }

LAB_0040850b:
        if (entry != nullptr) {
            const std::uint32_t messageId = *param_1;
            *reinterpret_cast<std::uint32_t*>(entry) = 0;
            reinterpret_cast<std::uint32_t*>(entry)[1] = 0;
            reinterpret_cast<std::uint32_t*>(entry)[2] = 0;
            reinterpret_cast<std::uint32_t*>(entry)[4] = messageId;
            reinterpret_cast<std::uint32_t*>(entry)[3] = reinterpret_cast<std::uint32_t>(unaff_ESI);
            *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(entry) + 0x14) = 1;
            *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(entry) + 0x16) = param_2;
            goto LAB_00408544;
        }
    }

    entry = nullptr;

LAB_00408544:
    if (*reinterpret_cast<std::int32_t*>(object + 8) == 0) {
        auto* storage = reinterpret_cast<std::uint64_t*>(FUN_00409510());
        if (storage == nullptr) {
            storage = nullptr;
        }
        else {
            storage[0] = 0;
            storage[1] = 0;
        }
        *reinterpret_cast<std::uint64_t**>(object + 8) = storage;
    }

    if (((*reinterpret_cast<std::uint32_t*>(object + 4) >> 2) & 1U) == 0) {
        const int result = FUN_00409a90(*reinterpret_cast<std::uint32_t*>(object + 8), entry);
        if (result == 1) {
            void* newStorage = reinterpret_cast<void*>(FUN_00409680());
            if (newStorage == nullptr) {
                newStorage = nullptr;
            }
            else {
                _memset(newStorage, 0, 0x80);
            }

            FUN_004092d0(*reinterpret_cast<std::uint32_t*>(object + 8));
            if (*reinterpret_cast<std::int32_t*>(object + 8) != 0) {
                FUN_004abf50(*reinterpret_cast<std::int32_t*>(object + 8));
            }

            *reinterpret_cast<std::uint32_t*>(object + 4) =
                *reinterpret_cast<std::uint32_t*>(object + 4) | 4;
            *reinterpret_cast<void**>(object + 8) = newStorage;
        }
    }
    else if (((*reinterpret_cast<std::uint32_t*>(object + 4) >> 3) & 1U) == 0) {
        const int result = FUN_00409ae0(*reinterpret_cast<std::uint32_t*>(object + 8), entry);
        if (result == 1) {
            void* newStorage = reinterpret_cast<void*>(FUN_00409810());
            if (newStorage == nullptr) {
                newStorage = nullptr;
            }
            else {
                _memset(newStorage, 0, 0x400);
            }

            FUN_00409310(*reinterpret_cast<std::uint32_t*>(object + 8));
            if (*reinterpret_cast<std::int32_t*>(object + 8) != 0) {
                FUN_004abf50(*reinterpret_cast<std::int32_t*>(object + 8));
            }

            *reinterpret_cast<std::uint32_t*>(object + 4) =
                *reinterpret_cast<std::uint32_t*>(object + 4) | 8;
            *reinterpret_cast<void**>(object + 8) = newStorage;
        }
    }
    else {
        FUN_00409b20(*reinterpret_cast<std::uint32_t*>(object + 8), entry);
    }

    auto** const buckets = reinterpret_cast<MessageEntry**>(DAT_01162380);
    MessageEntry* bucketEntry = buckets[(*param_1 & 0x0fff)];
    while (bucketEntry != nullptr && bucketEntry->messageId != *param_1) {
        bucketEntry = bucketEntry->next;
    }

    FUN_00409090(entry);
}