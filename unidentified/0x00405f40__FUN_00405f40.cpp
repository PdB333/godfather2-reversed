#include <cstdint>

struct FUN_00405f40_Object
{
    std::int32_t values[0x10];      // [0x00] .. [0x3C]
    std::int32_t count;             // [0x40]
    std::int32_t extraValue;        // [0x44]
};

struct FUN_00405f40_ListNode
{
    std::uint8_t pad00[0x04];       // [0x00]
    std::int32_t next;              // [0x04]
    std::uint8_t pad08[0x14];       // [0x08] .. [0x1B]
    std::int32_t value;             // [0x1C]
    std::uint8_t pad20[0x0C];       // [0x20] .. [0x2B]
    std::int32_t key;               // [0x2C]
};

struct FUN_00405f40_GlobalState
{
    std::uint8_t pad00[0x6C];
    std::int32_t listHead;          // [0x6C]
    std::uint8_t pad70[0x10];
    std::int32_t cachedNode;        // [0x80]
};

extern FUN_00405f40_GlobalState* DAT_0122337c;

std::int32_t __fastcall FUN_00405f40(FUN_00405f40_Object* self)
{
    const std::int32_t key =
        *reinterpret_cast<std::int32_t*>(
            *reinterpret_cast<std::int32_t*>(
                self->values[self->count]
            )
        );

    std::int32_t nodeValue = DAT_0122337c->cachedNode;

    if ((nodeValue == 0) || (reinterpret_cast<FUN_00405f40_ListNode*>(nodeValue)->key != key))
    {
        nodeValue = DAT_0122337c->listHead;

        while (true)
        {
            if (nodeValue == 0)
            {
                return 0;
            }

            if (reinterpret_cast<FUN_00405f40_ListNode*>(nodeValue)->key == key)
            {
                break;
            }

            nodeValue = reinterpret_cast<FUN_00405f40_ListNode*>(nodeValue)->next;
        }
    }

    return reinterpret_cast<FUN_00405f40_ListNode*>(nodeValue)->value;
}