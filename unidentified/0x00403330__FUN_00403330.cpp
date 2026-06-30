#include <cstdint>

using uint = std::uint32_t;

struct FUN_00403330_Object
{
    void** vftable;                  // +0x00
    void** secondaryVftable;         // +0x04
    std::uint8_t pad_08[0x3c];
    void* member_44;                 // +0x44
    std::uint8_t pad_48[0x0c];
    void* member_54;                 // +0x54
};

struct FUN_00486cd0_Context
{
    FUN_00403330_Object* object;
    uint cookie;
    void (__fastcall* callback)();
    void* label;
};

extern void* PTR_FUN_00e2f0d0;
extern void* PTR_FUN_00e2f0d4;
extern void* PTR_LAB_00e2f0dc;

extern void* DAT_01223380;
extern std::uint32_t DAT_0122337c;

extern std::uint8_t DAT_01206760;
extern std::uint8_t DAT_01206768;
extern std::uint8_t DAT_01206770;
extern std::uint8_t DAT_01206778;
extern std::uint8_t DAT_01206780;
extern std::uint8_t DAT_0120678c;
extern std::uint8_t DAT_01206794;
extern std::uint8_t DAT_0120679c;
extern std::uint8_t DAT_012067a4;
extern std::uint8_t DAT_012067ac;
extern std::uint8_t DAT_012067b4;

extern "C" void __fastcall FUN_00404fe0();
extern "C" void* LAB_00407730;

extern void FUN_00486cd0(void* param_1, FUN_00486cd0_Context* param_2);
extern void FUN_00408310(void* param_1);
extern void FUN_004034c0();
extern void FUN_00407430();
extern void FUN_00406a00();
extern void FUN_009c8f10(void* param_1);
extern void FUN_004de130();

void __fastcall FUN_00403330(FUN_00403330_Object* self)
{
    FUN_00486cd0_Context local_1c;

    self->vftable = static_cast<void**>(&PTR_FUN_00e2f0d0);

    local_1c.label = &LAB_00407730;
    local_1c.cookie = 0x2a7ed975;
    local_1c.callback = FUN_00404fe0;
    local_1c.object = self;

    FUN_00486cd0(DAT_01223380, &local_1c);

    FUN_00408310(&DAT_01206770);
    FUN_00408310(&DAT_0120679c);
    FUN_00408310(&DAT_0120678c);
    FUN_00408310(&DAT_012067a4);
    FUN_00408310(&DAT_01206768);
    FUN_00408310(&DAT_012067b4);
    FUN_00408310(&DAT_01206778);
    FUN_00408310(&DAT_012067ac);
    FUN_00408310(&DAT_01206780);
    FUN_00408310(&DAT_01206760);
    FUN_00408310(&DAT_01206794);

    FUN_004034c0();
    FUN_00407430();
    FUN_00406a00();

    FUN_009c8f10(self->member_54);

    if (self->member_44 != nullptr) {
        FUN_009c8f10(self->member_44);
    }

    self->secondaryVftable = static_cast<void**>(&PTR_FUN_00e2f0d4);

    FUN_004de130();

    self->vftable = static_cast<void**>(&PTR_LAB_00e2f0dc);
    DAT_0122337c = 0;
}