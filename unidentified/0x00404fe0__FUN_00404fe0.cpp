int __thiscall FUN_00404fe0(void* this_, std::uint32_t param_2, std::uint32_t param_3, int param_4)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    int result = 0;
    LARGE_INTEGER startCounter{};
    QueryPerformanceCounter(&startCounter);

    int previousGeneration = 0;
    FUN_00404c50(param_2, param_3, param_4 == 0);

    LARGE_INTEGER waitEndCounter{};
    QueryPerformanceCounter(&waitEndCounter);

    int currentGeneration = *reinterpret_cast<int*>(self + 0x80);

    while (true) {
        if ((currentGeneration == 0) || (currentGeneration == previousGeneration)) {
            return result;
        }

        std::uint32_t elapsedHigh =
            static_cast<std::uint32_t>(waitEndCounter.HighPart - startCounter.HighPart) -
            static_cast<std::uint32_t>(waitEndCounter.LowPart < startCounter.LowPart);

        if ((param_3 < elapsedHigh) ||
            ((param_3 <= elapsedHigh) &&
             (param_2 <= static_cast<std::uint32_t>(waitEndCounter.LowPart - startCounter.LowPart)))) {
            param_2 = 0;
            param_3 = 0;
        } else {
            const bool carry =
                static_cast<std::uint32_t>(param_2) >
                static_cast<std::uint32_t>(0xFFFFFFFFu -
                                           static_cast<std::uint32_t>(startCounter.LowPart - waitEndCounter.LowPart));

            param_2 = param_2 + static_cast<std::uint32_t>(startCounter.LowPart - waitEndCounter.LowPart);
            param_3 = param_3 +
                      (static_cast<std::uint32_t>(startCounter.HighPart - waitEndCounter.HighPart) -
                       static_cast<std::uint32_t>(startCounter.LowPart < waitEndCounter.LowPart)) +
                      static_cast<std::uint32_t>(carry);
        }

        LARGE_INTEGER callStartCounter{};
        QueryPerformanceCounter(&callStartCounter);

        const std::uint32_t status =
            FUN_00404db0(this_, *reinterpret_cast<std::uint32_t*>(self + 0x80), 0, param_2, param_3);

        if (((status & 4U) != 0) || (((status & 2U) != 0) && ((status & 8U) == 0))) {
            result = 1;
        }

        LARGE_INTEGER callEndCounter{};
        QueryPerformanceCounter(&callEndCounter);

        if (*reinterpret_cast<int*>(self + 0x9C) != 0) {
            break;
        }

        if (result != 0) {
            return result;
        }

        std::uint32_t callElapsedHigh =
            static_cast<std::uint32_t>(callEndCounter.HighPart - callStartCounter.HighPart) -
            static_cast<std::uint32_t>(callEndCounter.LowPart < callStartCounter.LowPart);

        if (param_3 < callElapsedHigh) {
            return 0;
        }

        if ((param_3 <= callElapsedHigh) &&
            (param_2 <= static_cast<std::uint32_t>(callEndCounter.LowPart - callStartCounter.LowPart))) {
            return 0;
        }

        previousGeneration = *reinterpret_cast<int*>(self + 0x80);
        FUN_00404c50(param_2, param_3, 0);
        QueryPerformanceCounter(&waitEndCounter);
        currentGeneration = *reinterpret_cast<int*>(self + 0x80);
    }

    return 1;
}