#include <cstdint>

using uint = std::uint32_t;

struct HashNode
{
    uint key;        // +0x00
    uint value;      // +0x04
    uint next;       // +0x08
};

struct HashTable
{
    std::uint8_t pad_00[0x50];
    HashNode** buckets;   // +0x50
    uint bucketCount;     // +0x54
};

extern HashTable* DAT_0122337c;
extern void FUN_00402f40(int, int);

void FUN_00402c90(int param_1)
{
    uint uVar1;
    HashNode* puVar2;
    uint uVar3;
    uint uVar4;
    uint uVar5;
    uint* puVar6;
    uint uVar7;

    uVar7 = 0;
    if (*(int*)(param_1 + 0xec) != 0) {
        puVar6 = reinterpret_cast<uint*>(param_1 + 0x78);

LAB_00402cb0:
        uVar1 = *puVar6;
        if (uVar1 != 0) {
            for (puVar2 = DAT_0122337c->buckets[uVar1 % DAT_0122337c->bucketCount];
                 puVar2 != nullptr;
                 puVar2 = reinterpret_cast<HashNode*>(puVar2->next)) {
                if (puVar2->key == uVar1) {
                    if ((puVar2 != nullptr) && ((uVar1 = puVar2->value), uVar1 != 0)) {
                        uVar5 = *(uint*)(uVar1 + 0x74);
                        uVar4 = 0;
                        if (uVar5 != 0) {
                            goto LAB_00402cf4;
                        }
                    }
                    break;
                }
            }
        }
        goto LAB_00402d30;
    }

LAB_00402d42:
    uVar7 = 0;
    if (*(int*)(param_1 + 0x74) == 0) {
        return;
    }
    puVar6 = reinterpret_cast<uint*>(param_1 + 100);

LAB_00402d50:
    uVar1 = *puVar6;
    if (uVar1 != 0) {
        for (puVar2 = DAT_0122337c->buckets[uVar1 % DAT_0122337c->bucketCount];
             puVar2 != nullptr;
             puVar2 = reinterpret_cast<HashNode*>(puVar2->next)) {
            if (puVar2->key == uVar1) {
                if ((puVar2 != nullptr) && ((uVar1 = puVar2->value), uVar1 != 0)) {
                    uVar5 = *(uint*)(uVar1 + 0xec);
                    uVar4 = 0;
                    if (uVar5 != 0) {
                        goto LAB_00402db0;
                    }
                }
                break;
            }
        }
    }
    goto LAB_00402e79;

    while (uVar4 = uVar4 + 1, uVar4 < uVar5) {
LAB_00402cf4:
        if (*(int*)(uVar1 + 100 + uVar4 * 4) == *(int*)(param_1 + 0x1c)) {
            if ((uVar4 != 0xffffffff) && (uVar4 < uVar5)) {
                if (uVar4 < uVar5 - 1) {
                    do {
                        *(std::uint32_t*)(uVar1 + 100 + uVar4 * 4) =
                            *(std::uint32_t*)(uVar1 + 0x68 + uVar4 * 4);
                        uVar4 = uVar4 + 1;
                    } while (uVar4 < *(int*)(uVar1 + 0x74) - 1U);
                }
                *(int*)(uVar1 + 0x74) = *(int*)(uVar1 + 0x74) + -1;
            }
            break;
        }
    }

LAB_00402d30:
    uVar7 = uVar7 + 1;
    puVar6 = puVar6 + 1;
    if (*(uint*)(param_1 + 0xec) <= uVar7) {
        goto LAB_00402d42;
    }
    goto LAB_00402cb0;

    while (uVar4 = uVar4 + 1, uVar4 < uVar5) {
LAB_00402db0:
        if (*(int*)(uVar1 + 0x78 + uVar4 * 4) == *(int*)(param_1 + 0x1c)) {
            if (uVar4 != 0xffffffff) {
                if (uVar4 < uVar5) {
                    uVar3 = uVar4;
                    if (uVar4 < uVar5 - 1) {
                        do {
                            *(std::uint32_t*)(uVar1 + 0x78 + uVar3 * 4) =
                                *(std::uint32_t*)(uVar1 + 0x7c + uVar3 * 4);
                            uVar3 = uVar3 + 1;
                        } while (uVar3 < *(int*)(uVar1 + 0xec) - 1U);
                    }
                    *(int*)(uVar1 + 0xec) = *(int*)(uVar1 + 0xec) + -1;
                }
                uVar5 = (1 << (static_cast<std::uint8_t>(uVar4) & 0x1f)) - 1;
                uVar5 = *(uint*)(uVar1 + 0x60) >> 1 & ~uVar5 & 0x1fffffff |
                        *(uint*)(uVar1 + 0x60) & 0xc0000000 |
                        *(uint*)(uVar1 + 0x60) & uVar5;
                *(uint*)(uVar1 + 0x60) = uVar5;
                if ((((-1 < static_cast<int>(uVar5)) &&
                      ((~static_cast<std::uint8_t>(uVar5 >> 0x1e) & 1) != 0)) &&
                     (*(int*)(uVar1 + 0x24) == 3)) &&
                    ((uVar5 & (1 << (static_cast<std::uint8_t>(*(std::uint32_t*)(uVar1 + 0xec)) & 0x1f)) - 1U) == 0)) {
                    *(uint*)(uVar1 + 0x60) = uVar5 | 0x80000000;
                    FUN_00402f40(0x100, 1);
                }
            }
            break;
        }
    }

LAB_00402e79:
    uVar7 = uVar7 + 1;
    puVar6 = puVar6 + 1;
    if (*(uint*)(param_1 + 0x74) <= uVar7) {
        return;
    }
    goto LAB_00402d50;
}