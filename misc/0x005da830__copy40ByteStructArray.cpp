// FUNC_NAME: copy40ByteStructArray
// Address: 0x005da830
// Role: Copies an array of 40-byte structures from source to destination.
// Parameters:
//   count - number of 40-byte blocks to copy
//   src   - source array pointer (undefined8* for 8-byte aligned access)
//   dst   - destination array pointer (may be NULL per element; if NULL, skip copy for that element)

void __fastcall copy40ByteStructArray(int count, undefined8* src, undefined8* dst)
{
    if (count != 0) {
        do {
            if (dst != (undefined8*)0x0) {
                dst[0] = src[0];
                dst[1] = src[1];
                dst[2] = src[2];
                dst[3] = src[3];
                dst[4] = src[4];
            }
            count = count - 1;
            dst = dst + 5;
        } while (count != 0);
    }
    return;
}