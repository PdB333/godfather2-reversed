// FUNC_NAME: Container::pushBack

// Function at 0x0081c590: Dynamic array push_back for 12-byte elements.
// The container stores a pointer to data (offset 0), count (offset 4), and capacity (offset 8).
// When full, capacity doubles (or becomes 1 if initially 0) via reallocation helper.

typedef struct {
    char data[12]; // 12-byte element
} Element12;

class Container {
public:
    Element12* m_data;   // +0x00
    int m_count;         // +0x04
    int m_capacity;      // +0x08

    void pushBack(const Element12* element) {
        int curCapacity = m_capacity;
        if (m_count == curCapacity) {
            int newCapacity;
            if (curCapacity == 0) {
                newCapacity = 1;
            } else {
                newCapacity = curCapacity * 2;
            }
            // Reallocate internal buffer (FUN_00818f90)
            reallocate(newCapacity); // updates m_data and m_capacity
        }
        Element12* dest = m_data + m_count;
        m_count++;
        if (dest != nullptr) {
            *dest = *element; // copy 12 bytes
        }
    }

private:
    void reallocate(int newCapacity); // external function at 0x00818f90
};