#include <cstdint>

struct FUN_00406a90_Node
{
    std::uint32_t key;                // [0x00]
    std::uint32_t unknown_04;         // [0x04]
    FUN_00406a90_Node* nextInBucket;  // [0x08]
};

struct FUN_00406a90_Object
{
    FUN_00406a90_Node** buckets;  // [0x00]
    std::uint32_t bucketCount;    // [0x04]
    FUN_00406a90_Node* freeList;  // [0x08]
    std::int32_t count;           // [0x0C]
};

extern "C" std::uint32_t* in_EAX;

extern "C" std::uint32_t __fastcall FUN_00406a90(FUN_00406a90_Object* this_)
{
    FUN_00406a90_Node** const bucket =
        this_->buckets + ((*in_EAX % static_cast<std::uint32_t>(this_->bucketCount)) * 1);

    FUN_00406a90_Node* current = *bucket;
    FUN_00406a90_Node* previous = nullptr;

    while (true) {
        FUN_00406a90_Node* const node = current;
        if (node == nullptr) {
            return 1;
        }

        if (node->key == *in_EAX) {
            if (previous != nullptr) {
                previous->nextInBucket = node->nextInBucket;
                node->nextInBucket = this_->freeList;
                this_->count = this_->count + -1;
                this_->freeList = node;
                return 0;
            }

            *bucket = node->nextInBucket;
            node->nextInBucket = this_->freeList;
            this_->count = this_->count + -1;
            this_->freeList = node;
            return 0;
        }

        current = node->nextInBucket;
        previous = node;
    }
}