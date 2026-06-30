#include <cstdint>
#include <cstring>

struct HashNode
{
    std::uint32_t key;  // [0x00]
    std::uint32_t unk;  // [0x04]
    HashNode* next;     // [0x08]
};

struct FUN_00406dd0_Object
{
    HashNode** buckets;       // [0x00]
    std::int32_t bucketCount; // [0x04]
};

extern "C" void* FUN_009c8e80(std::uint32_t size);
extern "C" void FUN_009c8f10(void* ptr);

extern "C" void FUN_00406dd0(FUN_00406dd0_Object* this_)
{
    FUN_00406dd0_Object* piVar5 = this_;

    const std::uint32_t uVar2 =
        static_cast<std::uint32_t>(this_->bucketCount * 2 + 1);

    const std::uint64_t mul = static_cast<std::uint64_t>(uVar2) * 4;

    void* const _Dst =
        FUN_009c8e80(
            (static_cast<std::uint32_t>(
                 -static_cast<std::uint32_t>((static_cast<std::uint32_t>(mul >> 32) != 0)))) |
            static_cast<std::uint32_t>(mul));

    std::memset(_Dst, 0, uVar2 * 4);

    if (this_->bucketCount != 0) {
        std::uint32_t i = 0;
        do {
            HashNode* puVar4 = this_->buckets[i];

            while (puVar4 != nullptr) {
                HashNode* const puVar3 = puVar4->next;

                puVar4->next =
                    reinterpret_cast<HashNode**>(_Dst)[puVar4->key % uVar2];

                reinterpret_cast<HashNode**>(_Dst)[puVar4->key % uVar2] = puVar4;

                puVar4 = puVar3;
            }

            i = i + 1;
        } while (i < static_cast<std::uint32_t>(piVar5->bucketCount));
    }

    FUN_009c8f10(this_->buckets);

    this_->buckets = static_cast<HashNode**>(_Dst);
    piVar5->bucketCount = static_cast<std::int32_t>(uVar2);
}