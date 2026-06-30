// FUNC_NAME: AnimationController::updateBlendState
void AnimationController::updateBlendState(float blendFactor) // in_XMM4_Da passed from caller (likely XMM4)
{
    float normalizedBlend = blendFactor / *(float*)(this + 0x2c); // +0x2c: blend divisor
    int state = *(int*)(this + 0x28); // +0x28: blend state ID

    switch (state)
    {
    case 1: // Reset blend?
        unknownFunction1(); // FUN_00b99fcb
        return;

    case 2: // Apply external effect?
        unknownFunction2(*(undefined4*)(esi + 8), *(undefined4*)(esi + 0xc)); // esi likely points to an animation data structure
        return;

    case 3: // Clamp threshold checks (seems to always return, possibly a stub)
        if (globalBlendMax < normalizedBlend) return; // DAT_00e2b198
        if (normalizedBlend <= globalBlendMin) // DAT_00e2cd54
        {
            if (normalizedBlend <= globalBlendThreshold) // DAT_00e35654
                return;
            return;
        }
        return;

    case 4: // Linear interpolation with clamping
        {
            float interp1 = *(float*)(this + 0x4c) * normalizedBlend + *(float*)(this + 0x48);
            float interp2 = *(float*)(this + 0x54) * normalizedBlend + *(float*)(this + 0x50);
            if (interp1 < interp2)
                interp2 = interp1;
            if (interp2 < *(float*)(this + 0x44)) return;
            if (*(float*)(this + 0x40) < interp2) return;
            // Possibly store result? But no output operation visible.
        }
        break;

    case 5: // Countdown (likely a timing or animation step loop)
        {
            int count = (int)*(float*)(this + 0x3c); // +0x3c: timer or loop count
            if (*(float*)(this + 0x3c) <= 0.0f)
            {
                count = -count; // abs
                if (count > 7)
                {
                    int blocks = (count - 8) / 8 + 1;
                    int total = blocks * 8;
                    do { blocks--; } while (blocks != 0); // empty loop (no-op)
                    if (total < count)
                    {
                        int remainder = count - total;
                        do { remainder--; } while (remainder != 0); // empty loop
                    }
                }
            }
            else
            {
                if (count > 7)
                {
                    int blocks = (count - 8) / 8 + 1;
                    int total = blocks * 8;
                    do { blocks--; } while (blocks != 0);
                }
                if (count % 8 != 0)
                {
                    int remainder = count % 8;
                    do { remainder--; } while (remainder != 0);
                }
            }
        }
        break;
    }
}