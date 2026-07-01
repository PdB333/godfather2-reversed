// FUNC_NAME: PlayerReputationTracker::calculateLevelMetric
// Function address: 0x007f3f60
// Role: Computes a metric based on a byte field at offset 0x1f1c from two objects.
// The metric formula: given min = min(a,b), max = max(a,b), returns:
//   max - ( ( (79 - min) * (80 - min) ) >> 1 ) - min + 3159
// This likely computes a normalized score (e.g., experience points needed for a level difference).

class PlayerReputationTracker {
    // Data at offset 0x1f1c is a byte (likely level or rank)
    uint8_t m_byteField; // +0x1f1c level or rank indicator
public:
    // Compare this instance's field with another instance's field to compute a metric.
    int __fastcall calculateLevelMetric(void* other) {
        // Get byte fields from both instances
        uint8_t thisVal = this->m_byteField;     // in_EAX + 0x1f1c
        uint8_t otherVal = *(uint8_t*)((uintptr_t)other + 0x1f1c); // param_1 + 0x1f1c

        uint8_t minVal, maxVal;
        if (thisVal < otherVal) {
            minVal = thisVal;
            maxVal = otherVal;
        } else {
            minVal = otherVal;
            maxVal = thisVal;
        }

        // Compute intermediate term: ( (79 - min) * (80 - min) ) / 2
        int halfProduct = ( (79 - (int)minVal) * (80 - (int)minVal) ) >> 1;

        // Final result: max - halfProduct - min + 3159
        return (int)maxVal - halfProduct - (int)minVal + 0xc57;
    }
};