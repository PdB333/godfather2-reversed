// FUN_00718360: CoverState::executeCoverMovement
void __thiscall CoverState::executeCoverMovement(
    Sentient* pCharacter,          // param_2
    ActionData* pActionData,       // param_3
    int param4,                    // param_4
    Vector3* pTargetPoint          // param_5 (optional)
)
{
    int iVar1;
    float fDistance;
    Vector3 localVector;            // local_14 + local_c (16 bytes)
    bool bFlag;                     // local_8

    if (pCharacter != nullptr) {
        // Set the character's movement target from action data at offset +0x50
        SetMovementTarget(pCharacter, *(uint*)(pActionData + 0x50));

        if (pTargetPoint != nullptr) {
            // Copy the optional target point into a local vector and set flag
            localVector = *pTargetPoint;
            bFlag = true;
        }

        // Compute action parameters (direction, time offset, etc.)
        ComputeActionParameters(pActionData, param4, (uint8*)&localVector);

        // Virtual function call through the AI interface vtable (offset 0xBC)
        fDistance = (*(float (__thiscall**)(Sentient*))(
            *(int**)(*(int*)(this + 0x18)) + 0x2F
        ))(pCharacter);

        if (fDistance != 0.0f) {
            iVar1 = IsInCoverState(pCharacter);  // FUN_0071ce70
            if (iVar1 == 0) {
                EnterCoverState();                // FUN_0071ce20
            }
            if (pTargetPoint == nullptr) {
                // Allocate a temporary cover point buffer
                iVar1 = AllocateTempCoverPoint();  // FUN_00471610
                pTargetPoint = (Vector3*)(iVar1 + 0x30);
            }

            // Select cover ID based on character flag at +0x5C bit 3
            uint coverID = g_DefaultCoverID;       // DAT_00d5ccf8
            if ((pCharacter->flags & 0x08) != 0) { // flag at offset 0x5C
                coverID = g_AlternativeCoverID;    // DAT_01205228
            }

            if (pTargetPoint == nullptr) {
                ApplyCoverActionNoTarget(*(uint*)(this + 0x18), pCharacter, coverID); // FUN_0071c720
            } else {
                ApplyCoverActionAtPoint(*(uint*)(this + 0x18), pCharacter, coverID, pTargetPoint); // FUN_0071c440
            }
        }

        // Destructor for the local vector (smart pointer or temporary)
        if (localVector._raw[0] != 0) {
            DestroyVector(&localVector); // FUN_004daf90
        }
    }
}