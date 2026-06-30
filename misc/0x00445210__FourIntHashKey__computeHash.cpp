// FUNC_NAME: FourIntHashKey::computeHash
class FourIntHashKey {
public:
    int field0;  // +0x00
    int field4;  // +0x04
    int field8;  // +0x08
    int field12; // +0x0C

    // Computes a hash from the four integer fields and stores it at *outHash.
    // Hash = (((field0 * 33 + field4) * 33 + field8) * 33 + field12)
    void __thiscall computeHash(int *outHash) {
        *outHash = ((field0 * 0x21 + field4) * 0x21 + field8) * 0x21 + field12;
    }
};