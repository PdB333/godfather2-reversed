// FUNC_NAME: MathUtils::withinCircularRange
bool withinCircularRange(float edge1, float edge2, float point)
{
    // Global constants for range check (likely angular tolerance)
    // DAT_00e44598: maximum difference for "short arc" check (e.g., 180 degrees in radians)
    // DAT_00e44680: mask to clear sign bit (0x7FFFFFFF)
    // DAT_00e446d0: another threshold for "long arc" wrap case
    static const float s_maxShortArcDiff = DAT_00e44598;
    static const unsigned int s_signMask = DAT_00e44680; // e.g., 0x7FFFFFFF
    static const float s_maxWrapDiff   = DAT_00e446d0;

    // Compute unsigned absolute difference of the two edges (via integer reinterpretation)
    // This checks if the edges are within a short arc (<= maxShortArcDiff)
    float diffBitwise = (float)((unsigned int)(edge1 - edge2) & s_signMask);
    if (s_maxShortArcDiff <= diffBitwise)
    {
        // Edges span a long arc; check if point lies between them considering wrap-around
        if (edge2 <= edge1)
        {
            // edge2 is "ahead" of edge1 in increasing order
            if (point < edge2)
                return false;
            bool isAbove = edge1 < point;
            if (isAbove)
                return false;
        }
        else
        {
            // edge1 is ahead of edge2
            if (point < edge1)
                return false;
            bool isAbove = edge2 < point;
            if (isAbove)
                return false;
        }
    }
    else
    {
        // Edges are close - check point against the circular wrap boundary
        float wrapDiff = (float)((unsigned int)(edge1 - point) & s_signMask);
        if (s_maxWrapDiff <= wrapDiff)
            return false;
    }
    return true;
}