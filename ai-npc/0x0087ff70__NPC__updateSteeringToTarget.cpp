// FUNC_NAME: NPC::updateSteeringToTarget
void __thiscall NPC::updateSteeringToTarget(int thisPtr, int* pTargetEntity, float* pTargetPosition) {
    int currentTime = g_GlobalTime; // 0x01205224
    if (((*(int*)(thisPtr + 0x200) == 0) || (currentTime - *(int*)(thisPtr + 0x200) > 4000)) &&
        (**(int**)g_SomeGlobalPointers[1] != 0)) {
        int* pGlobalEntity = *(int**)(**(int**)g_SomeGlobalPointers[1] + -0x1f30); // +4 then offset
        if (pGlobalEntity != nullptr) {
            int iVar4 = FUN_00471610(); // returns some object
            // Get position from pTargetEntity via vtable[0x4c]
            float targetPos[3];
            (**(code**)(*pTargetEntity + 0x4c))(targetPos);
            // Compare squared distance from pTargetEntity to pTargetPosition
            float diffX = *(float*)(iVar4 + 0x30) - pTargetPosition[0];
            float diffY = *(float*)(iVar4 + 0x34) - pTargetPosition[1];
            float diffZ = *(float*)(iVar4 + 0x38) - pTargetPosition[2];
            float sqDist = diffX * diffX + diffY * diffY + diffZ * diffZ;
            if (sqDist < *(float*)(thisPtr + 0x1fc)) {
                int local_10 = g_SomeConstant; // 0x00d76acc (unused)
                // Get position from pGlobalEntity via vtable[0x4c]
                float globalPos[3];
                (**(code**)(*pGlobalEntity + 0x4c))(globalPos);
                // Compute difference between targetPos and globalPos?
                float localDiff[3];
                localDiff[0] = targetPos[0] - globalPos[1]; // Note: odd indexing, may be decompiler artifact
                localDiff[1] = m_positionY - globalPos[2]; // unaff_ESI -> m_positionY
                localDiff[2] = m_positionZ - globalPos[0]; // unaff_EBP -> m_positionZ
                float sqLen = localDiff[0] * localDiff[0] + localDiff[1] * localDiff[1] + localDiff[2] * localDiff[2];
                if (*(float*)(thisPtr + 0x1f8) <= sqLen && sqLen != *(float*)(thisPtr + 0x1f8)) {
                    float rangeSq = *(float*)(thisPtr + 0x1fc);
                    char result = FUN_0087f5b0(localDiff, pTargetPosition, localDiff, *(int*)(thisPtr + 0x1f0), *(int*)(thisPtr + 500));
                    if (result != 0) {
                        FUN_0087f7c0(localDiff, *reinterpret_cast<float(*)[12]>(localDiff), thisPtr + 0x1cc, thisPtr + 0x1dc, *(int*)(thisPtr + 0x204));
                    }
                }
                *(int*)(thisPtr + 0x200) = currentTime;
            }
        }
    }
}