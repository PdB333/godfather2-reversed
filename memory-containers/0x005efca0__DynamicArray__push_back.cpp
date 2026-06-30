// FUNC_NAME: DynamicArray::push_back
// Function address: 0x005efca0
// Role: Appends an element to a resizable array, doubling capacity when full.

template<typename T>
class DynamicArray {
public:
    // Constructor/Destructor likely elsewhere, reallocate at 0x005efc20
    void push_back(const T& value); // __thiscall

private:
    T* m_data;       // +0x00
    int m_size;      // +0x04
    int m_capacity;  // +0x08

    void reallocate(int newCapacity); // 0x005efc20
};

template<typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (m_size == m_capacity) {
        int newCapacity = (m_capacity == 0) ? 1 : (m_capacity * 2);
        reallocate(newCapacity);
    }

    T* slot = &m_data[m_size];
    m_size++;
    if (slot != nullptr) {
        *slot = value; // copy assignment
    }
}