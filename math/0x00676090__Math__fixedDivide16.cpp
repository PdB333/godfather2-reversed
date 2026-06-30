// FUNC_NAME: Math::fixedDivide16
int __fastcall fixedDivide16(int numerator, int denominator) {
    int sign = 1;
    if (numerator < 0) {
        numerator = -numerator;
        sign = -1;
    }
    if (denominator < 0) {
        denominator = -denominator;
        sign = -sign;
    }
    int quotient = numerator / denominator;
    int remainder = numerator % denominator;
    // Normalize remainder to less than 2^16 for the fractional part
    while (remainder > 0xFFFF) {
        remainder >>= 1;
        denominator >>= 1;
    }
    int result = ((remainder << 16) / denominator) + (quotient << 16);
    return result * sign;
}