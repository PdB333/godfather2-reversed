// FUNC_NAME: generateBresenhamCirclePoints
void generateBresenhamCirclePoints(void)
{
    // DAT_0112a960 is a global array of 30 (0x1e) 2-byte entries (x,y pairs)
    // This function generates a circle of radius 5 using Bresenham's algorithm
    // and stores the points sorted by distance from origin
    
    char *pointArray = &DAT_0112a960;  // +0x0: start of point array
    
    // Initialize all points to (99,99) - sentinel/invalid values
    // 30 entries * 2 bytes = 60 bytes, from 0x112a961 to 0x112a99b
    char *p = &DAT_0112a961;
    do {
        p[-1] = 99;
        *p = 99;
        p = p + 2;
    } while ((int)p < 0x112a99b);
    
    int x = -5;
    int y = -5;
    int radiusSq = 0x19;  // 25 = 5^2
    
    do {
        int index = 0;
        char *currentPoint = &DAT_0112a960;
        
        // Find insertion point: scan for first point farther from origin than current (x,y)
        do {
            // Compare squared distances: current (x,y) vs stored point
            if (y * y + radiusSq < (int)*currentPoint * (int)*currentPoint + (int)currentPoint[1] * (int)currentPoint[1]) {
                // Found insertion point - shift remaining points right
                if (index != 0x1c) {  // 28 = max index before last slot
                    _memmove(&DAT_0112a962 + index * 2,  // destination: one slot after insertion
                             &DAT_0112a960 + index * 2,  // source: current position
                             (0x1c - index) * 2);        // bytes to move: remaining slots * 2
                }
                // Insert new point at current position
                *currentPoint = (char)x;
                currentPoint[1] = (char)y;
                break;
            }
            currentPoint = currentPoint + 2;
            index = index + 1;
        } while ((int)currentPoint < 0x112a99a);  // end of array
        
        y = y + 1;
        if (5 < y) {
            x = x + 1;
            if (5 < x) {
                return;  // Done scanning all points in [-5,5] x [-5,5] grid
            }
            radiusSq = x * x;  // Reset y loop with new x
            y = -5;
        }
    } while( true );
}