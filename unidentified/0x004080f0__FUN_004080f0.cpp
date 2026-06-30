extern "C" void FUN_004080f0(
    std::uint32_t param_1,
    std::uint32_t param_2,
    std::uint32_t param_3
)
{
    FUN_00408e80(param_2, param_3);
    FUN_00408d50(param_1);
    FUN_00408ff0();

    void* const allocation = reinterpret_cast<void*>(FUN_009c8e50(0x4004));
    if (allocation == nullptr) {
        DAT_01162380 = nullptr;
    } else {
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(allocation) + 0x4000) = 0;
        _memset(allocation, 0, 0x4000);
        DAT_01162380 = allocation;
    }

    std::uint32_t messageId = FUN_004dafd0("iMsgDeleteEventHandler");
    FUN_00408260(&DAT_012067d4, messageId);

    messageId = FUN_004dafd0("iMsgDeleteEntity");
    FUN_00408260(&DAT_012067c4, messageId);

    messageId = FUN_004dafd0("iMsgOnDeleteEntity");
    FUN_00408260(&DAT_012067cc, messageId);

    messageId = FUN_004dafd0("iMsgNotifyDeleteEntity");
    FUN_00408260(&DAT_012067dc, messageId);
}