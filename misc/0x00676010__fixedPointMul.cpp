// FUNC_NAME: fixedPointMul
// Signed 16.16 fixed-point multiplication: result = (a * b) >> 16
int fixedPointMul(int a, int b)
{
    int sign = 1;
    if (a < 0) {
        a = -a;
        sign = -1;
    }
    if (b < 0) {
        b = -b;
        sign = -sign;
    }

    unsigned int aLow = a & 0xFFFF;
    unsigned int aHigh = (unsigned int)a >> 16;
    unsigned int bLow = b & 0xFFFF;
    unsigned int bHigh = (unsigned int)b >> 16;

    unsigned int product = ((aLow * bLow) >> 16) 
                         + (bLow * aHigh) 
                         + (aLow * bHigh) 
                         + ((aHigh * bHigh) << 16);

    return sign * (int)product;
}