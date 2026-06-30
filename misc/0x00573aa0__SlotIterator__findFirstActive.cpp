// FUNC_NAME: SlotIterator::findFirstActive

class SlotIterator {
public:
    // +0x00: pointer to array descriptor
    struct ArrayDescriptor {
        int* items;  // +0x00: pointer to array of ints (0 = empty slot)
        int count;   // +0x04: number of elements in the array
    };

    ArrayDescriptor* descriptor; // +0x00
    int currentIndex;            // +0x04
    int currentValue;            // +0x08

    // Resets iteration and finds the first non-zero element.
    // Sets currentIndex to the index after the found element,
    // currentValue to the element's value (0 if none found).
    void findFirstActive() {
        currentIndex = 0;
        currentValue = 0;

        if (descriptor == nullptr || descriptor->items == nullptr) {
            return;
        }

        // Scan the array for the first non-zero entry
        while (currentIndex < descriptor->count) {
            int val = descriptor->items[currentIndex];
            currentValue = val;
            currentIndex++;
            if (val != 0) {
                break; // found a valid slot
            }
        }
        // If the loop completes without breaking, currentValue remains 0
        // and currentIndex equals count (past-the-end).
    }
};