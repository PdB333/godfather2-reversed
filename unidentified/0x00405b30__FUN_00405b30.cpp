extern "C" void FUN_00402f40(int, int);

extern "C" void FUN_00405b30(int param_1, std::uint32_t* param_2)
{
    const int thisObject = reinterpret_cast<int>(param_2);

    FUN_00402f40(2, 1);

    std::uint32_t processedCount = 0;

    if (*reinterpret_cast<int*>(thisObject + 0x74) == 0)
    {
finalize_self:
        const std::uint32_t flags = *reinterpret_cast<std::uint32_t*>(thisObject + 0x60);

        if ((((~static_cast<std::uint8_t>(flags >> 0x1e) & 1) != 0) && (-1 < static_cast<int>(flags))) &&
            ((flags & ((1u << (static_cast<std::uint8_t>(*reinterpret_cast<std::uint32_t*>(thisObject + 0xec)) & 0x1f)) - 1u)) == 0))
        {
            *reinterpret_cast<std::uint32_t*>(thisObject + 0x60) = flags | 0x80000000;
            FUN_00402f40(0x100, 1);
        }

        return;
    }

    param_2 = reinterpret_cast<std::uint32_t*>(thisObject + 100);

iterate_entries:
    for (std::uint32_t* node =
             *reinterpret_cast<std::uint32_t**>(
                 *reinterpret_cast<int*>(param_1 + 0x50) +
                 (*param_2 % *reinterpret_cast<std::uint32_t*>(param_1 + 0x54)) * 4);
         node != nullptr;
         node = reinterpret_cast<std::uint32_t*>(node[2]))
    {
        if (*node == *param_2)
        {
            if (node != nullptr)
            {
                const std::uint32_t targetObject = node[1];
                if (targetObject != 0)
                {
                    std::uint32_t matchIndex = 0;
                    std::uint32_t bitIndex = 0xffffffff;

                    if (*reinterpret_cast<std::uint32_t*>(targetObject + 0xec) == 0)
                    {
clear_bit:
                        *reinterpret_cast<std::uint32_t*>(targetObject + 0x60) =
                            *reinterpret_cast<std::uint32_t*>(targetObject + 0x60) &
                            ~(1u << (static_cast<std::uint8_t>(bitIndex) & 0x1f));

                        const std::uint32_t targetFlags =
                            *reinterpret_cast<std::uint32_t*>(targetObject + 0x60);

                        if ((((targetFlags &
                               ((1u << (static_cast<std::uint8_t>(
                                            *reinterpret_cast<std::uint32_t*>(targetObject + 0xec)) &
                                        0x1f)) -
                                1u)) == 0) &&
                             (*reinterpret_cast<int*>(targetObject + 0x24) == 3)) &&
                            ((~static_cast<std::uint8_t>(targetFlags >> 0x1e) & 1) != 0))
                        {
                            *reinterpret_cast<std::uint32_t*>(targetObject + 0x60) =
                                targetFlags | 0x80000000;
                            FUN_00402f40(0x100, 1);
                        }
                    }
                    else
                    {
                        do
                        {
                            bitIndex = matchIndex;
                            if (*reinterpret_cast<int*>(targetObject + 0x78 + matchIndex * 4) ==
                                *reinterpret_cast<int*>(thisObject + 0x1c))
                            {
                                goto clear_bit;
                            }

                            ++matchIndex;
                            bitIndex = 0xffffffff;
                        } while (matchIndex < *reinterpret_cast<std::uint32_t*>(targetObject + 0xec));

                        goto clear_bit;
                    }
                }
            }

            break;
        }
    }

    ++param_2;
    ++processedCount;

    if (*reinterpret_cast<std::uint32_t*>(thisObject + 0x74) <= processedCount)
    {
        goto finalize_self;
    }

    goto iterate_entries;
}