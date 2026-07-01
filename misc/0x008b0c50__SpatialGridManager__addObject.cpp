// FUNC_NAME: SpatialGridManager::addObject
// Address: 0x008b0c50
// This function adds an object to a master list and also to a bucket list keyed by a 4-int compound key (likely grid cell coordinates).
// If the object already exists in the master list, return early.

struct Bucket {
    int* m_objectList;      // +0x04: pointer to dynamic array of object pointers
    int m_count;            // +0x08
    int m_capacity;         // +0x0C
    // padding / unknown
    int m_key0;             // +0x20
    int m_key1;             // +0x24
    int m_key2;             // +0x28
    int m_key3;             // +0x2C
};

class SpatialGridManager {
public:
    Bucket** m_buckets;     // +0x04: array of pointers to Bucket
    int m_bucketCount;      // +0x08
    // ... possibly padding ...
    int* m_masterList;      // +0x1C: array of object pointers
    int m_masterCount;      // +0x20
    int m_masterCapacity;   // +0x24

    // Helper function (proved by FUN_008aff60) to grow an array
    static void* growArray(int newSize); // placeholder - actual implementation not shown
};

void __thiscall SpatialGridManager::addObject(SpatialGridManager* this, int object) {
    // --- Step 1: Check if object is already in the master list ---
    if (this->m_masterCount != 0) {
        int* masterList = this->m_masterList;
        for (uint32_t i = 0; i < this->m_masterCount; i++) {
            if (masterList[i] == object) {
                return; // duplicate, skip insertion
            }
        }
    }

    // --- Step 2: Try to find a bucket matching the object's key ---
    if (this->m_bucketCount != 0) {
        Bucket** buckets = this->m_buckets;
        for (uint32_t i = 0; i < this->m_bucketCount; i++) {
            Bucket* bucket = buckets[i];
            // Compare bucket key with object fields at offsets 0x134,0x138,0x13C,0x140
            if (bucket->m_key0 == *(int*)(object + 0x134) &&
                bucket->m_key1 == *(int*)(object + 0x138) &&
                bucket->m_key2 == *(int*)(object + 0x13C) &&
                bucket->m_key3 == *(int*)(object + 0x140)) {
                // Bucket found – add object to its dynamic list
                if (bucket->m_count == bucket->m_capacity) {
                    // Grow the bucket's object list
                    int newCapacity = (bucket->m_capacity == 0) ? 1 : bucket->m_capacity * 2;
                    bucket->m_objectList = (int*)growArray(newCapacity);
                    bucket->m_capacity = newCapacity; // assuming growArray updates capacity
                }
                bucket->m_objectList[bucket->m_count] = object;
                bucket->m_count++;
                break; // bucket found, stop searching
            }
        }
    }

    // --- Step 3: Always add to the master list ---
    if (this->m_masterCount == this->m_masterCapacity) {
        int newCapacity = (this->m_masterCapacity == 0) ? 1 : this->m_masterCapacity * 2;
        this->m_masterList = (int*)growArray(newCapacity);
        this->m_masterCapacity = newCapacity; // assumed
    }
    this->m_masterList[this->m_masterCount] = object;
    this->m_masterCount++;
}