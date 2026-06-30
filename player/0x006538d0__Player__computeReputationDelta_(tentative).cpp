// FUNC_NAME: Player::computeReputationDelta (tentative)
// Function address: 0x006538d0
// Calculates a clamped product of two min/max values and scales it, capped at 1024.
// Offsets: +0xd4 (min1), +0xe8 (max1), +0xdc (min2), +0xf0 (max2), +0xfc (output), +0xf8 (finalValue)
// Global constants: DAT_00e44578 (rounding correction), DAT_00e2e210 (scale factor)

extern float DAT_00e44578; // likely 0.5 or 1.0 for rounding
extern float DAT_00e2e210; // scaling multiplier

void __thiscall Player::computeReputationDelta(Player* thisPtr)
{
    float fVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned int local_8;

    // uVar2 = max(source1_min, source1_max) ? Actually the logic:
    // if (*(uint *)(param_1 + 0xe8) < *(uint *)(param_1 + 0xd4)) { uVar2 = *(uint *)(param_1 + 0xd4); }
    // So uVar2 = max(*(+0xE8), *(+0xD4))
    uVar2 = *(unsigned int*)(thisPtr + 0xE8);
    if (*(unsigned int*)(thisPtr + 0xE8) < *(unsigned int*)(thisPtr + 0xD4)) {
        uVar2 = *(unsigned int*)(thisPtr + 0xD4);
    }
    *(unsigned int*)(thisPtr + 0xFC) = uVar2; // store max as some intermediate value

    // uVar3 = min(source2_min, source2_max) ? Logic:
    // if (*(uint *)(param_1 + 0xdc) <= *(uint *)(param_1 + 0xf0)) { uVar3 = *(uint *)(param_1 + 0xdc); }
    // So uVar3 = min(*(+0xDC), *(+0xF0))
    uVar3 = *(unsigned int*)(thisPtr + 0xF0);
    if (*(unsigned int*)(thisPtr + 0xDC) <= *(unsigned int*)(thisPtr + 0xF0)) {
        uVar3 = *(unsigned int*)(thisPtr + 0xDC);
    }

    // product = uVar2 * uVar3 (may overflow int, but cast to int later)
    int product = (int)(uVar2 * uVar3);
    fVar1 = (float)product; // convert to float

    // if product < 0, add rounding correction (likely for negative values)
    if (product < 0) {
        fVar1 = fVar1 + DAT_00e44578;
    }

    // scale and round to nearest integer
    local_8 = (unsigned int)(long long)ROUND(fVar1 * DAT_00e2e210);
    *(unsigned int*)(thisPtr + 0xF8) = local_8;

    // cap at 1024 (0x400)
    if (0x400 < local_8) {
        *(unsigned int*)(thisPtr + 0xF8) = 0x400;
    }
    return;
}