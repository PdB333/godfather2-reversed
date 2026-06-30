// FUNC_NAME: BigInt::add
// Function at 0x0066bb40: Big integer addition with 28-bit limbs (mask 0xFFFFFFF).
// The 'this' pointer (in_EAX) is the destination BigInt. The function adds two BigInts pointed to by a and b.
// Structure offsets: length +0x00, capacity +0x04, sign +0x08, data pointer +0x0C.
// Returns 0 on success, -1 on allocation failure.

int BigInt::add(const BigInt* a, const BigInt* b)
{
    int* srcA = a->data;   // piVar3
    int* srcB = b->data;   // piVar5
    int lenA = a->length;  // iVar4
    int lenB = b->length;  // iVar1

    // Determine which operand has more limbs and which has fewer
    const BigInt* larger; // local_8: pointer to the BigInt with more limbs
    int lenLarge;          // param_1 after swap
    int lenSmall;          // param_2 after swap
    if (lenB < lenA) {
        larger = a;
        lenLarge = lenA;
        lenSmall = lenB;
    } else {
        larger = b;
        lenLarge = lenB;
        lenSmall = lenA;
    }

    int resultLen = lenLarge + 1; // maximum result length (with possible carry)
    // Ensure capacity is sufficient; reallocate if needed (FUN_00667740 is realloc)
    if (resultLen <= this->capacity ||
        (this->reallocData(resultLen), this->data != nullptr))
    {
        int oldLength = this->length;
        this->length = resultLen;

        int* dst = this->data; // puVar6
        const int* smallData = (srcA == nullptr ? b->data : a->data); // Actually need proper mapping
        // Above is messy due to decompiler; corrected below:

        // Reconstruction:
        const int* aData = a->data; // piVar5 originally
        const int* bData = b->data; // piVar3 originally
        const int* largerData = larger->data; // local_8[3]

        int carry = 0; // uVar2
        int i = 0;     // iVar4

        // Add corresponding limbs from both operands with carry
        for (; i < lenSmall; i++) {
            int sum = bData[i] + aData[i] + carry;
            dst[i] = sum & 0xFFFFFFF; // 28-bit limb
            carry = sum >> 28;         // carry into next limb
        }

        // Propagate carry through remaining limbs of the larger operand
        for (; i < lenLarge; i++) {
            int sum = largerData[i] + carry;
            dst[i] = sum & 0xFFFFFFF;
            carry = sum >> 28;
        }

        // Store final carry (result may have one extra limb)
        dst[resultLen - 1] = carry;

        // Trim leading zero limbs
        while (this->length > 0 && dst[this->length - 1] == 0) {
            this->length--;
        }

        // If the result is zero, clear sign
        if (this->length == 0) {
            this->sign = 0;
        }

        // Note: original code had a potential overflow loop that zeroed extra limbs if length decreased;
        // The while loop above effectively handles trimming.
        return 0; // success
    }
    return -1; // allocation failure
}