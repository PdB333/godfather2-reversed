// FUNC_NAME: OrderedHashTable::removeElement
// Reconstructed from 0x006552f0: removes an element from an open-addressing hash table with linear probing, also maintains a linear array of all elements for iteration order.

class HashableElement {
public:
    virtual void* getVtable() const; // vtable pointer at offset 0 (implied)
    virtual void destructor();       // virtual destructor at offset 8 (called when refcount hits 0)
    int referenceCount;              // offset 0x08 (int after vtable pointer)

    // Hash key fields – exact semantics unknown, but used to compute bucket index
    unsigned short field_0x102;      // offset 0x102 (ushort)
    int field_0x104;                 // offset 0x104 (int)
    int field_0x108;                 // offset 0x108 (int)
    int field_0x10C;                 // offset 0x10C (int)
};

// Container that stores elements both in a linear array (for iteration) and in a hash table (for lookup)
class OrderedHashTable {
public:
    int elementCount;                // offset 0x0C
    int linearArrayCapacity;         // offset 0x10 (not used here)
    HashableElement** linearArray;   // offset 0x14 – pointer to array of all elements (insertion order)
    int bucketCount;                 // offset 0x18 – size of hash table
    HashableElement** hashTable;     // offset 0x20 – array of bucketCount pointers (open addressing)

    // Remove element from both the linear array and hash table, decrement refcount, and destroy if zero.
    void removeElement(HashableElement* element) {
        // ---- First: remove from linear array ----
        for (int i = 0; i < elementCount; i++) {
            if (linearArray[i] == element) {
                // If not the last element, replace with the last element
                if (i != elementCount - 1) {
                    linearArray[i] = linearArray[elementCount - 1];
                }
                elementCount--;
                break;
            }
        }

        // ---- Compute initial hash bucket ----
        unsigned int bucket = hash(element) % bucketCount;
        int idx = bucket;

        // ---- Find and remove from hash table ----
        while (hashTable[idx] != nullptr) {
            if (hashTable[idx] == element) {
                // Found: clear bucket
                hashTable[idx] = nullptr;

                // Rehash all following elements in the cluster to maintain probing invariants
                while (true) {
                    idx = (idx + 1) % bucketCount;
                    if (hashTable[idx] == nullptr) break;

                    HashableElement* rehashElem = hashTable[idx];
                    hashTable[idx] = nullptr;

                    unsigned int newBucket = hash(rehashElem) % bucketCount;
                    int newIdx = newBucket;
                    while (hashTable[newIdx] != nullptr) {
                        newIdx = (newIdx + 1) % bucketCount;
                    }
                    hashTable[newIdx] = rehashElem;
                }

                // ---- Decrement reference count, destroy if zero ----
                element->referenceCount--;
                if (element->referenceCount == 0) {
                    // Call virtual destructor at offset 8 of vtable
                    (*(void (__thiscall**)(HashableElement*))(element->getVtable() + 8))(element);
                }
                return;
            }
            idx = (idx + 1) % bucketCount;
            if (idx == bucket) break; // wrapped around without finding
        }
        // Element not found in hash table – possible inconsistency
    }

    // Hash function based on fields from the element
    unsigned int hash(HashableElement* elem) const {
        unsigned int h = (
            ( ((elem->field_0x102) ^ (elem->field_0x108 << 8)) * 8 ^ elem->field_0x10C) << 5
            ^ (elem->field_0x108 >> 16) ^ elem->field_0x104
        );
        return h;
    }

private:
    // Ensure we don't accidentally call the default
    OrderedHashTable() = delete;
    ~OrderedHashTable() = delete;
};