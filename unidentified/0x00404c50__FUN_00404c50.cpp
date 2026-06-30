void __fastcall FUN_00404c50(std::uint32_t param_1, std::uint32_t param_2, char param_3)
{
    LARGE_INTEGER startCounter{};
    QueryPerformanceCounter(&startCounter);

    const std::uint32_t startHigh = static_cast<std::uint32_t>(startCounter.HighPart);
    const std::uint32_t startLow = static_cast<std::uint32_t>(startCounter.LowPart);

    const auto schedulerState = DAT_012234a8;
    auto* const criticalSection =
        reinterpret_cast<LPCRITICAL_SECTION>(schedulerState + 0x68);

    EnterCriticalSection(criticalSection);
    FUN_004d0920();
    if (*reinterpret_cast<int*>(schedulerState + 0x48) == 0) {
        FUN_004d0870();
    }
    LeaveCriticalSection(criticalSection);

    const std::uint32_t requestedLow = param_1;
    const std::uint32_t requestedHigh = param_2;

    if ((*reinterpret_cast<int*>(in_EAX + 0x70) == 0) &&
        (*reinterpret_cast<int*>(in_EAX + 0x78) == 0)) {
        *reinterpret_cast<int*>(in_EAX + 0xA0) =
            *reinterpret_cast<int*>(in_EAX + 0xA0) + 1;
        FUN_004055f0();
        return;
    }

    if (param_3 != '\0') {
        FUN_004053f0(in_EAX, param_1, param_2);
    }

    LARGE_INTEGER afterOptionalWork{};
    QueryPerformanceCounter(&afterOptionalWork);

    std::uint32_t elapsedLow =
        static_cast<std::uint32_t>(afterOptionalWork.LowPart) - startLow;
    std::uint32_t elapsedHigh =
        (static_cast<std::uint32_t>(afterOptionalWork.HighPart) - startHigh) -
        static_cast<std::uint32_t>(
            static_cast<std::uint32_t>(afterOptionalWork.LowPart) < startLow);

    std::uint32_t remainingLow;
    std::uint32_t remainingHigh;
    if ((requestedHigh < elapsedHigh) ||
        ((requestedHigh <= elapsedHigh) && (requestedLow <= elapsedLow))) {
        remainingLow = 0;
        remainingHigh = 0;
    } else {
        remainingLow = requestedLow - elapsedLow;
        remainingHigh =
            (requestedHigh - elapsedHigh) -
            static_cast<std::uint32_t>(requestedLow < elapsedLow);
    }

    FUN_00405240();

    LARGE_INTEGER afterYield{};
    QueryPerformanceCounter(&afterYield);

    const std::uint32_t yieldLow =
        static_cast<std::uint32_t>(afterYield.LowPart) -
        static_cast<std::uint32_t>(afterOptionalWork.LowPart);
    const std::uint32_t yieldHigh =
        (static_cast<std::uint32_t>(afterYield.HighPart) -
         static_cast<std::uint32_t>(afterOptionalWork.HighPart)) -
        static_cast<std::uint32_t>(
            static_cast<std::uint32_t>(afterYield.LowPart) <
            static_cast<std::uint32_t>(afterOptionalWork.LowPart));

    int sleepLow;
    int sleepHigh;
    if ((remainingHigh < yieldHigh) ||
        ((remainingHigh <= yieldHigh) && (remainingLow <= yieldLow))) {
        sleepLow = 0;
        sleepHigh = 0;
    } else {
        sleepLow = static_cast<int>(remainingLow - yieldLow);
        sleepHigh = static_cast<int>(
            (remainingHigh - yieldHigh) -
            static_cast<std::uint32_t>(remainingLow < yieldLow));
    }

    FUN_00405120(in_EAX, sleepLow, sleepHigh);
    *reinterpret_cast<std::uint32_t*>(in_EAX + 0xA0) = 0;
    FUN_004055f0();
}