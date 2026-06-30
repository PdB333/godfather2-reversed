extern "C" void __fastcall FUN_0064f3f0(std::int32_t* entry)
{
    auto** const heap = *reinterpret_cast<std::int32_t***>(
        reinterpret_cast<std::uint8_t*>(this) + 0x1fc
    );

    if (*reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(entry) + 0x2c
        ) != *reinterpret_cast<std::int32_t*>(
                reinterpret_cast<std::uint8_t*>(this) + 0x204
            )) {

        heap[*reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(this) + 0x204
        )][0x2c / 4] = *reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(entry) + 0x2c
        );

        *reinterpret_cast<std::int32_t**>(
            reinterpret_cast<std::uint8_t*>(heap) +
            *reinterpret_cast<std::int32_t*>(
                reinterpret_cast<std::uint8_t*>(entry) + 0x2c
            ) * 4
        ) = heap[*reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(this) + 0x204
        )];

        heap[*reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(this) + 0x204
        )] = entry;

        *reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(entry) + 0x2c
        ) = *reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(this) + 0x204
        );
    }

    *reinterpret_cast<std::int32_t*>(
        reinterpret_cast<std::uint8_t*>(this) + 0x204
    ) = *reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(this) + 0x204
        ) + 1;
}