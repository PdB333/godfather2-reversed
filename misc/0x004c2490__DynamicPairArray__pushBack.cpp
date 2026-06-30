// FUNC_NAME: DynamicPairArray::pushBack
struct Pair {
    int first;  // +0x00
    int second; // +0x04
};

class DynamicPairArray {
public:
    Pair* pushBack() {
        // If the array is full, grow the capacity
        if (m_count == m_capacity) {
            if (m_capacity == 0) {
                m_capacity = 1;
            } else {
                m_capacity *= 2;
            }
            grow(m_capacity);
        }

        // Get pointer to the new element slot
        Pair* newElement = &m_data[m_count];

        // Initialize the pair to zero
        newElement->first = 0;
        newElement->second = 0;

        // Increase element count
        m_count++;

        // Return pointer to the newly added zero-initialized element
        return newElement;
    }

private:
    // Resizes the internal buffer to hold at least newCapacity elements
    void grow(int newCapacity); // FUN_004b1440

    Pair* m_data;    // +0x00
    int m_count;     // +0x04
    int m_capacity;  // +0x08
};