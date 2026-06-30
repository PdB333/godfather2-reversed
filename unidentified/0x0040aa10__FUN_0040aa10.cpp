extern "C" long double __fastcall FUN_0040aa10(void* param_1)
{
    struct Object
    {
        void* vtable;            // 0x00
        int field_04;            // 0x04
        int field_08;            // 0x08
        int field_0C;            // 0x0C
        unsigned char active;    // 0x10
        unsigned char field_11;  // 0x11
        unsigned char field_12;  // 0x12
        unsigned char field_13;  // 0x13
        int field_14;            // 0x14
        float field_18;          // 0x18
        int field_1C;            // 0x1C
        int field_20;            // 0x20
        unsigned char fired;     // 0x24
        unsigned char pad_25;    // 0x25
        unsigned char pad_26;    // 0x26
        unsigned char pad_27;    // 0x27
        int field_28;            // 0x28
        float progress;          // 0x2C
    };

    auto* self = static_cast<Object*>(param_1);

    if (self->active != 0) {
        if (self->progress < self->field_18) {
            const long double ratio =
                static_cast<long double>(self->progress) /
                static_cast<long double>(self->field_18);

            if (self->field_14 == 0) {
                return ratio;
            }

            return static_cast<long double>(1.0) - ratio;
        }

        if (self->field_14 == 0) {
            return static_cast<long double>(1.0);
        }
    }

    return static_cast<long double>(0.0);
}