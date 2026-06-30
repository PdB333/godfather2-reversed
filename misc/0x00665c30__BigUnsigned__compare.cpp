// FUNC_NAME: BigUnsigned::compare
int __fastcall BigUnsigned::compare(const BigUnsigned& other) const
{
    int mySize = this->size;           // offset +0x00: number of 32-bit limbs
    if (other.size < mySize)
        return 1;                     // this > other
    if (mySize < other.size)
        return -1;                    // this < other

    // Compare limbs from most significant (highest index) to least significant
    const unsigned int* myPtr = this->data + mySize - 1;      // offset +0x0C: pointer to limb array
    const unsigned int* otherPtr = other.data + mySize - 1;

    for (int i = mySize; i > 0; --i)
    {
        unsigned int myLimb = *myPtr;
        unsigned int otherLimb = *otherPtr;
        if (myLimb > otherLimb)
            return 1;
        if (myLimb < otherLimb)
            return -1;
        --myPtr;
        --otherPtr;
    }
    return 0; // equal
}