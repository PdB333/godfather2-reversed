#include <cstddef>
#include <cstdint>

extern "C" void FUN_009c8eb0(void* ptr);

struct FUN_00406a00_Node
{
    FUN_00406a00_Node* nextFree; // [0x00]
    std::byte pad04[0x04];
    FUN_00406a00_Node* nextInBucket; // [0x08]
};

struct FUN_00406a00_Object
{
    FUN_00406a00_Node** buckets;    // [0x00]
    std::uint32_t bucketCount;      // [0x04]
    FUN_00406a00_Node* freeList;    // [0x08]
    std::int32_t unknown_0c;        // [0x0C]
    FUN_00406a00_Node* unknown_10;  // [0x10]
};

extern "C" void __thiscall FUN_00406a00(FUN_00406a00_Object* this_)
{
    std::uint32_t bucketIndex = 0;

    if (this_->bucketCount != 0) {
        do {
            FUN_00406a00_Node* node = this_->buckets[bucketIndex];
            if (node != nullptr) {
                do {
                    FUN_00406a00_Node* next = node->nextInBucket;
                    node->nextInBucket = this_->freeList;
                    this_->unknown_0c = this_->unknown_0c + -1;
                    this_->freeList = node;
                    node = next;
                } while (next != nullptr);

                this_->buckets[bucketIndex] = nullptr;
            }

            bucketIndex = bucketIndex + 1;
        } while (bucketIndex < this_->bucketCount);
    }

    FUN_00406a00_Node* current = this_->unknown_10;
    while (current != nullptr) {
        FUN_00406a00_Node* next = current->nextFree;
        FUN_009c8eb0(current);
        current = next;
    }

    this_->unknown_10 = nullptr;
    this_->freeList = nullptr;
}