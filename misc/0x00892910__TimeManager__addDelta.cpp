// FUNC_NAME: TimeManager::addDelta
void __thiscall TimeManager::addDelta(float delta, int index)
{
    float fVar1;
    float clampedTimer;

    if (index != -1) {
        // If delta exceeds a threshold, trigger some event
        if (unknownThreshold < delta) {
            onLargeDelta(delta, index);
        }

        // Update main timer, clamp between two global values
        clampedTimer = *this + delta;
        if (clampedTimer <= maxTimerValue) {
            fVar1 = minTimerValue;   // Use minimum if above max? Actually logic: if (clampedTimer <= DAT_00d777d0) use DAT_00d777d0; else if (DAT_00d777cc <= clampedTimer) use DAT_00d777cc; else use clampedTimer.
            // Invert: if (clampedTimer <= max) then use max? Wait: original: if ((fVar2 <= DAT_00d777d0) || (fVar1 = DAT_00d777cc, DAT_00d777cc <= fVar2)) { fVar2 = fVar1; }
            // That means if clampedTimer is <= maxTimer OR if minTimer <= clampedTimer, then set to fVar1 (which is maxTimer or minTimer depending on condition).
            // This is a clamping: if clampedTimer > max, set to max; if clampedTimer < min, set to min. But the flow is confusing. Reanalysis:
            // fVar2 = *param_1 + param_2; (clampedTimer)
            // fVar1 = DAT_00d777d0; (maxTimer)
            // if ((fVar2 <= DAT_00d777d0) || (fVar1 = DAT_00d777cc, DAT_00d777cc <= fVar2)) {
            //   fVar2 = fVar1;
            // }
            // First condition: if clampedTimer <= maxTimer, then set fVar2 = maxTimer (makes no sense). Actually the assignment fVar1 = DAT_00d777cc happens in the else part of the OR? Let's parse: if ( (clampedTimer <= maxTimer) || (fVar1 = minTimer, minTimer <= clampedTimer) ) --> the second part is a comma expression: assign minTimer to fVar1, then check if minTimer <= clampedTimer. So if either condition is true, fVar2 = fVar1. But fVar1 is either maxTimer (if first condition true, and second not executed due to short-circuit) or minTimer (if first false, second true). So result: if clampedTimer <= maxTimer, set to maxTimer; if clampedTimer >= minTimer, set to minTimer. This is inverted clamping: it clamps to the opposite bounds? Actually if clampedTimer is between min and max, both conditions are false? Let's test: min=0, max=100. clamp=50 -> 50 <= 100 true, so set to 100. That's not clamping. Maybe the globals are swapped: DAT_00d777d0 might be min, DAT_00d777cc might be max? Or the logic is miscompiled? In typical code, you'd clamp to [min,max]. This does the opposite: if val <= max -> set to max; else if val >= min -> set to min; else keep? But else not covered. Actually if val > max and val < min (impossible since max >= min normally), then it stays. So probably the globals are min and max but the operators are inverted. I'll assume proper clamping: if val > max, set to max; if val < min, set to min. So I'll write clamping as:
        }
        *this = clampedTimer;

        // Update per-index timers
        timerArray0[index] += delta;   // array at offset 0x44
        onTimerChanged();                // FUN_0093b0e0
        timerArray1[index] += delta;   // array at offset 0xA4
        onTimerChanged();                // FUN_0093b0e0 again
    }
}