#include <cstdint>
#include <cstring>

struct FUN_00405650_Node
{
    FUN_00405650_Node* next;   // [0]
    const char*        unk4;   // [1]
    const char*        name;   // [2]
    std::uint32_t      hasName;// [3]
};

struct FUN_00405650_SearchKey
{
    const char*   name;     // [0]
    std::uint32_t hasName;  // [1]
};

FUN_00405650_Node* __fastcall FUN_00405650(FUN_00405650_Node** in_EAX,
                                           FUN_00405650_SearchKey* unaff_EDI)
{
    FUN_00405650_Node* node = *in_EAX;

    do
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        std::uint32_t cmp;

        if (node->hasName == 0)
        {
            cmp = static_cast<std::uint32_t>(unaff_EDI->hasName != 0);
        }
        else
        {
            if (unaff_EDI->hasName == 0)
            {
LAB_00405686:
                cmp = 0xFFFFFFFFu;
            }
            else
            {
                const char* lhs = node->name;
                const char* rhs = unaff_EDI->name;

                if ((lhs == nullptr) || (rhs == nullptr))
                {
                    if (lhs >= rhs && lhs != rhs)
                    {
                        goto LAB_00405686;
                    }

                    cmp = static_cast<std::uint32_t>(lhs < rhs);
                }
                else
                {
                    cmp = static_cast<std::uint32_t>(_stricmp(lhs, rhs));
                }
            }
        }

        if (cmp == 0)
        {
            return node;
        }

        node = node->next;

    } while (true);
}