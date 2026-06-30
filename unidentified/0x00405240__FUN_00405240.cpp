void __thiscall FUN_00405240(void* this_)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    while (true) {
        int current = *reinterpret_cast<int*>(self + 0x80);

        if (current == 0) {
            current = FUN_00404d60(this_);
            if (current != 0) {
                auto* queued = *reinterpret_cast<int**>(self + 0x78);
                if (queued != nullptr) {
                    do {
                        if (queued[0x0B] == *reinterpret_cast<int*>(current + 0x2C)) {
                            goto reject_current;
                        }
                        queued = reinterpret_cast<int*>(*queued);
                    } while (queued != nullptr);
                }

                if (((*reinterpret_cast<unsigned int*>(current + 0x50) >> 4) & 1U) != 0) {
                    auto* name = *reinterpret_cast<const char**>(current + 8);
                    if (name == nullptr) {
                        name = reinterpret_cast<const char*>(&DAT_0120546e);
                    }

                    if ((*reinterpret_cast<void***>(DAT_01223378 + 0x50) != nullptr) &&
                        (reinterpret_cast<char(__cdecl*)(const char*, int)>(
                             *reinterpret_cast<void**>(DAT_01223378 + 0x50))(name, 0) != '\0')) {
reject_current:
                        current = 0;
                    }
                }

                *reinterpret_cast<int*>(self + 0x80) = current;
            }

            if (*reinterpret_cast<int*>(self + 0x80) == 0) {
                return;
            }

            *reinterpret_cast<std::uint32_t*>(*reinterpret_cast<int*>(self + 0x80) + 0x24) = 1;
            FUN_00402f40(1, 1);

            current = *reinterpret_cast<int*>(self + 0x80);
            if (current == 0) {
                return;
            }
        }

        if (*reinterpret_cast<int*>(current + 0x24) == 1) {
            auto* generationNode = *reinterpret_cast<int**>(DAT_012234a8 + 0x4C);
            if (generationNode != nullptr) {
                do {
                    if (generationNode[0x2B] == *reinterpret_cast<int*>(current + 0x28)) {
                        if (generationNode[0x2C] != -0x67) {
                            goto continue_processing;
                        }
                        break;
                    }
                    generationNode = reinterpret_cast<int*>(*generationNode);
                } while (generationNode != nullptr);
            }

            if (*reinterpret_cast<int*>(self + 0x9C) == 0) {
                auto* node = *reinterpret_cast<int**>(self + 0x80);

                if (reinterpret_cast<int*>(node[1]) == nullptr) {
                    int prev = *node;
                    *reinterpret_cast<int*>(self + 0x70) = prev;
                    if (prev != 0) {
                        *reinterpret_cast<std::uint32_t*>(prev + 4) = 0;
                        goto relink_tail;
                    }

set_wait_tail:
                    {
                        auto* next = reinterpret_cast<std::uint32_t*>(node[1]);
                        *reinterpret_cast<std::uint32_t**>(self + 0x74) = next;
                        if (next != nullptr) {
                            *next = 0;
                        }
                    }
                } else {
                    *reinterpret_cast<int*>(node[1]) = *node;

relink_tail:
                    if (*node == 0) {
                        goto set_wait_tail;
                    }
                    *reinterpret_cast<int*>(*node + 4) = node[1];
                }

                node[1] = 0;
                *node = 0;
                *reinterpret_cast<std::uint32_t*>(*reinterpret_cast<int*>(self + 0x80) + 0x28) = 0xFFFFFFFF;
                *reinterpret_cast<std::uint32_t*>(*reinterpret_cast<int*>(self + 0x80) + 0x24) = 3;

                auto* readyNode = reinterpret_cast<std::uint32_t*>(*reinterpret_cast<int*>(self + 0x80));
                readyNode[0] = *reinterpret_cast<std::uint32_t*>(self + 0x68);
                readyNode[1] = 0;

                if (*reinterpret_cast<int*>(self + 0x68) == 0) {
                    *reinterpret_cast<std::uint32_t**>(self + 0x6C) = readyNode;
                } else {
                    *reinterpret_cast<std::uint32_t**>(*reinterpret_cast<int*>(self + 0x68) + 4) = readyNode;
                }

                *reinterpret_cast<std::uint32_t**>(self + 0x68) = readyNode;

                const std::uint32_t movedNode = *reinterpret_cast<std::uint32_t*>(self + 0x80);
                *reinterpret_cast<std::uint32_t*>(self + 0x80) = 0;
                FUN_00405b30(this_, movedNode);
            }
        }

continue_processing:
        current = *reinterpret_cast<int*>(self + 0x80);
        if (current != 0) {
            if (*reinterpret_cast<int*>(current + 0x24) != 1) {
                FUN_004048c0(current, 0);
            }

            if (*reinterpret_cast<int*>(self + 0x80) != 0) {
                return;
            }
        }
    }
}