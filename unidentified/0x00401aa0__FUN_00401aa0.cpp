#include <cstddef>
#include <cstdint>
#include <cstring>

using ReleaseFn = void(__cdecl*)(void*);

struct TempBuffer
{
    char* value;          // local_10
    std::int32_t length;  // local_c
    std::int32_t unk_08;  // local_8
    ReleaseFn release;    // local_4
};

extern std::uint8_t DAT_012051f8;
extern char DAT_0120546e[];

extern void FUN_00401b60();
extern char FUN_00401a20(TempBuffer* self);

char* FUN_00401aa0(char* dest, std::size_t len)
{
    char* pcVar3 = nullptr;

    // in_EAX mapped to len (per calling convention observation)
    if (len != 0) {
        TempBuffer temp{};
        char* pcVar2;

        if (DAT_012051f8 != 0) {
            FUN_00401b60();

            pcVar3 = temp.value;
            pcVar2 = temp.value;

            if (temp.value == nullptr) {
                pcVar2 = &DAT_0120546e;
            }

            std::strncpy(dest, pcVar2, len);
            dest[temp.length] = '\0';

            if (pcVar3 != nullptr) {
                temp.release(pcVar3);
            }

            return dest;
        }

        const char cVar1 = FUN_00401a20(&temp);
        pcVar2 = temp.value;

        if (cVar1 != 0) {
            pcVar3 = temp.value;

            if (temp.value == nullptr) {
                pcVar3 = &DAT_0120546e;
            }

            std::strncpy(dest, pcVar3, len);
            dest[temp.length] = '\0';

            pcVar3 = dest;
        }

        if (pcVar2 != nullptr) {
            temp.release(pcVar2);
        }
    }

    return pcVar3;
}