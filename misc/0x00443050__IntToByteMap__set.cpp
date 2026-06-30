// FUNC_NAME: IntToByteMap::set
// Address: 0x00443050
// Role: Sets a byte value for an integer key in a dynamic map. If key exists, updates; else adds new entry with potential resize.

struct KeyValuePair {
    int key;          // +0x00
    unsigned char value; // +0x04
    // padding? (total 8 bytes per entry)
};

void __thiscall IntToByteMap::set(int key, unsigned char value) {
    unsigned int index = 0;
    KeyValuePair* pairs = reinterpret_cast<KeyValuePair*>(this->m_pairs); // +0x18
    unsigned int count = this->m_count; // +0x1c

    // Search for existing key
    if (count != 0) {
        do {
            if (pairs[index].key == key) {
                pairs[index].value = value;
                return;
            }
            index++;
        } while (index < count);
    }

    // Key not found, need to insert
    int capacity = this->m_capacity; // +0x20
    if (count == capacity) {
        int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        resize(newCapacity); // FUN_00443e50
        // After resize, pairs pointer may have changed; reload
        pairs = reinterpret_cast<KeyValuePair*>(this->m_pairs);
    }

    // Insert new entry at end
    KeyValuePair* newEntry = &pairs[this->m_count];
    this->m_count++;
    newEntry->key = key;
    newEntry->value = value;
}