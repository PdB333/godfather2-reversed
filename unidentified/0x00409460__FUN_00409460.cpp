extern "C" std::uint32_t FUN_00409460(std::uint32_t* param_1)
{
    const int bucketsBase = DAT_01162380;
    const std::uint32_t key = *param_1;
    const std::uint32_t bucketIndex = key & 0x0fff;

    int* previous = nullptr;
    int* node = *reinterpret_cast<int**>(bucketsBase + bucketIndex * 4);
    std::uint32_t result = 1;

    if (node != nullptr)
    {
        int* current;
        do
        {
            current = node;
            if (current[4] == key)
            {
                if (previous != nullptr)
                {
                    *previous = *current;
                    int* count = reinterpret_cast<int*>(bucketsBase + 0x4000);
                    *count = *count + -1;
                    return 0;
                }

                *reinterpret_cast<int*>(bucketsBase + bucketIndex * 4) = *current;
                int* count = reinterpret_cast<int*>(bucketsBase + 0x4000);
                *count = *count + -1;
                result = 0;
                return result;
            }

            node = reinterpret_cast<int*>(*current);
            previous = current;
        } while (node != nullptr);
    }

    return result;
}