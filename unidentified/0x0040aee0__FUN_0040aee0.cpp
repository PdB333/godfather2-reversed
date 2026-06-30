extern "C" void __thiscall FUN_0040aee0(void* this_, unsigned int param_1, unsigned int param_2)
{
    struct PendingCall
    {
        unsigned int arg0; // 0x00
        unsigned int arg1; // 0x04
        unsigned int arg2; // 0x08
        float arg3;        // 0x0C
    };

    auto* self = static_cast<PendingCall*>(this_);

    if (DAT_00e2af44 < self->arg3) {
        FUN_00516160(self->arg0, self->arg1, self->arg2, self->arg3, param_1, param_2);
        DAT_012066d0 = DAT_012066d0 + DAT_00e2b1a4;
    }
}