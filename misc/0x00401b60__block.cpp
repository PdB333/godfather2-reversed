#include <cstdint>
#include <cstring>

using ReleaseFn = void(__cdecl*)(void*);
using CleanupCallback = void(__cdecl*)(int);

struct TempBuffer
{
    char* value;               // +0x00
    std::int32_t length;       // +0x04
    std::int32_t unk_08;       // +0x08
    ReleaseFn release;         // +0x0c
};

extern char DAT_0120546e[];
extern std::uint8_t DAT_00e2f048;
extern std::uint8_t DAT_00e2f04c;

extern void* FUN_004d3bc0(const char* param_1);
extern void FUN_004d3e20(void* param_1);
extern void FUN_004d4c00(void* param_1, void* param_2);
extern void FUN_004d3d90(const char* param_1);

bool __cdecl block(TempBuffer* self, char* path)
{
    bool result = false;
    int local_14;
    CleanupCallback pcStack_8;

    if (self->value != nullptr) {
        self->release(self->value);
    }

    self->value = nullptr;
    self->unk_08 = 0;
    self->length = 0;

    if (path != nullptr) {
        char* colon = std::strrchr(path, ':');
        if (colon != nullptr) {
            path = colon + 1;
        }

        void* parsed = FUN_004d3bc0(path);
        FUN_004d3e20(parsed);

        if (local_14 != 0) {
            pcStack_8(local_14);
        }

        FUN_004d4c00(&DAT_00e2f04c, &DAT_00e2f048);

        char* trimmed = DAT_0120546e;
        while ((*trimmed != '\0') && (*trimmed == '\\')) {
            ++trimmed;
        }

        FUN_004d3d90(trimmed);
        result = true;
    }

    return result;
}