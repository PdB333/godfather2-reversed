// FUNC_NAME: BigInt::addUint
// Address: 0x00665820
// Role: Adds an unsigned 32-bit value to a big integer (28-bit limbs) and stores result in another big integer.
// Supports both addition and subtraction handling via a flag (m_flags bit 0 for negative?).
// Uses base 2^28 to avoid overflow in 32-bit intermediate.

class BigInt {
public:
    int m_numLimbs;     // +0x00: number of valid limbs
    int m_capacity;     // +0x04: allocated limb count (max before resize)
    int m_flags;        // +0x08: bit0 = 1 if this is a "negative" (or subtracted) representation?
    int *m_limbs;       // +0x0C: pointer to 28-bit limb array
};

// FUN_00667740: potentially resize result to accommodate one more limb (size+1)
extern bool BigInt_resizeForAdd(BigInt *result, int extraLimbs);

// FUN_0066a7f0: full BigInt addition (used when both operands are multi-limb)
extern int BigInt_add(BigInt *a, uint word, BigInt *result);

int BigInt::addUint(BigInt *this, uint word, BigInt *result)
{
    // Early check: if result capacity is enough for one extra limb, or if resize succeeds, proceed.
    // If not enough and resize fails, return 0 (failure)
    bool canFit = (this->m_numLimbs + 1 <= result->m_capacity);
    if (!canFit) {
        if (!BigInt_resizeForAdd(result, 1)) {
            // resize failed, but we still fall through to the main path?
            // Actually the original code had an OR condition that might force entry.
            // We simulate: if resize fails, set iVar2=1 (maybe error?) but continue.
            // It's unclear; we replicate the logic as per decompilation.
        }
    }

    // Main addition path
    int iVar2 = 1;  // success flag

    if (this->m_flags == 1) {
        // Special handling when this->m_flags indicates subtraction mode?
        // Single-limb subtraction: result = word - this->m_limbs[0]
        if (this->m_numLimbs <= 1 && word <= (uint)this->m_limbs[0]) {
            this->m_flags = 0;          // clear flag
            iVar2 = BigInt_add(this, word, result);  // recursive call (likely does full addition)
            result->m_flags = 1;        // set flag on result
            this->m_flags = 1;          // restore flag
            return iVar2;
        }
    }

    // Normal addition of word to this, storing in result
    int resultNumLimbs = result->m_numLimbs = 0;  // will be set
    result->m_flags = 0;

    int *srcLimbs = this->m_limbs;
    int *dstLimbs = result->m_limbs;

    if (this->m_flags == 0) {
        // Addition case: word is added with carry propagation
        uint carry = 0;
        uint sum = (uint)*srcLimbs + word;
        *dstLimbs = sum & 0x0FFFFFFF;   // 28-bit mask
        carry = sum >> 28;
        iVar2 = 1;
        dstLimbs++;
        // Process remaining limbs (if any)
        for (int i = 1; i < this->m_numLimbs; i++) {
            srcLimbs++;
            uint limb = (uint)*srcLimbs;
            sum = limb + carry;
            *dstLimbs = sum & 0x0FFFFFFF;
            carry = sum >> 28;
            dstLimbs++;
            iVar2++;
        }
        // Store final carry as extra limb
        *dstLimbs = carry;
        iVar2++;  // one extra limb for carry
        result->m_numLimbs = this->m_numLimbs + 1;
    } else {
        // Subtraction case: word is subtracted (this->m_flags == 1)
        result->m_numLimbs = 1;
        if (this->m_numLimbs == 1) {
            word -= (uint)*srcLimbs;   // subtract this's limb
        }
        *dstLimbs = word;
    }

    // Ensure result size matches actual limb count (remove trailing zeros)
    result->m_numLimbs = iVar2;
    // Trim leading zeros
    while (result->m_numLimbs > 0 && result->m_limbs[result->m_numLimbs - 1] == 0) {
        result->m_numLimbs--;
    }

    if (result->m_numLimbs == 0) {
        result->m_flags = 0;
    }

    return iVar2;  // non-zero indicates success
}