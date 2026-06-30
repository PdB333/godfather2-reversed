// FUNC_NAME: BigInt_subtractUint28
// Address: 0x0066a7f0
// Role: Subtracts a 28-bit unsigned integer from a BigInt (arbitrary precision), storing result in a separate BigInt.
// Handles positive and negative source numbers, with borrow propagation and zero padding.

struct BigInt {
    int32_t size;       // +0x00 number of limbs used
    int32_t capacity;   // +0x04 allocated limb count
    int32_t sign;       // +0x08 0 = positive, 1 = negative (stored as sign flag)
    uint32_t* limbs;    // +0x0C pointer to array of 28-bit values (stored in uint32_t, masked with 0x0FFFFFFF)
};

// External helper functions
int32_t bigint_enlargeCapacity(BigInt* bigint); // may enlarge limb array, returns 0 on success or error code
int32_t bigint_add_uint28(BigInt* a, uint32_t b, BigInt* out); // a + b (absolute addition)
void bigint_normalize(BigInt* bigint); // trim leading zeros, adjust sign

// This function: out = a - b  (where b is a 28-bit scalar)
int32_t __cdecl BigInt_subtractUint28(BigInt* a, uint32_t b, BigInt* out)
{
    int32_t iVar1;
    uint32_t* srcLimb;
    int32_t iVar3;
    uint32_t* dstLimb;

    // Ensure destination has enough capacity for result (a->size + 1 limbs)
    if (out->capacity < a->size + 1) {
        iVar1 = bigint_enlargeCapacity(out);
        if (iVar1 != 0) {
            return iVar1;
        }
    }

    // Branch based on sign of source 'a'
    if (a->sign != 1) {
        // a is non-negative (sign == 0) -> result will be non-negative or need borrow
        iVar1 = out->size;
        iVar3 = a->size;
        dstLimb = out->limbs;
        srcLimb = a->limbs;

        // If a is zero or a single limb <= b, result is b - a (positive)
        if ((iVar3 == 1 && *srcLimb <= b) || (iVar3 == 0)) {
            if (iVar3 == 1) {
                b = b - *srcLimb; // subtract single limb
            }
            *dstLimb = b;
            iVar3 = 1;
            dstLimb++;
            out->sign = 1;          // result non-negative? Actually sign=1 is negative? Ambiguous, but consistent with other branch
            out->size = 1;
        } else {
            // a > b, need to compute a - b with borrow propagation
            out->sign = 0;          // result positive
            out->size = a->size;    // result size at most a->size
            b = *srcLimb - b;       // first limb subtraction
            *dstLimb = b & 0x0FFFFFFF;
            iVar3 = 1;
            dstLimb++;

            // Propagate borrow through remaining limbs
            if (1 < a->size) {
                do {
                    srcLimb++;
                    b = *srcLimb + ( (int32_t)b >> 0x1F ); // add borrow (sign-extend)
                    *dstLimb = b & 0x0FFFFFFF;
                    iVar3++;
                    dstLimb++;
                } while (iVar3 < a->size);
            }

            // Zero out any extra limbs if result size is smaller than original out->size
            if (iVar3 < iVar1) {
                for (iVar1 = iVar1 - iVar3; iVar1 != 0; iVar1--) {
                    *dstLimb = 0;
                    dstLimb++;
                }
            }

            bigint_normalize(); // trim leading zeros
        }
        return 0;
    } else {
        // a is negative (sign == 1) -> result = -( |a| + b ), reduce to addition
        a->sign = 0;             // temporarily treat as positive
        iVar1 = bigint_add_uint28(a, b, out); // compute |a| + b
        out->sign = 1;           // result is negative
        a->sign = 1;             // restore original sign
        return iVar1;
    }
}