extern "C" void __fastcall FUN_00408af0()
{
    auto* node = *reinterpret_cast<std::uint32_t**>(in_EAX + 0x0C);

    for (;;)
    {
        if (node == nullptr)
        {
            return;
        }

        FUN_004091f0();

        auto* head = *reinterpret_cast<std::uint32_t**>(in_EAX + 0x0C);
        std::uint32_t* prev;

        if (node == head)
        {
            *reinterpret_cast<std::uint32_t*>(in_EAX + 0x0C) = head[3];
        }
        else
        {
            do
            {
                prev = head;
                if (prev == nullptr)
                {
                    break;
                }

                head = reinterpret_cast<std::uint32_t*>(prev[3]);
            } while (reinterpret_cast<std::uint32_t*>(prev[3]) != node);

            if (reinterpret_cast<std::uint32_t*>(prev[3]) == node)
            {
                prev[3] = node[3];
            }
        }

        auto* pool = DAT_012051fc;

        if (node != nullptr)
        {
            auto* poolBase = reinterpret_cast<std::uint32_t*>(*DAT_012051fc);

            if (poolBase != nullptr)
            {
                if (reinterpret_cast<std::int32_t*>(DAT_012051fc[7]) == nullptr ||
                    (poolBase <= node &&
                     node < reinterpret_cast<std::uint32_t*>(
                                DAT_012051fc[1] + reinterpret_cast<std::intptr_t>(poolBase))))
                {
                    *node = DAT_012051fc[2];
                    auto* freeCount = pool + 5;
                    *freeCount = *freeCount + 1;
                    pool[2] = reinterpret_cast<std::uint32_t>(node);
                }
                else
                {
                    auto* vtable = *reinterpret_cast<std::uint8_t**>(DAT_012051fc[7]);
                    auto fn = *reinterpret_cast<void (**)(std::uint32_t*)>(vtable + 8);
                    fn(node);
                }
            }
        }

        node = *reinterpret_cast<std::uint32_t**>(in_EAX + 0x0C);
    }
}