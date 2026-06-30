// FUNC_NAME: computeColorWeightedDistance
// Function at 0x0061d2e0: Computes the weighted sum of squared color differences between a source palette (with weights) and target colors, but only for targets with alpha == 0.
// Source data is an array of 5-byte records: 4 bytes RGBx color (little-endian) + 1 byte weight.
// Target colors are 32-bit ARGB (alpha in high byte).
// Returns total weighted Euclidean distance sum for all matching entries.

#include <cstdint>

int computeColorWeightedDistance(const uint8_t* sourceColorWeights, const uint32_t* targetColors, int count)
{
    int totalDistance = 0;
    int i = 0;
    
    if (count <= 0)
        return 0;
    
    do {
        uint32_t srcColor = *(const uint32_t*)sourceColorWeights;        // First 4 bytes: source color (low byte = blue)
        uint8_t weight = sourceColorWeights[4];                          // 5th byte: weight factor
        uint32_t tgtColor = targetColors[i];                             // Target color from array
        
        // Check if target alpha (high byte) is zero
        if ((int8_t)(tgtColor >> 24) == 0) {
            int blueDiff  = (srcColor & 0xFF)       - (tgtColor & 0xFF);
            int greenDiff = ((srcColor >> 8) & 0xFF) - ((tgtColor >> 8) & 0xFF);
            int redDiff   = ((srcColor >> 16) & 0xFF)- ((tgtColor >> 16) & 0xFF);
            
            totalDistance += (redDiff * redDiff + greenDiff * greenDiff + blueDiff * blueDiff) * weight;
        }
        
        sourceColorWeights += 5;  // Advance to next 5-byte source record
        i++;
    } while (i < count);
    
    return totalDistance;
}