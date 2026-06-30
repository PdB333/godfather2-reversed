// FUNC_NAME: computeWeightedColorDifference
// Address: 0x0061d2e0
// Computes weighted sum of squared RGB differences between two arrays of colors (with weight per entry).
// param_1: pointer to array of 5-byte entries: 4-byte color (RGBA, little-endian) + 1-byte weight
// param_2: pointer to array of 4-byte colors (BGRA?), only used when high byte (alpha) is 0
// param_3: number of entries to compare
int computeWeightedColorDifference(const uint8_t* weightedColorArray, const uint32_t* colorArray, int count)
{
    int i = 0;
    int totalError = 0;
    int error = 0;

    if (count > 0) {
        do {
            uint32_t srcColor = *reinterpret_cast<const uint32_t*>(weightedColorArray);   // 4 bytes at offset 0
            uint32_t dstColor = *(reinterpret_cast<const uint32_t*>(&colorArray[i]));      // from array of colors

            // Only process if destination color's high byte (alpha) is zero
            if (static_cast<int8_t>(dstColor >> 24) == 0) {
                int diffR = (srcColor & 0xFF) - (dstColor & 0xFF);
                int diffG = ((srcColor >> 8) & 0xFF) - ((dstColor >> 8) & 0xFF);
                int diffB = ((srcColor >> 16) & 0xFF) - ((dstColor >> 16) & 0xFF);

                // Weight is stored as the byte at offset 4 (the 5th byte of the entry)
                uint8_t weight = *(reinterpret_cast<const uint8_t*>(weightedColorArray + 4));
                error = totalError + (diffR * diffR + diffG * diffG + diffB * diffB) * weight;
                totalError = error;
            }

            i++;
            // Each entry is 5 bytes: 4-byte color + 1-byte weight
            weightedColorArray += 5;
        } while (i < count);
    }

    return totalError;
}