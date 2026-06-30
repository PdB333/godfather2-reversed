// FUNC_NAME: ValueResolver::resolve
// Address: 0x00627dd0
// Role: Resolves a value stored as a variant (int/float) by converting it to a canonical form.
// The object stores a pointer at +0x8 to a small header (8 bytes) containing type (int) and value (float).
// Based on the current type and value, this method selects a conversion function and updates the header.

struct ValueHeader {
    int type;   // +0x00: 3 = int-like, 4 = float-like, else unknown
    float value; // +0x04: the raw value as float
};

// Forward declarations for the three value pair generators.
// Each returns two unsigned 32-bit values that are written directly as type and value.
extern std::pair<uint32_t, uint32_t> getDefaultValuePair();  // FUN_00637ea0
extern std::pair<uint32_t, uint32_t> getIntValuePair();      // FUN_00637f10
extern std::pair<uint32_t, uint32_t> getFloatValuePair();    // FUN_00637f90

void __thiscall ValueResolver::resolve(void* this)
{
    // Call base initializer (FUN_00625ca0)
    initBase(this);

    // Get pointer to the header (stored at this+0x8 points just past the header)
    ValueHeader* header = reinterpret_cast<ValueHeader*>(
        *reinterpret_cast<int*>(static_cast<char*>(this) + 8) - 8
    );

    int type = header->type;
    float value = header->value;

    std::pair<uint32_t, uint32_t> result;

    if (type == 3) {
        // If value is exactly an integer (i.e., truncation to int and back matches)
        if (static_cast<float>(static_cast<int>(value)) == value) {
            result = getIntValuePair();
            header->type = static_cast<int>(result.first);
            header->value = *reinterpret_cast<float*>(&result.second);
            return;
        }
    } else if (type == 4) {
        result = getFloatValuePair();
        header->type = static_cast<int>(result.first);
        header->value = *reinterpret_cast<float*>(&result.second);
        return;
    }

    // Fallback: use default value generator
    result = getDefaultValuePair();
    header->type = static_cast<int>(result.first);
    header->value = *reinterpret_cast<float*>(&result.second);
}