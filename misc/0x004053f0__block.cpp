void __thiscall block(std::uint8_t* this_, std::uint32_t param_2, std::uint32_t param_3)
{
    const long long baseTicks = FUN_00b9a1f6();

    LARGE_INTEGER startCounter{};
    QueryPerformanceCounter(&startCounter);

    LARGE_INTEGER scopeArg{};
    scopeArg.LowPart = DAT_0120679c;
    scopeArg.HighPart = 0;
    FUN_00408a00(&scopeArg, 0);

    auto* queued = *reinterpret_cast<int**>(this_ + 0x78);

    do {
        if (queued == nullptr) {
            break;
        }

        auto* const next = reinterpret_cast<int*>(queued[0]);
        if (queued[9] == 4) {
            if (FUN_00402f40(0x20, 0) == 0) {
remove_node:
                FUN_00402f40(0x40, 1);

                if (queued[1] == 0) {
                    const int newHead = queued[0];
                    *reinterpret_cast<int*>(this_ + 0x78) = newHead;
                    if (newHead != 0) {
                        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(static_cast<std::uintptr_t>(newHead)) + 4) = 0;
                        goto relink_tail_side;
                    }

update_tail:
                    auto* const newTail = reinterpret_cast<int*>(queued[1]);
                    *reinterpret_cast<int**>(this_ + 0x7C) = newTail;
                    if (newTail != nullptr) {
                        newTail[0] = 0;
                    }
                } else {
                    *reinterpret_cast<int*>(static_cast<std::uintptr_t>(queued[1])) = queued[0];

relink_tail_side:
                    if (queued[0] == 0) {
                        goto update_tail;
                    }

                    *reinterpret_cast<int*>(static_cast<std::uintptr_t>(queued[0]) + 4) = queued[1];
                }

                queued[1] = 0;
                queued[0] = 0;
                FUN_00405570(this_);
            }
        } else {
            if (FUN_00402f40(0x10, 1) == 0) {
                goto remove_node;
            }

            queued[9] = 4;
        }

        LARGE_INTEGER currentCounter{};
        QueryPerformanceCounter(&currentCounter);
        queued = next;
    } while (static_cast<unsigned long long>(
                 baseTicks +
                 (static_cast<unsigned long long>(
                      static_cast<std::uint32_t>(currentCounter.LowPart - startCounter.LowPart)) |
                  (static_cast<unsigned long long>(
                       static_cast<std::uint32_t>(
                           (currentCounter.HighPart - startCounter.HighPart) -
                           static_cast<std::uint32_t>(currentCounter.LowPart < startCounter.LowPart)))
                   << 32))) <=
             (static_cast<unsigned long long>(param_2) |
              (static_cast<unsigned long long>(param_3) << 32)));

    LARGE_INTEGER endArg{};
    endArg.LowPart = DAT_01206770;
    endArg.HighPart = 0;
    FUN_00408a00(&endArg, 0);
}