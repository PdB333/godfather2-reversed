// FUNC_NAME: Bitmap::resize
// Address: 0x00668920
// Role: Manages a bitmap with 28 bits per word (custom word size). Resizes the bitmap, clears extra bits, and zeroes extra words.

#include <cstring>

class Bitmap {
public:
    int mNumWords;      // +0x00: current number of words used
    int mCapacityWords; // +0x04: allocated word capacity
    int mFlags;         // +0x08: some flag (set to 0 on reset)
    uint32_t* mBuffer;  // +0x0C: pointer to word array

    // Resizes the bitmap to hold 'newSize' bits.
    // Returns 0 on success, non-zero on failure (e.g. allocation error).
    int resize(uint32_t newSize) {
        if (newSize < 1) {
            // Reset the bitmap
            mFlags = 0;
            mNumWords = 0;
            std::memset(mBuffer, 0, mCapacityWords * 4);
            return 0;
        }

        // Check if we need to grow (current capacity in bits = mNumWords * 28)
        if (mNumWords * 28 < newSize) {
            // Attempt to grow; FUN_00665ce0 likely reallocates memory
            int result = FUN_00665ce0();
            return result;
        }

        // Shrinking or same size: call FUN_00665ce0 (maybe commit/sync)
        int result = FUN_00665ce0();
        if (result == 0) {
            // Calculate new number of 28-bit words needed (ceiling division)
            int newWordCount = (newSize + 27) / 28; // equivalent to (newSize % 28 != 0) + newSize/28

            // Zero out words beyond the new size
            if (newWordCount < mNumWords) {
                do {
                    mBuffer[newWordCount] = 0;
                    newWordCount++;
                } while (newWordCount < mNumWords);
            }

            // Clear bits above the new size in the last partial word
            uint32_t* lastWord = &mBuffer[newSize / 28];
            int bitIndex = newSize % 28; // bit index within the word (0..27)
            uint32_t mask = (1 << bitIndex) - 1; // bits 0..bitIndex-1 left set
            *lastWord &= mask;

            FUN_00665b10(); // Possibly update some internal state
            result = 0;
        }
        return result;
    }

private:
    // External functions (not relevant for reconstruction)
    int FUN_00665ce0();
    void FUN_00665b10();
};