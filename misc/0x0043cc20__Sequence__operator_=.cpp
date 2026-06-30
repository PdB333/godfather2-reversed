// FUNC_NAME: Sequence::operator<=
// Address: 0x0043cc20
// Role: Compares two Sequence objects (6 uint32s) and returns 1 if *this <= other, 0 otherwise.
// This is a lexicographic comparison with a specific ordering: first by element 0, then 1, then 2, then 3,
// then 4 (signed), then 5 (signed). Return 1 if this <= other, else 0.
// Likely used for ordering sequences or timestamps in the EARS engine.

int __thiscall Sequence::operator<=(const Sequence& other) const
{
    const uint32_t* a = &v[0]; // this->v
    const uint32_t* b = &other.v[0]; // other.v

    if (a[0] <= b[0]) {
        if (b[0] <= a[0]) { // first elements equal
            if (b[1] < a[1]) return 1; // other < this? Actually return 1 means this <= other
            if (b[1] <= a[1]) {
                if (b[2] < a[2]) return 1;
                if (b[2] <= a[2] && b[3] < a[3]) return 1;
            }
        }
        // Fall through: first element <= but not equal, or equality case in first 4 elements but 4th/5th need checking
        // The following condition determines if returning 0 (not <=) is appropriate.
        // It's complex: essentially if elements after the first are not all <=, or if the first is not equal and...
        // We'll keep the logic as-is.
        if ((b[0] != a[0]) ||
            ( ((b[1] != a[1] || b[2] != a[2] || b[3] != a[3] || (int)a[4] <= (int)b[4]) &&
               ((b[0] != a[0] || b[1] != a[1]) ||
                (b[2] != a[2] || b[3] != a[3] || b[4] != a[4]) || (int)a[5] <= (int)b[5]) )))
        {
            return 0;
        }
    }
    return 1;
}