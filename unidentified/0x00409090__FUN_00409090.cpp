extern "C" void FUN_00409090(std::uint32_t* param_1)
{
    auto* const self = reinterpret_cast<std::uint8_t*>(__builtin_frame_address(0)); // unresolved unaff_EDI-backed context
    auto* listNode = *reinterpret_cast<std::uint32_t**>(reinterpret_cast<std::uintptr_t>(self) + 4);

    *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uintptr_t>(self) + 0x16) =
        (*reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uintptr_t>(self) + 0x16) & 0xfffe) + 2 ^
        *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uintptr_t>(self) + 0x16) & 1;

    int allocator = DAT_01205200;

    for (; listNode != nullptr; listNode = reinterpret_cast<std::uint32_t*>(*listNode))
    {
        if (*reinterpret_cast<std::uint16_t*>(listNode[2] + 0x16) ==
            *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uintptr_t>(param_1) + 0x16))
        {
            goto found_or_inserted;
        }

        if (*reinterpret_cast<std::uint16_t*>(listNode[2] + 0x16) <
            *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uintptr_t>(param_1) + 0x16))
        {
            auto* freeNode = *reinterpret_cast<std::uint32_t**>(DAT_01205200 + 8);

            if (freeNode == nullptr)
            {
                if (*reinterpret_cast<int**>(DAT_01205200 + 0x1c) != nullptr)
                {
                    freeNode =
                        reinterpret_cast<std::uint32_t*>((**reinterpret_cast<std::uint32_t* (***)(std::uint32_t, std::uint32_t)>(
                            **reinterpret_cast<int**>(DAT_01205200 + 0x1c) + 4))(
                            *reinterpret_cast<std::uint32_t*>(DAT_01205200 + 0xc),
                            *reinterpret_cast<std::uint32_t*>(DAT_01205200 + 0x10)));
                    allocator = DAT_01205200;
                    goto acquired_insert_node;
                }
no_insert_node_available:
                freeNode = nullptr;
            }
            else
            {
                const std::uint32_t next = *freeNode;
                *reinterpret_cast<int*>(DAT_01205200 + 0x14) =
                    *reinterpret_cast<int*>(DAT_01205200 + 0x14) + -1;
                *reinterpret_cast<std::uint32_t*>(allocator + 8) = next;

                if (*reinterpret_cast<std::uint32_t*>(allocator + 0x14) <
                    *reinterpret_cast<std::uint32_t*>(allocator + 0x18))
                {
                    *reinterpret_cast<std::uint32_t*>(allocator + 0x18) =
                        *reinterpret_cast<std::uint32_t*>(allocator + 0x14);
                }

acquired_insert_node:
                if (freeNode == nullptr)
                {
                    goto no_insert_node_available;
                }

                *freeNode = 0;
                freeNode[1] = 0;
                freeNode[2] = 0;
            }

            *freeNode = reinterpret_cast<std::uint32_t>(listNode);
            freeNode[1] = listNode[1];

            if (listNode[1] == 0)
            {
                *reinterpret_cast<std::uint32_t**>(reinterpret_cast<std::uintptr_t>(self) + 4) = freeNode;
                listNode[1] = reinterpret_cast<std::uint32_t>(freeNode);
                listNode = freeNode;
            }
            else
            {
                *reinterpret_cast<std::uint32_t**>(listNode[1]) = freeNode;
                listNode[1] = reinterpret_cast<std::uint32_t>(freeNode);
                listNode = freeNode;
            }

            goto found_or_inserted;
        }
    }

    listNode = *reinterpret_cast<std::uint32_t**>(allocator + 8);

    if (listNode == nullptr)
    {
        if (*reinterpret_cast<int**>(allocator + 0x1c) != nullptr)
        {
            listNode =
                reinterpret_cast<std::uint32_t*>((**reinterpret_cast<std::uint32_t* (***)(std::uint32_t, std::uint32_t)>(
                    **reinterpret_cast<int**>(allocator + 0x1c) + 4))(
                    *reinterpret_cast<std::uint32_t*>(allocator + 0xc),
                    *reinterpret_cast<std::uint32_t*>(allocator + 0x10)));
            goto acquired_tail_node;
        }
    }
    else
    {
        const std::uint32_t next = *listNode;
        *reinterpret_cast<int*>(allocator + 0x14) = *reinterpret_cast<int*>(allocator + 0x14) + -1;
        *reinterpret_cast<std::uint32_t*>(allocator + 8) = next;

        if (*reinterpret_cast<std::uint32_t*>(allocator + 0x14) <
            *reinterpret_cast<std::uint32_t*>(allocator + 0x18))
        {
            *reinterpret_cast<std::uint32_t*>(allocator + 0x18) =
                *reinterpret_cast<std::uint32_t*>(allocator + 0x14);
        }

acquired_tail_node:
        if (listNode != nullptr)
        {
            *listNode = 0;
            listNode[1] = 0;
            listNode[2] = 0;
            goto link_tail_node;
        }
    }

    listNode = nullptr;

link_tail_node:
    *listNode = 0;
    listNode[1] = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(self) + 8);

    if (*reinterpret_cast<std::uint32_t**>(reinterpret_cast<std::uintptr_t>(self) + 8) == nullptr)
    {
        *reinterpret_cast<std::uint32_t**>(reinterpret_cast<std::uintptr_t>(self) + 4) = listNode;
    }
    else
    {
        **reinterpret_cast<std::uint32_t***>(reinterpret_cast<std::uintptr_t>(self) + 8) = listNode;
    }

    *reinterpret_cast<std::uint32_t**>(reinterpret_cast<std::uintptr_t>(self) + 8) = listNode;

found_or_inserted:
    auto* const ownerLink = listNode + 2;
    param_1[1] = listNode[2];
    *param_1 = reinterpret_cast<std::uint32_t>(ownerLink);

    if (reinterpret_cast<std::uint32_t*>(*ownerLink) != nullptr)
    {
        *reinterpret_cast<std::uint32_t*>(*ownerLink) = reinterpret_cast<std::uint32_t>(param_1 + 1);
    }

    *ownerLink = reinterpret_cast<std::uint32_t>(param_1);
}