// FUNC_NAME: BitFlags::compare
bool __thiscall BitFlags::compare(uint right, int op) const
{
    // 'this' holds the left-hand value (passed in ECX)
    uint left = reinterpret_cast<uint>(this); // treat this pointer as integer value

    switch (op) {
    case 0: // less than
        return left < right;
    case 1: // greater than
        return left > right;
    case 2: // less or equal
        return left <= right;
    case 3: // greater or equal
        return left >= right;
    case 4: // equal
        return left == right;
    case 5: // not equal
        return left != right;
    case 6: // bitwise AND / equality test
        // Returns true if values share any bits (non-zero intersection) or are exactly equal.
        // False only if no overlapping bits AND values differ.
        if (((left & right) == 0) && (left != right))
            return false;
        return true;
    default:
        return false;
    }
}