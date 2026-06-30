extern "C" void FUN_00408260(std::uint32_t* const param_1, const std::uint32_t param_2)
{
    if (param_2 == 0) {
        *param_1 = DAT_012067bc;
        if (DAT_012067bc == 0) {
            return;
        }

        FUN_00408030();
        return;
    }

    struct MessageEntry {
        MessageEntry* next;
        std::uint32_t field_04;
        std::uint32_t field_08;
        std::uint32_t field_0c;
        std::uint32_t messageId;
        std::uint16_t refCount;
        std::uint16_t field_16;
    };

    auto* const tableBase = static_cast<std::uint8_t*>(DAT_01162380);
    auto** const buckets = reinterpret_cast<MessageEntry**>(tableBase);

    MessageEntry* entry = buckets[param_2 & 0x0fff];
    if (entry != nullptr) {
        do {
            if (entry->messageId == param_2) {
                goto found_entry;
            }
            entry = entry->next;
        } while (entry != nullptr);
    }

    entry = reinterpret_cast<MessageEntry*>(FUN_00407b50());
    if (entry == nullptr) {
        entry = nullptr;
    } else {
        entry->next = nullptr;
        entry->field_04 = 0;
        entry->field_08 = 0;
        entry->field_0c = 0;
        entry->messageId = param_2;
        entry->refCount = 0;
        entry->field_16 = 0;
    }

    {
        auto* const bucket = &buckets[entry->messageId & 0x0fff];
        entry->next = *bucket;
        *bucket = entry;
        *reinterpret_cast<std::int32_t*>(tableBase + 0x4000) =
            *reinterpret_cast<std::int32_t*>(tableBase + 0x4000) + 1;
    }

found_entry:
    *param_1 = entry->messageId;
    entry->refCount = entry->refCount + 1;
    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(param_1) + 6) =
        *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(param_1) + 6) + 1;
    return;
}