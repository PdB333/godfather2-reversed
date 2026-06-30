// FUNC_NAME: VariantList::getCurrentValue

#include <cstdint>

// Represents a node in a variant list: first uint32 is type tag, second is value
struct VariantNode {
    uint32_t type;   // +0x00
    uint32_t value;  // +0x04
};

// Forward declaration of the helper function called for types 2 and 7
uint32_t convertVariantValue();

// Class holding a list of variant nodes (likely part of EA EARS serialization system)
class VariantList {
public:
    // +0x00: vtable or other fields
    // +0x04: unknown
    VariantNode* start;  // +0x08: pointer to beginning of node array
    VariantNode* end;    // +0x0C: pointer to current iterator position (or end marker)

    // Returns the value of the current node according to its type
    uint32_t getCurrentValue() {
        VariantNode* node = this->end;  // Current iterator position

        // Guard: ensure node is within valid range and non-null
        if (node < this->start && node != nullptr) {
            return 0;
        }

        switch (node->type) {
            case 2:   // Probably float or string requiring conversion
            case 7:   // Another complex type
                return convertVariantValue();

            case 5:   // Direct 32-bit integer
            case 6:   // Unsigned integer
            case 8:   // Boolean or enumeration
                return node->value;

            default:
                return 0;
        }
    }
};