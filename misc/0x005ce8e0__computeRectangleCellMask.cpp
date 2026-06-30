// FUNC_NAME: computeRectangleCellMask
// Function address: 0x005ce8e0
// Computes a 16-bit mask representing which cells in a 2x8 grid are intersected by a rectangle.
// Grid: 2 columns (x) x 8 rows (y). Cell width = g_cellWidth / 2, cell height = g_cellHeight / 8 (with rounding).
// Parameters: rectX, rectY = top-left corner; rectWidth, rectHeight = rectangle dimensions.
// Returns: bitmask where bit N (0..15) corresponds to cell (col, row) with col = N/8, row = N%8.

#include <cstdint>

// Global constants (from DAT_012056b4 and DAT_012056b8)
extern int g_cellWidth;   // +0x012056b4
extern int g_cellHeight;  // +0x012056b8

uint32_t computeRectangleCellMask(int rectX, int rectY, int rectWidth, int rectHeight)
{
    int right = rectX + rectWidth;   // right edge of rectangle
    int bottom = rectY + rectHeight; // bottom edge of rectangle

    uint32_t mask = 0;
    int colRight = 0;                // right edge of current column
    int colIndex = 0;                // column counter (0 or 1)
    int bitIndex = 0;                // bit position in mask

    do {
        // If rectangle is entirely to the left of this column, no more columns to check
        if (right < colRight) {
            return mask;
        }

        // Advance to next column's right edge
        colRight += g_cellWidth / 2;

        int nextBitIndex = bitIndex + 8; // bit index for next column's first row

        // Check if rectangle overlaps this column (rectX < colRight)
        if (rectX < colRight) {
            int rowBottom = 0;       // bottom edge of current row
            int rowIndex = 0;        // row counter (0..7)

            do {
                // If rectangle is entirely above this row, break out of row loop
                if (bottom < rowBottom) {
                    break;
                }

                // Compute cell height step (with rounding for negative values)
                int cellHeightStep = (g_cellHeight + ((g_cellHeight >> 31) & 7)) >> 3;
                rowBottom += cellHeightStep;

                // If rectangle overlaps this cell (rectY < rowBottom), set the bit
                if (rectY < rowBottom) {
                    mask |= (1 << (bitIndex & 0x1f));
                }

                rowIndex++;
                bitIndex++;
            } while (rowIndex < 8);
        }

        colIndex++;
        bitIndex = nextBitIndex;

        // Only two columns (colIndex 0 and 1)
        if (colIndex > 1) {
            return mask;
        }
    } while (true);
}