// FUNC_NAME: Sequence::computeMaxValueAndAppend
undefined4 __thiscall Sequence::computeMaxValueAndAppend(int this)
{
    Keyframe *pStart;
    int count;
    Keyframe *pEnd;
    float newValue;
    float value;
    float currentMax;
    int type;

    pStart = *(Keyframe **)(this + 0xc);
    count = (int)(*(Keyframe **)(this + 8) - pStart) / 8;
    if (*(Keyframe **)(this + 8) <= pStart || pStart == nullptr)
        goto errorExit;

    if (pStart->type != 3)
    {
        if (pStart->type != 4 || !FUN_00636850(&currentMax))
            goto errorExit;
        type = 3;
        newValue = currentMax;
        pStart = (Keyframe *)&type; // point to temporary local? Actually dangerous, but likely placeholder
    }

    currentMax = pStart[1].value; // first element's value
    if (currentMax == DAT_00e2b05c) // some sentinel float constant
    {
        while (true)
        {
            pStart = *(Keyframe **)(this + 0xc);
            if (*(Keyframe **)(this + 8) <= pStart || pStart == nullptr)
                break;
            if (pStart->type == 3)
                break;
            if (pStart->type == 4 && FUN_00636850(&value))
                break;
            FUN_00627ac0(PTR_s_number_00e2a8a8); // "number" error
errorExit:
            currentMax = 0.0f;
        }
    }

    if (count > 1)
    {
        for (int i = 2; i <= count; i++)
        {
            float val = (float)FUN_006259b0(this, i);
            value = val;
            if (val == 0.0f)
            {
                // Sentinel index handling
                Keyframe *pFound = nullptr;
                if (i < 1)
                {
                    pFound = nullptr; // will be fixed below
                }
                else
                {
                    pFound = (Keyframe *)(*(int *)(this + 0xc) + -8 + i * 8);
                    if (pFound < *(Keyframe **)(this + 8))
                        goto findValid;
                }

                if (i < -9999)
                {
                    if (i == -0x2711) // -10001
                        pFound = (Keyframe *)(this + 0x40);
                    else if (i == -10000)
                        pFound = (Keyframe *)(*(int *)(this + 0x10) + 0x2c);
                    else
                    {
                        int base = *(int *)(*(int *)(this + 0xc) - 4);
                        int byteCount = *(byte *)(base + 7);
                        if (byteCount < (-0x2711 - i))
                            pFound = nullptr;
                        else
                            pFound = (Keyframe *)(base + 8 + (-0x2711 - i) * 8);
                    }
                }
                else
                {
                    pFound = (Keyframe *)(*(int *)(this + 8) + i * 8);
                }

findValid:
                while (pFound == nullptr || (pFound->type != 3 && (pFound->type != 4 || !FUN_00636850(&type))))
                {
                    // Retry with next index? Actually the loop seems flawed; similar to earlier error pattern
                    FUN_00627ac0(PTR_s_number_00e2a8a8);
                    // Note: This could be infinite if no valid, but original code may have early exit
                }
            }

            if (currentMax < value)
                currentMax = value;
        }
    }

    // Append new keyframe with currentMax
    pEnd = *(Keyframe **)(this + 8);
    pEnd->type = 3;
    pEnd->value = currentMax;
    *(Keyframe **)(this + 8) = pEnd + 1;
    return 1;
}