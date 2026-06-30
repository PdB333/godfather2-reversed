// FUNC_NAME: AnimationBlender::readBlendWeights

#include <cstdint>

/**
 * Reads blend weight data from a serialization stream.
 * This method processes a chunk with ID 0xee247873 and populates
 * an 8-bone blend weight set with bone IDs and weights.
 * The structure at `param_1` has the following layout:
 *   +0x50  uint32_t  someFlag1? (case 0)
 *   +0x54  uint32_t  someFlag2? (case 1)
 *   +0x58  BoneId[4] boneIDs[0] (4 ints)
 *   +0x68  BoneId[4] boneIDs[1]
 *   +0x78  BoneId[4] boneIDs[2]
 *   +0x88  BoneId[4] boneIDs[3]
 *   +0x98  BoneId[4] boneIDs[4]
 *   +0xa8  BoneId[4] boneIDs[5]
 *   +0xb8  BoneId[4] boneIDs[6]
 *   +0xc8  BoneId[4] boneIDs[7]
 *   +0xd8  float     blendWeight[0]
 *   +0xdc  float     blendWeight[1]
 *   +0xe0  float     blendWeight[2]
 *   +0xe4  float     blendWeight[3]
 *   +0xe8  float     blendWeight[4]
 *   +0xec  float     blendWeight[5]
 *   +0xf0  float     blendWeight[6]
 *   +0xf4  float     blendWeight[7]
 *   +0xf8  float     blendWeightSum
 *   +0xfc  float     totalWeight (read from stream)
 *   +0x100 float     minWeight?
 */

