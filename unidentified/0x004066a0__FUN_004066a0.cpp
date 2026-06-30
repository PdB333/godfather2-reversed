extern "C" void __thiscall FUN_004066a0(int param_1, std::uint8_t* param_2)
{
    if (param_2 != nullptr)
    {
        std::uint32_t index = 0;

        if (*reinterpret_cast<std::uint32_t*>(param_1 + 0x158) != 0)
        {
            auto* entry = reinterpret_cast<std::uint32_t*>(*reinterpret_cast<int*>(param_1 + 0x154));

            do
            {
                auto* existing = reinterpret_cast<std::uint8_t*>(entry[0]);
                auto* input = param_2;

                if (existing == nullptr)
                {
                    existing = reinterpret_cast<std::uint8_t*>(&DAT_0120546e);
                }

                int compareResult;
                do
                {
                    const std::uint8_t lhs0 = existing[0];
                    const bool less0 = lhs0 < input[0];

                    if (lhs0 != input[0])
                    {
                        compareResult =
                            (1 - static_cast<std::uint32_t>(less0)) -
                            static_cast<std::uint32_t>(less0 != 0);
                        goto compare_done;
                    }

                    if (lhs0 == 0)
                    {
                        break;
                    }

                    const std::uint8_t lhs1 = existing[1];
                    const bool less1 = lhs1 < input[1];

                    if (lhs1 != input[1])
                    {
                        compareResult =
                            (1 - static_cast<std::uint32_t>(less1)) -
                            static_cast<std::uint32_t>(less1 != 0);
                        goto compare_done;
                    }

                    existing += 2;
                    input += 2;
                } while (true);

                compareResult = 0;

compare_done:
                if (compareResult == 0)
                {
                    return;
                }

                index = index + 1;
                entry = entry + 4;
            } while (index < *reinterpret_cast<std::uint32_t*>(param_1 + 0x158));
        }

        FUN_004d3bc0(param_2);

        int capacity = *reinterpret_cast<int*>(param_1 + 0x15c);
        if (*reinterpret_cast<int*>(param_1 + 0x158) == capacity)
        {
            if (capacity == 0)
            {
                capacity = 1;
            }
            else
            {
                capacity = capacity * 2;
            }

            FUN_00407880(capacity);
        }

        const int count = *reinterpret_cast<int*>(param_1 + 0x158);
        *reinterpret_cast<int*>(param_1 + 0x158) = count + 1;

        int local_10[3];
        code* local_4;

        if (count * 0x10 + *reinterpret_cast<int*>(param_1 + 0x154) != 0)
        {
            FUN_004d3b50(local_10);
        }

        if (local_10[0] != 0)
        {
            local_4(local_10[0]);
        }
    }
}