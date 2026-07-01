// Xbox PDB: EARS_Apt_UIRatingPopup_HandleInput
// FUNC_NAME: PlayerReputationTracker::updateRating
// Address: 0x00983460
// Role: Updates a rating value (e.g., reputation/heat) with clamping and callback support.
// Offsets:
//   +0x50 (param_1[0x14]): callback function pointer (optional)
//   +0x5C (param_1[0x17]): rating value (stored as int, used as float)
//   vtable+0x2C: virtual method (likely update or apply)

int __thiscall PlayerReputationTracker::updateRating(int* thisPtr, int param2)
{
    float fVar1;
    float fVar2;
    int currentEventId;
    float fVar4;

    currentEventId = getCurrentEventId(); // FUN_00466840
    if (param2 == currentEventId) {
        // If param2 matches current event, invoke callback and virtual update
        if ((code*)thisPtr[0x14] != (code*)0x0) {
            ((void (*)(int, int*))thisPtr[0x14])(thisPtr[0x17], thisPtr);
        }
        (**(code**)(*thisPtr + 0x2c))(); // virtual call
        return 0;
    }

    fVar1 = (float)thisPtr[0x17]; // current rating
    if (param2 == 6) {
        fVar4 = fVar1 - gRatingStep; // DAT_00d90850
    }
    else {
        if (param2 != 7) goto LAB_009834e1;
        fVar4 = fVar1 + gRatingStep; // DAT_00d90850
    }

    fVar2 = gRatingStep; // DAT_00d90850
    if ((fVar4 < gRatingStep) || (fVar2 = gRatingMax, gRatingMax < fVar4)) {
        fVar4 = fVar2; // clamp to min or max
    }
    thisPtr[0x17] = (int)fVar4;

LAB_009834e1:
    if (fVar1 != (float)thisPtr[0x17]) {
        logRatingUpdate("UpdateRating", 0, &gRatingUpdateParam, 0); // FUN_005a04a0
    }
    return 0;
}