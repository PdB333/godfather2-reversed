// FUNC_NAME: Matrix33::scaleFirstTwoRows
// Address: 0x00530450
// This function scales the first two rows of a 3x3 matrix (row-major) by a factor
// derived from a global constant divided by the bottom-right element (row2[2]).
// It is likely part of a math utility for normalizing or adjusting matrix scale.

void Matrix33::scaleFirstTwoRows(void)
{
    // DAT_00e2b1a4 is a global float constant (e.g., 1.0f or a specific scaling factor)
    float scaleFactor = DAT_00e2b1a4 / this->m[8];  // this->m[8] is row2[2]

    // Scale first row (indices 0,1,2)
    this->m[0] *= scaleFactor;
    this->m[1] *= scaleFactor;
    this->m[2] *= scaleFactor;

    // Scale second row (indices 3,4,5)
    this->m[3] *= scaleFactor;
    this->m[4] *= scaleFactor;
    this->m[5] *= scaleFactor;

    // Third row (indices 6,7,8) remains unchanged
}