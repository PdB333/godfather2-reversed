// FUNC_NAME: UniqueIDList::addUnique
// Address: 0x006af330
// Description: Adds a unique integer ID to a dynamic array. If the ID already exists, returns early.
// If the array is full, resizes by doubling capacity (or initializing to 1 if empty).
// Structure offsets:
//   +0x198 : int* array_        (pointer to array of IDs)
//   +0x19c : uint32_t count_    (number of elements)
//   +0x1a0 : uint32_t capacity_ (allocated capacity)

class UniqueIDList {
public:
    // Sets up the array if needed and adds a new unique ID.
    void addUnique(int id) {
        uint32_t count = this->count_;
        uint32_t i = 0;

        // Linear search for duplicate
        if (count != 0) {
            int* arrayPtr = this->array_;
            do {
                if (*arrayPtr == id) {
                    if (i != 0xFFFFFFFF) { // Found, and index is valid
                        return;            // ID already exists
                    }
                    break;
                }
                i++;
                arrayPtr++;
            } while (i < count);
        }

        // Check if we need to grow
        if (count == this->capacity_) {
            uint32_t newCapacity;
            if (count == 0) {
                newCapacity = 1;
            } else {
                newCapacity = count * 2;
            }
            this->grow(newCapacity); // Resize array to new capacity
        }

        // Insert new ID at the end
        int* insertPos = this->array_ + this->count_;
        this->count_++;
        if (insertPos != nullptr) {
            *insertPos = id;
        }
    }

private:
    // Grow/resize function (address 0x006ad8a0)
    void grow(uint32_t newCapacity);
};