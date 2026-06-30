#include <cstdint>

struct FUN_00406d70_Object
{
    void* unknown_00;            // [0x00]
    std::uint32_t unknown_04;    // [0x04]
    std::uint32_t* freeList;     // [0x08]
    std::int32_t count;          // [0x0C]
    std::uint32_t* blockList;    // [0x10]
};

extern "C" void* FUN_009c8e50(std::uint32_t size);
extern "C" FUN_00406d70_Object* unaff_ESI;

extern "C" void FUN_00406d70(void)
{
    std::uint32_t* piVar2 = unaff_ESI->freeList;

    if (piVar2 == nullptr) {
        std::uint32_t* const block =
            static_cast<std::uint32_t*>(FUN_009c8e50(0x304));

        std::int32_t iVar3 = 0x3f;
        std::uint32_t* piVar1 = block;

        do {
            piVar1[3] = reinterpret_cast<std::uint32_t>(piVar1 + 4);
            iVar3 = iVar3 + -1;
            piVar1 = piVar1 + 3;
        } while (iVar3 != 0);

        block[0xc0] = 0;

        block[0] = reinterpret_cast<std::uint32_t>(unaff_ESI->blockList);
        unaff_ESI->blockList = block;

        piVar2 = block + 1;
        unaff_ESI->freeList = piVar2;
    }

    unaff_ESI->freeList = reinterpret_cast<std::uint32_t*>(piVar2[2]);
    piVar2[2] = 0;
    unaff_ESI->count = unaff_ESI->count + 1;
}