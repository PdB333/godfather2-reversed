void __cdecl FUN_00402b40(std::uint32_t in_EAX)
{
    std::int32_t local_10;
    std::uint32_t local_c;
    void (__cdecl* local_4)(void*);

    FUN_004d3bc0(in_EAX);

    char* const buffer = reinterpret_cast<char*>(local_10);
    const std::uint32_t length = local_c;
    auto* const freeFn = local_4;

    if (buffer != nullptr) {
        std::uint32_t index = 0;
        if (length != 0) {
            do {
                if (buffer[index] == '/') {
                    buffer[index] = '\\';
                }
                index = index + 1;
            } while (index < length);
        }
    }

    FUN_004d3e20(&local_10);

    if (local_10 != 0) {
        freeFn(reinterpret_cast<void*>(local_10));
    }
}