// FUNC_NAME: DynamicArray::assign(const DynamicArray& other)
class DynamicArray {
public:
    int* m_data;      // +0x00: pointer to array of ints
    int m_size;       // +0x04: number of valid elements
    int m_capacity;   // +0x08: allocated capacity (in elements)

    void assign(const DynamicArray& other) {
        m_capacity = other.m_capacity;   // copy capacity
        m_size = other.m_size;           // copy size

        if (m_capacity == 0) {
            m_data = nullptr;
        } else {
            m_data = (int*)FUN_009c8e80(m_capacity * sizeof(int)); // allocate memory
            if (m_size != 0) {
                int i = 0;
                do {
                    m_data[i] = other.m_data[i];
                    i++;
                } while (i < m_size);
            }
        }
    }
};