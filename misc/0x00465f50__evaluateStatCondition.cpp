// FUNC_NAME: evaluateStatCondition
// Address: 0x00465f50
// Role: Evaluates a condition on an array of floats (stats) at dataPtr+0x16b8,
//       compares each to a threshold at dataPtr+0x1694, returns true/false
//       based on conditionType and directionFlag.

int __fastcall evaluateStatCondition(int index, uint8_t conditionType, int dataPtr, char directionFlag)
{
    int count;
    uint8_t i;
    float* statPtr;

    // If conditionType is not 0x12 (special case that always fails)
    if (conditionType != 0x12)
    {
        // For conditionType < 0x10, delegate to a simpler check
        if (conditionType < 0x10)
        {
            // FUN_00465f00 returns true if some base condition holds
            if (FUN_00465f00() != 0)
            {
                return 1;
            }
        }
        else
        {
            // For conditionType >= 0x10, iterate over 16 stat slots
            count = 0;
            i = 0;
            statPtr = (float*)(dataPtr + 0x16b8 + index * 4);

            do
            {
                // Skip slot 0x12 (18) but loop only goes to 0x10, so always true
                if (i != 0x12)
                {
                    // Compare based on directionFlag (0 = <=, 1 = >=)
                    if (directionFlag == 0)
                    {
                        if (*statPtr <= *(float*)(dataPtr + 0x1694))
                            goto incrementCount;
                    }
                    else if (directionFlag == 1)
                    {
                        // Must be >= and not equal
                        if (*(float*)(dataPtr + 0x1694) <= *statPtr &&
                            *statPtr != *(float*)(dataPtr + 0x1694))
                        {
incrementCount:
                            count++;
                        }
                    }
                }
                i++;
                statPtr += 2;   // stride 8 bytes (2 floats)
            } while (i < 0x10);

            // Evaluate the count against conditionType
            switch (conditionType)
            {
            case 0x11:   // All 16 must satisfy the comparison
                if (count == 0x10)
                    return 1;
                break;
            case 0x12:   // Always false (already handled above, but kept for completeness)
                return 0;
            case 0x13:   // At least one satisfies
                if (count > 0)
                    return 1;
                break;
            case 0x14:   // Exactly two satisfy
                if (count == 2)
                    return 1;
                break;
            }
        }
    }
    return 0;
}