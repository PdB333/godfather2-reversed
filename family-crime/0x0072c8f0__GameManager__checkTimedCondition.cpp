// FUNC_NAME: GameManager::checkTimedCondition
void __thiscall GameManager::checkTimedCondition(GameManager *this, char param_2) {
    int *timePtr1 = (int *)getSimTimePointer();   // FUN_00471610: returns pointer to sim time struct
    int *timePtr2 = (int *)getSimTimePointer();   // same function
    float timeDiff = *(float *)(timePtr1 + 0x34) - *(float *)(timePtr2 + 0x34); // +0x34: mLastFrameTime
    uint maskedDiff = (uint)timeDiff & DAT_00e44680; // likely 0x7FFFFFFF for absolute diff
    if ((float)maskedDiff < DAT_00d5eee4) { // timeThreshold
        float angle = getAngleOrDistance((char *)(timePtr2 + 0x30)); // FUN_004702b0, +0x30: mAngleOffset
        if (angle <= DAT_00d62b5c && param_2 != '\0') { // angleThreshold and flag
            // Virtual call at vtable offset 0x4c (method index 19)
            char local_c[12]; // buffer for return/action
            ((void (__thiscall *)(GameManager *, char *))this->vtable[0x4c])(this, local_c);
        }
    }
}