extern "C" void __thiscall FUN_0064f810(void* this_, int param_2)
{
    auto* const self = static_cast<std::uint8_t*>(this_);

    FUN_0064e550(param_2);

    int node = *reinterpret_cast<int*>(param_2 + 0x18);

    while (node != 0) {
        auto* const nodeBytes = reinterpret_cast<std::uint8_t*>(node);
        const int nextNode = *reinterpret_cast<int*>(nodeBytes + 0x0c);

        const int object = *reinterpret_cast<int*>(nodeBytes + 0x08);

        if (*reinterpret_cast<int*>(object + 0x08) == node) {
            *reinterpret_cast<std::uint32_t*>(object + 0x08) = 0;
        }

        const std::uint32_t flags = *reinterpret_cast<std::uint32_t*>(nodeBytes + 0x04);

        if ((flags & 8U) == 0) {
            if ((flags & 0x20U) != 0) {
                const int entry = object;

                if ((*reinterpret_cast<int*>(entry + 0x2c) != 0x400) &&
                    (*reinterpret_cast<int*>(entry + 0x2c) < *reinterpret_cast<int*>(self + 0x200))) {
                    *reinterpret_cast<std::uint32_t*>(entry + 0x04) = 0;
                    FUN_0064d500();
                }

                *reinterpret_cast<int*>(self + 0x204) =
                    *reinterpret_cast<int*>(self + 0x204) + -1;

                if (*reinterpret_cast<int*>(entry + 0x2c) !=
                    *reinterpret_cast<int*>(self + 0x204)) {

                    *reinterpret_cast<int*>(
                        *reinterpret_cast<int*>(
                            *reinterpret_cast<int*>(self + 0x1fc) +
                            *reinterpret_cast<int*>(self + 0x204) * 4
                        ) + 0x2c
                    ) = *reinterpret_cast<int*>(entry + 0x2c);

                    *reinterpret_cast<std::uint32_t*>(
                        *reinterpret_cast<int*>(self + 0x1fc) +
                        *reinterpret_cast<int*>(entry + 0x2c) * 4
                    ) = *reinterpret_cast<std::uint32_t*>(
                        *reinterpret_cast<int*>(self + 0x1fc) +
                        *reinterpret_cast<int*>(self + 0x204) * 4
                    );

                    *reinterpret_cast<int*>(
                        *reinterpret_cast<int*>(self + 0x1fc) +
                        *reinterpret_cast<int*>(self + 0x204) * 4
                    ) = entry;

                    *reinterpret_cast<std::uint32_t*>(entry + 0x2c) =
                        *reinterpret_cast<std::uint32_t*>(self + 0x204);
                }
            }
        } else {
            auto* const objectBytes = reinterpret_cast<std::uint8_t*>(object);
            auto* const objectFlags = reinterpret_cast<std::uint32_t*>(objectBytes + 0x20);

            *objectFlags = *objectFlags & 0xfffffff7U;

            // Correct double dereference: **(int **)(iVar4 + 8)
            const int callbackObject = *reinterpret_cast<int*>(object);

            if (callbackObject != 0) {
                using CallbackFn = void (__thiscall*)(void*);
                auto* const vtable =
                    *reinterpret_cast<void***>(callbackObject);
                auto* const callback =
                    reinterpret_cast<CallbackFn>(vtable[6]); // +0x18

                callback(this_);
            }
        }

        FUN_009c8eb0(node);
        node = nextNode;
    }
}