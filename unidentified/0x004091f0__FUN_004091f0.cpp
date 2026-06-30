extern "C" void FUN_004091f0(int* param_1)
{
    int* next;
    int* node;
    int* free_list_head;
    bool stop;
    std::uint32_t* allocator;

    *reinterpret_cast<std::uint16_t*>(unaff_EDI + 0x16) =
        (
            *reinterpret_cast<std::uint16_t*>(unaff_EDI + 0x16) & 0xfffe
        ) - 1 ^ (
            static_cast<std::uint8_t>(
                ~static_cast<std::uint8_t>(*reinterpret_cast<std::uint16_t*>(unaff_EDI + 0x16))
            ) & 1
        );

    if (reinterpret_cast<int*>(*param_1) != nullptr)
    {
        *reinterpret_cast<int*>(*param_1) = param_1[1];
    }

    if (reinterpret_cast<int*>(param_1[1]) != nullptr)
    {
        *reinterpret_cast<int*>(param_1[1]) = *param_1;
    }

    param_1[1] = 0;
    *param_1 = 0;

    stop = false;
    next = *reinterpret_cast<int**>(unaff_EDI + 4);
    allocator = DAT_01205200;

joined_r0x0040922d:
    do
    {
        do
        {
            node = next;
            if ((node == nullptr) || stop)
            {
                return;
            }

            next = reinterpret_cast<int*>(*node);
        } while (node[2] != 0);

        if (reinterpret_cast<std::uint32_t*>(node[1]) == nullptr)
        {
            *reinterpret_cast<int**>(unaff_EDI + 4) = next;
            if (next != nullptr)
            {
                next[1] = 0;
                goto LAB_00409264;
            }

LAB_00409272:
            *reinterpret_cast<std::uint32_t**>(unaff_EDI + 8) =
                reinterpret_cast<std::uint32_t*>(node[1]);
            if (reinterpret_cast<std::uint32_t*>(node[1]) != nullptr)
            {
                *reinterpret_cast<std::uint32_t*>(node[1]) = 0;
            }
        }
        else
        {
            *reinterpret_cast<int*>(node[1]) = reinterpret_cast<int>(next);

LAB_00409264:
            if (*node == 0)
            {
                goto LAB_00409272;
            }

            *reinterpret_cast<int*>(*node + 4) = node[1];
        }

        node[1] = 0;
        *node = 0;

        free_list_head = reinterpret_cast<int*>(*allocator);
        next = node;

        if (free_list_head == nullptr)
        {
LAB_004092bb:
            stop = true;
            goto joined_r0x0040922d;
        }

        if ((reinterpret_cast<int*>(allocator[7]) == nullptr) ||
            ((free_list_head <= node) &&
             (node < reinterpret_cast<int*>(allocator[1] + reinterpret_cast<int>(free_list_head)))))
        {
            *node = allocator[2];
            allocator[5] = allocator[5] + 1;
            allocator[2] = reinterpret_cast<std::uint32_t>(node);
            goto LAB_004092bb;
        }

        (**reinterpret_cast<void (__thiscall***)(int*)>(
            *reinterpret_cast<int*>(allocator[7]) + 8))(node);

        stop = true;
        allocator = DAT_01205200;
    } while (true);
}