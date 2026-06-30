#include <cstdint>

struct FUN_00407da0_HashNode
{
    FUN_00407da0_HashNode* next;   // [0x00]
    std::uint32_t field_0x04;      // [0x04]
    std::uint32_t field_0x08;      // [0x08]
    std::uint32_t field_0x0C;      // [0x0C]
    std::uint32_t key;             // [0x10]
};

struct FUN_00407da0_HashTable
{
    std::uint32_t field_0x00;              // [0x00]
    std::uint32_t flags;                   // [0x04]
    FUN_00407da0_HashNode** buckets;       // [0x08]
};

extern "C" FUN_00407da0_HashNode* __fastcall FUN_00407da0(
    FUN_00407da0_HashTable* param_1,
    std::uint32_t* in_EAX)
{
    FUN_00407da0_HashNode* node;

    if ((~static_cast<std::uint8_t>(param_1->flags >> 2) & 1) == 0) {
        const std::uint32_t key = *in_EAX;

        if (((param_1->flags >> 3) & 1) == 0) {
            node = param_1->buckets[key & 0x1f];

            if (node != nullptr) {
                while (node->key != key) {
                    node = reinterpret_cast<FUN_00407da0_HashNode*>(node->field_0x08);
                    if (node == nullptr) {
                        return node;
                    }
                }
            }
        }
        else {
            node = param_1->buckets[key & 0xff];

            if (node != nullptr) {
                while (node->key != key) {
                    node = reinterpret_cast<FUN_00407da0_HashNode*>(node->field_0x08);
                    if (node == nullptr) {
                        return node;
                    }
                }
            }
        }
    }
    else if (param_1->buckets == nullptr) {
        node = nullptr;
    }
    else {
        node = param_1->buckets[(*in_EAX & 3)];

        if (node != nullptr) {
            while (node->key != *in_EAX) {
                node = reinterpret_cast<FUN_00407da0_HashNode*>(node->field_0x08);
                if (node == nullptr) {
                    return node;
                }
            }
        }
    }

    return node;
}