extern "C" bool FUN_00409ae0(int param_1, std::uint32_t param_2)
{
    int current = *reinterpret_cast<int*>(param_1 + unaff_EDI * 4);
    int count = 0;

    if (current != 0)
    {
        int last;
        do
        {
            last = current;
            count = count + 1;
            current = *reinterpret_cast<int*>(last + 8);
        } while (*reinterpret_cast<int*>(last + 8) != 0);

        if (last != 0)
        {
            *reinterpret_cast<std::uint32_t*>(last + 8) = param_2;
            return 2 < count;
        }
    }

    *reinterpret_cast<std::uint32_t*>(param_1 + unaff_EDI * 4) = param_2;
    return 2 < count;
}