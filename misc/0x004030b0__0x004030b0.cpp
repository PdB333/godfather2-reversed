std::uint32_t* __thiscall FUN_004030b0(
    std::uint32_t* param_1,
    std::uint32_t param_2,
    std::uint32_t param_3,
    std::uint32_t param_4)
{
    LARGE_INTEGER performanceCounter{};

    DAT_0122337c = param_1;

    param_1[0x00] = reinterpret_cast<std::uint32_t>(&PTR_FUN_00e2f0d0);
    param_1[0x02] = DAT_012054b8;
    param_1[0x03] = reinterpret_cast<std::uint32_t>("Streams");
    param_1[0x04] = 0;
    param_1[0x05] = 0;
    param_1[0x06] = 0;
    param_1[0x07] = 0x80;
    param_1[0x08] = 0;
    param_1[0x09] = 4;
    param_1[0x0a] = 0;
    param_1[0x0c] = 0xf0;
    param_1[0x0d] = 0;
    param_1[0x0e] = 0;
    param_1[0x0b] = 0xf0;
    param_1[0x01] = reinterpret_cast<std::uint32_t>(&PTR_FUN_00e2f0d4);

    DAT_012054b8 = param_1 + 1;

    param_1[0x0f] = 0;
    param_1[0x10] = 0;
    param_1[0x11] = FUN_009c8e80(0x2800);
    param_1[0x12] = 0;
    param_1[0x13] = 0x200;

    FUN_00406980();

    param_1[0x1a] = 0;
    param_1[0x1b] = 0;
    param_1[0x1c] = 0;
    param_1[0x1d] = 0;
    param_1[0x1e] = 0;
    param_1[0x1f] = 0;
    param_1[0x20] = 0;
    param_1[0x21] = 0;

    *reinterpret_cast<std::uint8_t*>(param_1 + 0x22) = 0;
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(param_1) + 0x89) = 0;
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(param_1) + 0x8a) = 0;

    QueryPerformanceCounter(&performanceCounter);

    param_1[0x24] = static_cast<std::uint32_t>(performanceCounter.LowPart);
    param_1[0x25] = static_cast<std::uint32_t>(performanceCounter.HighPart);
    param_1[0x26] = param_3;
    param_1[0x27] = 0;
    param_1[0x28] = 0;
    param_1[0x49] = 0;
    param_1[0x54] = 0;
    param_1[0x55] = 0;
    param_1[0x56] = 0;
    param_1[0x57] = 0;

    FUN_004028c0();

    FUN_00408260(&DAT_01206794, FUN_004dafd0("iMsgStreamBeginLoad"));
    FUN_00408260(&DAT_01206760, FUN_004dafd0("iMsgStreamLoadComplete"));
    FUN_00408260(&DAT_01206780, FUN_004dafd0("iMsgStreamCancel"));
    FUN_00408260(&DAT_012067ac, FUN_004dafd0("iMsgStreamExplicitDecRef"));
    FUN_00408260(&DAT_01206778, FUN_004dafd0("iMsgStreamBeginUnload"));
    FUN_00408260(&DAT_012067b4, FUN_004dafd0("iMsgStreamUnloading"));
    FUN_00408260(&DAT_01206768, FUN_004dafd0("iMsgStreamUnloadComplete"));
    FUN_00408260(&DAT_012067a4, FUN_004dafd0("iMsgStreamIdle"));
    FUN_00408260(&DAT_0120678c, FUN_004dafd0("iMsgStreamAllDispatched"));
    FUN_00408260(&DAT_0120679c, FUN_004dafd0("iMsgStreamManagerBeginUnload"));
    FUN_00408260(&DAT_01206770, FUN_004dafd0("iMsgStreamManagerUnloadComplete"));

    std::uint8_t* puStack_4 = reinterpret_cast<std::uint8_t*>(&LAB_00407730);
    std::int32_t iStack_18 = 0x2a7ed975;
    auto* pcStack_14 = FUN_00404fe0;
    std::uint32_t* puStack_1c = param_1;

    (void)pcStack_14;
    (void)puStack_1c;

    FUN_00486b90(param_2, param_4);

    if ((puStack_4 != nullptr) && (iStack_18 != 0x2a7ed975)) {
        FUN_00407640();
    }

    FUN_004074e0(0x40);
    return param_1;
}