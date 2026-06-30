// FUNC_NAME: DynamicArray::reserve
// Function address: 0x0064d260
// Role: Reallocate internal buffer to accommodate at least `newCapacity` elements (grow only)
// Uses custom alignment (rounds up element count to multiple of 16) and copies old data via internal helper.

// Known structure offsets:
// +0x00: size  (number of elements currently stored) — not used here
// +0x04: capacity (allocated number of elements)
// +0x08: data   (pointer to array of ints)

class DynamicArray {
public:
    // Fields (based on offsets)
    uint32_t size;       // +0x00
    uint32_t capacity;   // +0x04
    int32_t* data;       // +0x08

    // Reserves space for at least `newCapacity` elements.
    // Only grows if current capacity is insufficient.
    void __thiscall reserve(uint32_t newCapacity) {
        if (capacity < newCapacity) {
            // Round up to next multiple of 16 (in elements)
            uint32_t newCount = newCapacity + (0x10 - (newCapacity & 0xF));
            int32_t* newData = (int32_t*)malloc(newCount * sizeof(int32_t));

            // Copy old -> new, then free old
            int32_t* oldData = data;
            data = newData;
            copyFrom(oldData);          // copies size elements from oldData into newData
            data = oldData;
            free(oldData);
            data = newData;
            capacity = newCount;
        }
    }

private:
    // Internal helper: copies `size` elements from `source` into the current data buffer.
    void __thiscall copyFrom(const int32_t* source) {
        // Actual implementation at 0x0064d2d0
        // Presumably: memcpy(data, source, size * sizeof(int32_t));
    }
};