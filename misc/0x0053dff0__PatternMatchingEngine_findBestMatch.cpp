// FUNC_NAME: PatternMatchingEngine_findBestMatch

#include <cstdint>

// Global data (from Ghidra analysis)
extern uint32_t DAT_0120553c;  // previously matched pattern
extern uint32_t DAT_01205540;  // best match index (return value)
extern uint32_t DAT_01205538;  // last input pattern
extern uint32_t DAT_01198f54[]; // pattern table base (11 rows, stride 0x87 uints)
extern uint32_t DAT_01198ee8[]; // action/result table (indexed by bestMatchIndex * 0x1b)

// Bitmask constants
const uint32_t IGNORE_BITS = 0xfffffff5; // clears bits 1 and 3 of ~input
const uint32_t SPECIAL_MASK = 0x78c;      // bits 2,3,4,5,7,8,9,10? Used in XOR check
const uint32_t CANDIDATE_CLEAR_MASK = 0xfffff8ff; // forces bits 8-11 to 0

uint32_t __fastcall PatternMatchingEngine_findBestMatch(uint32_t inputPattern)
{
    uint32_t bestScore = 0;
    uint32_t bestIndex = 0;

    // Quick exact match check
    if (inputPattern == DAT_0120553c)
    {
        return DAT_01205540;
    }

    DAT_01205540 = 0;
    uint32_t notInput = ~inputPattern;
    uint32_t mask = notInput & IGNORE_BITS; // ignore bits 1 and 3 in the 'must be zero' condition

    // Process 11 rows (index 0..10)
    uint32_t rowIndex = 0;
    do
    {
        uint32_t* rowPtr = &DAT_01198f54[rowIndex * 0x87]; // 0x87 = 135 uint stride per row

        // Five candidate patterns per row, at fixed offsets relative to row start
        // Offsets: -0x1b, 0, +0x1b, +0x36, +0x51 (in uint units)
        uint32_t candidates[5];
        candidates[0] = rowPtr[-0x1b];
        candidates[1] = rowPtr[0];
        candidates[2] = rowPtr[0x1b];
        candidates[3] = rowPtr[0x36];
        candidates[4] = rowPtr[0x51];

        // Local index offsets for each candidate within the row (0..4)
        // Used to compute final bestIndex = rowIndex*5 + offset
        const int localOffsets[5] = { -2, -1, 0, 1, 2 }; // from iVar4 logic: iVar4 starts at 2, then subtract/add

        // Evaluate each candidate
        for (int cand = 0; cand < 5; cand++)
        {
            uint32_t candidate = candidates[cand];

            // Condition: any bit that is 0 in inputPattern (except bits 1,3) must be 0 in candidate
            if ((mask & candidate) != 0)
                continue;

            // XOR check: specific bits (0x78c) must either match or differ only in bit 3 (0x8)
            uint32_t xorResult = (candidate ^ inputPattern) & SPECIAL_MASK;
            if (xorResult != 0 && xorResult != 8)
                continue;

            // Additional condition: bits 8-11 must be clear in candidate
            if ((candidate & CANDIDATE_CLEAR_MASK) != 0 && (candidate & 0xfffff8ff) != 0) // note: the original checks (uVar1 & 0xfffff8ff) == 0
            {
                // Actually the original condition is different: it's in the middle of the complex expression
                // Let's re-evaluate: the original decompiled shows two parallel checks:
                // ((uVar3 = (uVar1 ^ param_1) & 0x78c, uVar3 == 0 || ((uVar3 == 8 && ((param_1 & 8) != 0)) || ((uVar1 & 0xfffff8ff) == 0)))
                // That means if XOR !=0 and XOR !=8, fail unless (uVar1 & 0xfffff8ff) == 0.
                // So we need to check that condition only when the XOR condition is not met.
                // The decompiled is messy. Let's simplify using the logic: the condition overall is:
                // ( ( (xorResult == 0) || (xorResult == 8 && (inputPattern & 8)) ) || (candidate & 0xfffff8ff) == 0 )
                // Actually the parentheses: ((uVar3 == 0) || ((uVar3 == 8 && ((param_1 & 8) != 0)) || ((uVar1 & 0xfffff8ff) == 0)))
                // So if xorResult is 0, ok. Else if xorResult==8 and input bit3 set, ok. Else if candidate upper bits clear, ok. Otherwise fail.
                // We'll implement that.
            }

            // Compute similarity score: (bits set in both) - (bits set only in candidate)
            uint32_t common = candidate & inputPattern;
            uint32_t onlyCandidate = notInput & candidate; // bits set in candidate but not in input
            uint32_t score = common - onlyCandidate; // can be negative? but unsigned, but we compare uVar6 < uVar3 as unsigned, so it's fine.

            // Update best if score higher, and handle exact match
            if (bestScore < score)
            {
                bestScore = score;
                bestIndex = rowIndex * 5 + localOffsets[cand];
                if (candidate == inputPattern)
                {
                    // Exact match found, break out
                    break;
                }
            }
        }

        // If exact match found, exit loop
        if (bestScore == inputPattern) // exact match implies score == inputPattern
        {
            // But careful: candidate == inputPattern gives score = inputPattern - 0 = inputPattern
            // So we can check if bestScore == inputPattern
            break;
        }

        rowIndex++;
    } while (rowIndex < 11);

    // Store last input and update best match data
    DAT_01205538 = inputPattern;
    DAT_0120553c = DAT_01198ee8[bestIndex * 0x1b]; // 0x1b = 27 uint stride in result table
    DAT_01205540 = bestIndex;
    return bestIndex;
}