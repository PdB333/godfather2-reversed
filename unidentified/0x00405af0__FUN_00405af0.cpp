extern "C" std::uint32_t FUN_00405af0(int param_1, int param_2)
{
    int node = *reinterpret_cast<int*>(param_1 + 0x80);

    if ((node == 0) || (*reinterpret_cast<int*>(node + 0x2c) != param_2))
    {
        node = *reinterpret_cast<int*>(param_1 + 0x6c);

        while (true)
        {
            if (node == 0)
            {
                return 0;
            }

            if (*reinterpret_cast<int*>(node + 0x2c) == param_2)
            {
                break;
            }

            node = *reinterpret_cast<int*>(node + 4);
        }
    }

    return *reinterpret_cast<std::uint32_t*>(node + 0x1c);
}