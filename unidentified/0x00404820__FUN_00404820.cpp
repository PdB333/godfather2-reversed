void __fastcall FUN_00404820(int param_1)
{
    auto* const node = unaff_EDI;

    if (reinterpret_cast<int*>(node[1]) == nullptr) {
        const int next = node[0];
        *reinterpret_cast<int*>(param_1 + 0x70) = next;
        if (next != 0) {
            *reinterpret_cast<int*>(next + 4) = 0;
            goto detach_done;
        }
    } else {
        *reinterpret_cast<int*>(node[1]) = node[0];
detach_done:
        if (node[0] != 0) {
            *reinterpret_cast<int*>(node[0] + 4) = node[1];
            goto links_cleared;
        }
    }

    {
        auto* const prev = reinterpret_cast<std::uint32_t*>(node[1]);
        *reinterpret_cast<std::uint32_t**>(param_1 + 0x74) = prev;
        if (prev != nullptr) {
            *prev = 0;
        }
    }

links_cleared:
    const std::uint32_t flags = static_cast<std::uint32_t>(node[0x14]);

    node[1] = 0;
    node[0] = 0;

    FUN_004d0cc0();
    node[10] = -1;

    if (((flags >> 9) & 1U) == 0) {
        FUN_00405570(param_1);
    } else {
        FUN_00404bc0();
        node[9] = 2;
    }

    if (node == *reinterpret_cast<int**>(param_1 + 0x80)) {
        *reinterpret_cast<int*>(param_1 + 0x80) = 0;
    }
}