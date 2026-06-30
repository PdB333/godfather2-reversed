// FUNC_NAME: findClosestColor (Color distance comparison among three colors)
// Address: 0x0061d400
// Role: Given four 32-bit ARGB colors (alpha ignored, only lower 24 bits used), returns the index (0,1,2) of the color closest to the target color.
int __cdecl findClosestColor(uint32_t color1, uint32_t color2, uint32_t color3, uint32_t target) {
    // Extract RGB channels from target
    uint8_t targetR = target & 0xFF;
    uint8_t targetG = (target >> 8) & 0xFF;
    uint8_t targetB = (target >> 16) & 0xFF;

    // Helper to compute absolute difference efficiently (branchless)
    auto absDiff = [](int a, int b) -> int {
        int diff = a - b;
        int sign = diff >> 31;         // -1 if diff < 0, 0 otherwise
        return (diff ^ sign) - sign;   // branchless abs
    };

    // Compute Manhattan distance for color1
    int r1 = color1 & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = (color1 >> 16) & 0xFF;
    int dist1 = absDiff(r1, targetR) + absDiff(g1, targetG) + absDiff(b1, targetB);

    // Compute Manhattan distance for color2
    int r2 = color2 & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = (color2 >> 16) & 0xFF;
    int dist2 = absDiff(r2, targetR) + absDiff(g2, targetG) + absDiff(b2, targetB);

    // Compute Manhattan distance for color3
    int r3 = color3 & 0xFF;
    int g3 = (color3 >> 8) & 0xFF;
    int b3 = (color3 >> 16) & 0xFF;
    int dist3 = absDiff(r3, targetR) + absDiff(g3, targetG) + absDiff(b3, targetB);

    // Determine which distance is smallest
    int minFirstTwo = (dist1 < dist2) ? dist1 : dist2;  // min of first two
    if (dist3 < minFirstTwo) {
        return 2;   // Third color is closest
    } else {
        // Third is not strictly better; return index of best among first two
        return (dist2 < dist1) ? 1 : 0;
    }
}