// FUNC_NAME: itow (int to wide string)
int __fastcall itow(short *buffer, int value)
{
    bool negative = false;
    int length = 0;
    short digits[32]; // temporary buffer for reversed digits

    // Handle negative sign
    if (value < 0) {
        negative = true;
        value = -value;
    }

    // Extract digits in reverse order (least significant first)
    do {
        digits[length] = (short)(value % 10) + 0x30; // '0' = 0x30
        value /= 10;
        length++;
    } while (value != 0);

    // Append '-' if negative
    if (negative) {
        digits[length] = 0x2d; // '-'
        length++;
    }

    // Reverse digits into output buffer (now includes optional sign)
    int i = length;
    while (i > 0) {
        i--;
        *buffer = digits[i];
        buffer++;
    }

    // Null-terminate
    *buffer = 0;

    return length; // number of characters written (excluding null)
}