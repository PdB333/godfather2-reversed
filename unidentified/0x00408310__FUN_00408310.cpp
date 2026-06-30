extern "C" void FUN_00408310(std::uint32_t* const param_1)
{
    struct MessageEntry {
        MessageEntry* next;
        std::uint32_t field_04;
        std::uint32_t field_08;
        std::uint32_t field_0c;
        std::uint32_t messageId;
        std::uint16_t refCount;
        std::uint16_t field_16;
    };

    const std::uint32_t messageId = *param_1;
    if (messageId == 0) {
        return;
    }

    auto** const buckets = reinterpret_cast<MessageEntry**>(DAT_01162380);
    MessageEntry* entry = buckets[messageId & 0x0fff];
    while (entry != nullptr && entry->messageId != messageId) {
        entry = entry->next;
    }

    auto* const localRefCount =
        reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uint8_t*>(param_1) + 6);

    if (*localRefCount == 0) {
        *param_1 = DAT_012067bc;
        if (DAT_012067bc != 0) {
            FUN_00408030();
            return;
        }
    } else {
        entry->refCount = static_cast<std::uint16_t>(entry->refCount + -1);
        *localRefCount = static_cast<std::uint16_t>(*localRefCount + -1);

        if (*localRefCount == 0) {
            *param_1 = 0;
        }

        if (entry->refCount == 0) {
            FUN_00409460();
            *param_1 = DAT_012067bc;
            if (DAT_012067bc != 0) {
                FUN_00408030();
            }
            FUN_004abf50(entry);
        }
    }

    return;
}