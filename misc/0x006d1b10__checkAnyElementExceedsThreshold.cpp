// FUNC_NAME: checkAnyElementExceedsThreshold
uint checkAnyElementExceedsThreshold( uint* pElementArray )
{
    uint index = 0;
    do {
        // Compare global threshold (float) to masked element treated as float
        float elementAsFloat = (float)( pElementArray[index] & g_elementMask );
        if ( g_thresholdFloat < elementAsFloat )
        {
            // Return 1 (success) if any element exceeds threshold
            return 1;
        }
        index = index + 1;
    } while ( (int)index < 3 );
    return 0;
}