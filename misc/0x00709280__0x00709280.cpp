extern "C" void __fastcall FUN_00709280(int param_1)
{
    float* const worldMatrix = reinterpret_cast<float*>(FUN_00471610());

    const float positionX = worldMatrix[0x0C];
    const float positionY = worldMatrix[0x0D];
    const float positionZ = worldMatrix[0x0E];

    struct Matrix3x4Like
    {
        std::uint32_t m00;
        std::uint32_t m01;
        std::uint32_t m02;
        std::uint32_t m03;
        std::uint32_t m10;
        std::uint32_t m11;
        std::uint32_t m12;
        std::uint32_t m13;
        std::uint32_t m20;
        std::uint32_t m21;
        std::uint32_t m22;
        std::uint32_t m23;
    };

    Matrix3x4Like localTransform{};
    localTransform.m00 = _DAT_00d5780c;
    localTransform.m11 = _DAT_00d5780c;
    localTransform.m22 = _DAT_00d5780c;

    std::uint32_t local14 = 0;
    (void)positionX;
    (void)positionY;
    (void)positionZ;
    (void)local14;

    TlsGetValue(DAT_01139810);

    int allocation = FUN_00aa2680(0x20, 0x27);
    *reinterpret_cast<std::uint16_t*>(allocation + 4) = 0x20;

    auto* object =
        reinterpret_cast<std::uint32_t*>(
            FUN_00a64b00(
                SQRT(worldMatrix[2] * worldMatrix[2] +
                     worldMatrix[1] * worldMatrix[1] +
                     *worldMatrix * *worldMatrix) *
                _DAT_00d5c458));

    TlsGetValue(DAT_01139810);

    allocation = FUN_00aa2680(0x160, 0x31);
    *reinterpret_cast<std::uint16_t*>(allocation + 4) = 0x160;

    std::uint32_t handle = FUN_0043b490();
    handle = FUN_00540c60(10, 0x1f, handle);
    handle = FUN_009f0c70(object, &localTransform.m00, handle);
    *reinterpret_cast<std::uint32_t*>(param_1 + 0x1E0) = handle;

    FUN_0043b490();
    FUN_009f01f0(0x2001, param_1, 0);

    const int createdHandle = *reinterpret_cast<int*>(param_1 + 0x1E0);
    if ((createdHandle != 0) && (*reinterpret_cast<int*>(createdHandle + 8) == 0)) {
        FUN_009e7450(createdHandle);
        FUN_007073c0();
    }

    if ((*reinterpret_cast<std::int16_t*>(reinterpret_cast<std::uintptr_t>(object) + 4) != 0) &&
        ((*reinterpret_cast<std::int16_t*>(reinterpret_cast<std::uintptr_t>(object) + 6) =
              static_cast<std::int16_t>(
                  *reinterpret_cast<std::int16_t*>(reinterpret_cast<std::uintptr_t>(object) + 6) + -1)),
         (*reinterpret_cast<std::int16_t*>(reinterpret_cast<std::uintptr_t>(object) + 6) == 0))) {
        (**reinterpret_cast<void(__thiscall***)(int)>(object))(1);
    }
}