// FUNC_NAME: bignumShiftLeft
// Address: 0x00668da0
// Performs left shift by 1 bit on a big number (multi-word integer).
// param_1: source BigNumber*
// param_2: destination BigNumber* (may be same as source)
// Returns 0 on success, non-zero on failure (insufficient capacity after reallocation attempt)

struct BigNumber {
    int32_t length;       // +0x00 number of 32-bit words currently used
    int32_t capacity;     // +0x04 allocated word count
    int32_t flags;        // +0x08 sign / flags
    uint32_t* data;       // +0x0C pointer to array of words
};

// forward declaration of helper function that ensures capacity
int32_t ensureBigNumberCapacity(BigNumber* num, int32_t neededWords); // FUN_00667740

int32_t bignumShiftLeft(BigNumber* src, BigNumber* dst)
{
    uint32_t carry;
    int32_t result;
    uint32_t* srcPtr;
    uint32_t* dstPtr;
    int32_t i;
    int32_t oldLen;
    int32_t newLen;

    // Check if dst has enough room (src->length + 1) or can be expanded
    if ((src->length + 1 <= dst->capacity) || 
        (result = ensureBigNumberCapacity(dst, src->length + 1), result == 0))
    {
        oldLen = dst->length;
        dst->length = src->length;  // new length in words (may increase later)

        srcPtr = (uint32_t*)src->data;
        dstPtr = (uint32_t*)dst->data;

        carry = 0;
        for (i = 0; i < src->length; i++)
        {
            uint32_t word = *srcPtr;
            *dstPtr = (word << 1) | carry;
            carry = word >> 31;
            srcPtr++;
            dstPtr++;
        }

        if (carry != 0)
        {
            *dstPtr = 1;            // final carry bit becomes the new most significant word
            dst->length = dst->length + 1;
        }

        // Zero out any remaining words in the original destination range
        if (dst->length < oldLen)
        {
            uint32_t* clearPtr = (uint32_t*)(dst->data + dst->length);
            int32_t clearCount = oldLen - dst->length;
            for (; clearCount != 0; clearCount--)
            {
                *clearPtr = 0;
                clearPtr++;
            }
        }

        dst->flags = src->flags;    // copy flags (sign etc.)
        result = 0;
    }

    return result;
}