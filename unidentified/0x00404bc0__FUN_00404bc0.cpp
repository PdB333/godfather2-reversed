void __fastcall FUN_00404bc0(void* result, int param_2)
{
    auto* node = static_cast<std::uint32_t*>(result);
    auto*& head = *reinterpret_cast<std::uint32_t**>(param_2 + 0x78);
    auto*& tail = *reinterpret_cast<std::uint32_t**>(param_2 + 0x7c);

    auto append_to_tail = [&]() -> void {
        node[0] = 0;
        node[1] = reinterpret_cast<std::uint32_t>(tail);

        if (tail != nullptr) {
            *reinterpret_cast<std::uint32_t*>(tail) = reinterpret_cast<std::uint32_t>(node);
            tail = node;
            return;
        }

        head = node;
        tail = node;
    };

    std::uint32_t* current = head;
    if (current == nullptr) {
        append_to_tail();
        return;
    }

    if (static_cast<std::uint32_t>(node[8]) <= static_cast<std::uint32_t>(current[8])) {
        do {
            current = reinterpret_cast<std::uint32_t*>(current[0]);
            if (current == nullptr) {
                append_to_tail();
                return;
            }
        } while (static_cast<std::uint32_t>(node[8]) <= static_cast<std::uint32_t>(current[8]));
    }

    node[0] = reinterpret_cast<std::uint32_t>(current);
    node[1] = current[1];

    if (current[1] != 0) {
        *reinterpret_cast<std::uint32_t*>(current[1]) = reinterpret_cast<std::uint32_t>(node);
        current[1] = reinterpret_cast<std::uint32_t>(node);
        return;
    }

    head = node;
    current[1] = reinterpret_cast<std::uint32_t>(node);
    return;
}