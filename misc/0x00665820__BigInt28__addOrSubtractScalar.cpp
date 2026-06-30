// FUNC_NAME: BigInt28::addOrSubtractScalar

// Function at 0x00665820: Performs addition or subtraction of a scalar (param_2) 
// to/from a big integer stored in base 2^28 (each word masked to 0xFFFFFFF).
// The operation mode is determined by the flag field in the input structure.
// Returns 0 on success, 1 if no operation was needed (due to capacity or some check).
// The result is stored in the output structure.

struct BigInt28 {
    int length;          // +0x00: number of valid words
    int capacity;        // +0x04: maximum number of words (allocated)
    int mode;            // +0x08: 0 = addition, 1 = subtraction (seems to handle special reset case)
    unsigned int* data; // +0x0C: pointer to array of words (each 28 bits)
};

// Forward declaration of external function that checks some condition (likely capacity overflow)
extern int FUN_00667740(void);

int BigInt28_addOrSubtractScalar(BigInt28* input, unsigned int scalar, BigInt28* output)
{
    int iVar1;
    int iVar2;
    unsigned int* puVar6;
    unsigned int uVar5;
    unsigned int* srcData;
    unsigned int* dstData;
    int origLen;

    // Check if addition would exceed capacity or if external function fails
    if ((input->length + 1 <= output->capacity) || (iVar2 = FUN_00667740(), iVar2 == 0)) {
        iVar2 = 1; // default return value 1? Actually this might be a flag, but below we return 0/1
        // Special reset/overflow case: if mode is 1 and condition holds
        if ((input->mode == 1) && ((1 < input->length) || (scalar <= *input->data))) {
            input->mode = 0; // reset mode
            iVar2 = FUN_0066a7f0(input, scalar, output); // external function call
            output->mode = 1;
            input->mode = 1; // restore?
            return iVar2;
        }
        origLen = output->length;
        output->mode = 0;
        srcData = input->data;
        dstData = output->data;

        if (input->mode == 0) { // Addition mode
            unsigned int carry = 0;
            iVar1 = *srcData;
            *dstData = (iVar1 + scalar) & 0xFFFFFFF;
            iVar2 = 1;
            carry = (iVar1 + scalar) >> 28;
            dstData++;
            // Add remaining words with carry
            while (iVar2 < input->length) {
                srcData++;
                iVar1 = *srcData;
                *dstData = (iVar1 + carry) & 0xFFFFFFF;
                iVar2++;
                carry = (iVar1 + carry) >> 28;
                dstData++;
            }
            // Store final carry as extra word
            *dstData = carry;
            iVar2++; // account for extra word
            output->length = input->length + 1; // one more word
        } else { // Subtraction mode (and not the special case above)
            output->length = 1;
            if (input->length == 1) {
                scalar = scalar - *input->data; // subtract input word from scalar
            }
            *dstData = scalar; // store scalar as single word
        }

        // Zero out any remaining words in output that are beyond the new length
        if (iVar2 < origLen) {
            int count = origLen - iVar2;
            while (count != 0) {
                dstData++;
                *dstData = 0;
                count--;
            }
        }

        // Trim leading zeros
        iVar2 = output->length;
        while (iVar2 > 0) {
            if (*(output->data + output->length - 1) != 0) break;
            iVar2--;
            output->length = iVar2;
        }

        if (iVar2 == 0) {
            output->mode = 0; // reset mode if result is zero
        }

        return 0; // success
    }

    return 1; // overflow / no-op indication
}