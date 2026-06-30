#include <cstdint>

using CleanupCallback = void(__cdecl*)(int);

struct FUN_00401a20_Object
{
    void* resource;                       // +0x00
    std::int32_t unk_04;                 // +0x04
    std::int32_t unk_08;                 // +0x08
    void (__cdecl* release)(void*);      // +0x0c
};

extern void FUN_004d3bc0(void* param_1);
extern void FUN_004d3d90(std::int32_t param_1);
extern void FUN_004d5900(std::int32_t param_1);
extern std::uint8_t DAT_00e2f044;

bool FUN_00401a20(FUN_00401a20_Object* self, std::int32_t param_2)
{
    bool result = false;
    int local_14;
    CleanupCallback pcStack_8;

    if (self->resource != nullptr) {
        self->release(self->resource);
    }

    self->resource = nullptr;
    self->unk_08 = 0;
    self->unk_04 = 0;

    if (param_2 != 0) {
        FUN_004d3bc0(&DAT_00e2f044);
        FUN_004d3d90(param_2);
        FUN_004d5900(1);
        result = true;

        if (local_14 != 0) {
            pcStack_8(local_14);
        }
    }

    return result;
}