void __thiscall AnimationBlender::readBlendWeights(uint32_t thisPtr, uint32_t streamHandle)
{
    // Stream initialization and chunk begin
    streamInit(streamHandle);
    streamBeginRead(streamHandle, 0xee247873);

    bool isFinished = streamIsEndOfChildren();
    do {
        if (isFinished) {
            // Process final sum: aggregate blend weight sum from all bones
            *(float *)(thisPtr + 0xf8) = 0.0f;
            // Check each bone ID group; if any ID is not a sentinel, add its corresponding weight
            // First bone group at +0x58
            if (((*(int *)(thisPtr + 0x58) != 0xBABDBDBA) ||   // ~0x45245246
                 (*(int *)(thisPtr + 0x5c) != 0xBEEFBEEF) ||   // ~0x41104111
                 (*(int *)(thisPtr + 0x60) != 0xEAC15A55) ||   // ~0x153ea5ab
                 (*(int *)(thisPtr + 0x64) != 0x91100911)))    // ~0x6eeff6ef
            {
                *(float *)(thisPtr + 0xf8) = *(float *)(thisPtr + 0xd8);
            }
            // Second group at +0x68
            if (((*(int *)(thisPtr + 0x68) != 0xBABDBDBA) ||
                 (*(int *)(thisPtr + 0x6c) != 0xBEEFBEEF) ||
                 (*(int *)(thisPtr + 0x70) != 0xEAC15A55) ||
                 (*(int *)(thisPtr + 0x74) != 0x91100911)))
            {
                *(float *)(thisPtr + 0xf8) += *(float *)(thisPtr + 0xdc);
            }
            // Third group at +0x78
            if (((*(int *)(thisPtr + 0x78) != 0xBABDBDBA) ||
                 (*(int *)(thisPtr + 0x7c) != 0xBEEFBEEF) ||
                 (*(int *)(thisPtr + 0x80) != 0xEAC15A55) ||
                 (*(int *)(thisPtr + 0x84) != 0x91100911)))
            {
                *(float *)(thisPtr + 0xf8) += *(float *)(thisPtr + 0xe0);
            }
            // Fourth group at +0x88
            if (((*(int *)(thisPtr + 0x88) != 0xBABDBDBA) ||
                 (*(int *)(thisPtr + 0x8c) != 0xBEEFBEEF) ||
                 (*(int *)(thisPtr + 0x90) != 0xEAC15A55) ||
                 (*(int *)(thisPtr + 0x94) != 0x91100911)))
            {
                *(float *)(thisPtr + 0xf8) += *(float *)(thisPtr + 0xe4);
            }
            // Fifth group at +0x98
            if (((*(int *)(thisPtr + 0x98) != 0xBABDBDBA) ||
                 (*(int *)(thisPtr + 0x9c) != 0xBEEFBEEF) ||
                 (*(int *)(thisPtr + 0xa0) != 0xEAC15A55) ||
                 (*(int *)(thisPtr + 0xa4) != 0x91100911)))
            {
                *(float *)(thisPtr + 0xf8) += *(float *)(thisPtr + 0xe8);
            }
            // Sixth group at +0xa8
            if (((*(int *)(thisPtr + 0xa8) != 0xBABDBDBA) ||
                 (*(int *)(thisPtr + 0xac) != 0xBEEFBEEF) ||
                 (*(int *)(thisPtr + 0xb0) != 0xEAC15A55) ||
                 (*(int *)(thisPtr + 0xb4) != 0x91100911)))
            {
                *(float *)(thisPtr + 0xf8) += *(float *)(thisPtr + 0xec);
            }
            // Seventh group at +0xb8
            if (((*(int *)(thisPtr + 0xb8) != 0xBABDBDBA) ||
                 (*(int *)(thisPtr + 0xbc) != 0xBEEFBEEF) ||
                 (*(int *)(thisPtr + 0xc0) != 0xEAC15A55) ||
                 (*(int *)(thisPtr + 0xc4) != 0x91100911)))
            {
                *(float *)(thisPtr + 0xf8) += *(float *)(thisPtr + 0xf0);
            }
            // Eighth group at +0xc8 (200 decimal)
            if (((*(int *)(thisPtr + 200) != 0xBABDBDBA) ||
                 (*(int *)(thisPtr + 0xcc) != 0xBEEFBEEF) ||
                 (*(int *)(thisPtr + 0xd0) != 0xEAC15A55) ||
                 (*(int *)(thisPtr + 0xd4) != 0x91100911)))
            {
                *(float *)(thisPtr + 0xf8) += *(float *)(thisPtr + 0xf4);
            }

            // Update minimum weight if needed
            float currentTotal = *(float *)(thisPtr + 0xfc);
            if (*(float *)(thisPtr + 0x100) <= currentTotal && currentTotal != *(float *)(thisPtr + 0x100)) {
                *(float *)(thisPtr + 0x100) = currentTotal;
            }
            return;
        }

        streamNextItem(); // Advance stream token
        uint32_t tokenType = streamGetTokenType();
        switch (tokenType) {
        case 0:
        {
            uint32_t val = streamReadInt32();
            *(uint32_t *)(thisPtr + 0x50) = val;
            break;
        }
        case 1:
        {
            uint32_t val = streamReadInt32();
            *(uint32_t *)(thisPtr + 0x54) = val;
            break;
        }
        case 2:
        {
            uint32_t val = streamReadInt32();
            *(float *)(thisPtr + 0xfc) = *(float *)&val;
            break;
        }
        case 3:
        {
            uint32_t val = streamReadInt32();
            *(float *)(thisPtr + 0x100) = *(float *)&val;
            break;
        }
        case 4:
            // Read four ints into boneID[0] group
            streamReadBlock(thisPtr + 0x58);
            streamEndBlock(thisPtr + 0x58);
            break;
        case 5:
        {
            uint32_t val = streamReadInt32();
            *(float *)(thisPtr + 0xd8) = *(float *)&val;
            break;
        }
        case 6:
            streamReadBlock(thisPtr + 0x68);
            streamEndBlock(thisPtr + 0x68);
            break;
        case 7:
        {
            uint32_t val = streamReadInt32();
            *(float *)(thisPtr + 0xdc) = *(float *)&val;
            break;
        }
        case 8:
            streamReadBlock(thisPtr + 0x78);
            streamEndBlock(thisPtr + 0x78);
            break;
        case 9:
        {
            uint32_t val = streamReadInt32();
            *(float *)(thisPtr + 0xe0) = *(float *)&val;
            break;
        }
        case 10:
            streamReadBlock(thisPtr + 0x88);
            streamEndBlock(thisPtr + 0x88);
            break;
        case 11:
        {
            uint32_t val = streamReadInt32();
            *(float *)(thisPtr + 0xe4) = *(float *)&val;
            break;
        }
        case 12:
            streamReadBlock(thisPtr + 0x98);
            streamEndBlock(thisPtr + 0x98);
            break;
        case 13:
        {
            uint32_t val = streamReadInt32();
            *(float *)(thisPtr + 0xe8) = *(float *)&val;
            break;
        }
        case 14:
            streamReadBlock(thisPtr + 0xa8);
            streamEndBlock(thisPtr + 0xa8);
            break;
        case 15:
        {
            uint32_t val = streamReadInt32();
            *(float *)(thisPtr + 0xec) = *(float *)&val;
            break;
        }
        case 16:
            streamReadBlock(thisPtr + 0xb8);
            streamEndBlock(thisPtr + 0xb8);
            break;
        case 17:
        {
            uint32_t val = streamReadInt32();
            *(float *)(thisPtr + 0xf0) = *(float *)&val;
            break;
        }
        case 18:
            streamReadBlock(thisPtr + 0xc8);
            streamEndBlock(thisPtr + 0xc8);
            break;
        case 19:
        {
            uint32_t val = streamReadInt32();
            *(float *)(thisPtr + 0xf4) = *(float *)&val;
            break;
        }
        default:
            break;
        }
        streamAdvance();
        isFinished = streamIsEndOfChildren();
    } while (true);
}