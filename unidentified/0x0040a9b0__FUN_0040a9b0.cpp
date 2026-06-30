extern "C" unsigned char __thiscall FUN_0040a9b0(void* this_, float param_1)
{
    struct VTable
    {
        void (__thiscall* vf0)(void*);
        void (__thiscall* vf4)(void*);
        void (__thiscall* vf8)(void*);
    };

    struct Object
    {
        VTable* vtable;          // 0x00
        int field_04;            // 0x04
        int field_08;            // 0x08
        int field_0C;            // 0x0C
        unsigned char active;    // 0x10  -> unaff_ESI[4]
        unsigned char field_11;  // 0x11
        unsigned char field_12;  // 0x12
        unsigned char field_13;  // 0x13
        int field_14;            // 0x14  (unused here, was incorrectly used before)
        int field_18;            // 0x18  -> unaff_ESI[6]
        int field_1C;            // 0x1C
        int field_20;            // 0x20
        unsigned char fired;     // 0x24  -> unaff_ESI[9]
        unsigned char pad_25;
        unsigned char pad_26;
        unsigned char pad_27;
        int field_28;            // 0x28
        int progress;            // 0x2C  -> unaff_ESI[0xb]
    };

    auto* self = static_cast<Object*>(this_);

    if (self->active != '\0') {

        if ((float)self->progress < (float)self->field_18) {
            auto fn = self->vtable->vf4;  // load first (order matters)

            self->progress = (int)((float)self->progress + param_1);

            fn(self);

            return (unsigned char)self->active;
        }

        if (self->fired == '\0') {
            auto fn = self->vtable->vf8;

            self->fired = 1;

            fn(self);
        }

        if (self->field_11 == '\0') {
            self->active = 0;
        }

        auto fn = self->vtable->vf4;
        fn(self);
    }

    return (unsigned char)self->active;
}