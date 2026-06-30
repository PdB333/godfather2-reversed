extern "C" std::uint32_t FUN_004098a0(std::uint32_t* param_1, int param_2)
{
    const std::uint32_t bucketIndex = *param_1 & 0xff;
    int node = *reinterpret_cast<int*>(param_2 + static_cast<int>(bucketIndex) * 4);
    int previous = 0;
    std::uint32_t result = 1;

    if (node != 0)
    {
        int current;
        while (true)
        {
            current = node;
            if (*reinterpret_cast<std::uint32_t*>(current + 0x10) == *param_1)
            {
                break;
            }

            node = *reinterpret_cast<int*>(current + 8);
            previous = current;

            if (*reinterpret_cast<int*>(current + 8) == 0)
            {
                return result;
            }
        }

        if (previous != 0)
        {
            *reinterpret_cast<std::uint32_t*>(previous + 8) =
                *reinterpret_cast<std::uint32_t*>(current + 8);
            return 0;
        }

        *reinterpret_cast<std::uint32_t*>(param_2 + static_cast<int>(bucketIndex) * 4) =
            *reinterpret_cast<std::uint32_t*>(current + 8);
        result = 0;
    }

    return result;
}