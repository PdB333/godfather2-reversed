int* __thiscall FUN_00404d60(void* this_)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    auto* current = *reinterpret_cast<int**>(DAT_012234a8 + 0x4C);
    int* result = nullptr;
    int* candidate = result;

    if (current != nullptr) {
        while ((
            *reinterpret_cast<std::uint8_t*>(
                reinterpret_cast<std::uint8_t*>(current) + 0xA8) & 2U) != 0) {
            current = reinterpret_cast<int*>(*current);
            if (current == nullptr) {
                return result;
            }
        }

        if ((current[0x2B] != -1) &&
            ((candidate = *reinterpret_cast<int**>(self + 0x70)),
             (*reinterpret_cast<int**>(self + 0x70) != nullptr))) {
            while ((result = candidate, result[10] != current[0x2B])) {
                candidate = reinterpret_cast<int*>(*result);
                if (reinterpret_cast<int*>(*result) == nullptr) {
                    return nullptr;
                }
            }
        }
    }

    return result;
}