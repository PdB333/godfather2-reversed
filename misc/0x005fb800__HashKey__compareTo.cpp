// FUNC_NAME: HashKey::compareTo
// Function at 0x005fb800: Compares two HashKey objects. Asserts that the type/high-level field matches.
// Fields: 0x00 = type (must be non-zero and equal), 0x04 = key (used to compute result)
// Returns: (key & 0xFFFFFF00) | (key != other->key)
// This is likely used for custom ordering/hashing where the low byte of key is a flag.

class HashKey {
public:
    int type;   // +0x00
    int key;    // +0x04

    // Compares this HashKey with another. Asserts type match and non-zero.
    // Returns a 32-bit value: high 24 bits of this->key combined with flag of inequality.
    int compareTo(const HashKey* other) {
        if ((this->type == 0) || (this->type != other->type)) {
            assertionFailed();  // FUN_00b97aea - likely assert or error
        }
        // Return: top 24 bits of this key (clearing low byte) OR (1 if keys differ)
        int result = (this->key & 0xFFFFFF00) | (this->key != other->key ? 1 : 0);
        return result;
    }
};