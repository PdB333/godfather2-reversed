void __thiscall FUN_00405120(void* this_, std::uint32_t param_2, std::uint32_t param_3)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    auto* entry = *reinterpret_cast<std::uint32_t**>(DAT_012234a8 + 0x4C);
    int generation;

    while (true) {
        if (entry == nullptr) {
            generation = -1;

enter_timing:
            LARGE_INTEGER startCounter{};
            QueryPerformanceCounter(&startCounter);

            std::uint32_t remainingLow = param_2;
            std::uint32_t remainingHigh = param_3;

resume_processing:
            do {
                if (generation == -1) {
                    return;
                }

                auto* waitNode = *reinterpret_cast<int**>(self + 0x70);
                int currentGeneration = waitNode[10];

                while (currentGeneration != generation) {
                    waitNode = reinterpret_cast<int*>(*waitNode);
                    currentGeneration = waitNode[10];
                }

                std::uint32_t waitResult;
                do {
                    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&param_2));

                    std::uint32_t elapsedLow =
                        param_2 - static_cast<std::uint32_t>(startCounter.LowPart);

                    if ((remainingHigh == 0) && (remainingLow <= elapsedLow)) {
                        return;
                    }

                    waitResult = FUN_00404db0(
                        this_,
                        waitNode,
                        1,
                        remainingLow - elapsedLow,
                        remainingHigh - static_cast<std::uint32_t>(remainingLow < elapsedLow));

                    if ((waitResult & 8U) != 0) {
                        return;
                    }

                } while ((waitResult & 2U) != 0);

                if (generation == -1) {
                    entry = *reinterpret_cast<std::uint32_t**>(DAT_012234a8 + 0x4C);
                } else {
                    entry = *reinterpret_cast<std::uint32_t**>(DAT_012234a8 + 0x4C);
                    do {
                        if (entry == nullptr) {
                            goto no_match;
                        }

                        auto* genField = reinterpret_cast<int*>(entry + 0x2B);
                        entry = reinterpret_cast<std::uint32_t*>(*entry);

                        if (*genField == generation) {
                            break;
                        }

                    } while (true);
                }

                for (; entry != nullptr; entry = reinterpret_cast<std::uint32_t*>(*entry)) {
                    if ((*reinterpret_cast<std::uint8_t*>(entry + 0x2A) & 2U) == 0) {
                        generation = static_cast<int>(entry[0x2B]);
                        goto resume_processing;
                    }
                }

no_match:
                generation = -1;

            } while (true);
        }

        if ((*reinterpret_cast<std::uint8_t*>(entry + 0x2A) & 2U) == 0) {
            generation = static_cast<int>(entry[0x2B]);
            goto enter_timing;
        }

        entry = reinterpret_cast<std::uint32_t*>(*entry);
    }
}