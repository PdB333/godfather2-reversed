// FUNC_NAME: IntToByteMap::addMapping
// Function address: 0x00460720
// Role: Inserts a key-value pair (int -> byte) into a resizable associative array.
// If key already exists, returns false without modifying. Otherwise inserts and returns true.
// Supports a flag (bit 1 at +0x184) to select post-insertion handler.

bool __thiscall IntToByteMap::addMapping(int key, unsigned char value) {
    bool found = false;
    
    if (key == 0) {
        // Invalid key, skip (but this appears to be a caller validation? Actually param_2 != 0 check)
        // In original code: if (param_2 != 0) { ... } so we replicate that
        // But our parameter is key, and it's checked for zero. So we put the whole body inside that check.
    }
    else {
        // Search for existing key
        int count = this->count; // +0x220
        if (count != 0) {
            int* pairPtr = this->pairs; // +0x21c
            do {
                if (*pairPtr == key) {
                    found = true;
                    break;
                }
                pairPtr += 2; // each pair is two ints (key, value)
                count--;
            } while (count != 0);
        }
        
        if (found) {
            // Key already present, skip insertion
            // But note: the original code has goto to return at the end, so we just fall through to return.
        }
        else {
            int capacity = this->capacity; // +0x224
            if (this->count == capacity) {
                // Need to grow array
                int newSize;
                if (capacity == 0) {
                    newSize = 1;
                } else {
                    newSize = capacity * 2;
                }
                this->resizeArray(newSize); // FUN_00461e30
            }
            
            // Insert new pair at the end
            int* insertPtr = this->pairs + (this->count * 2); // offset in int* units
            *insertPtr = key;
            *(unsigned char*)(insertPtr + 1) = value; // value stored as byte in second int's low byte
            this->count++;
            
            // Post-insertion handling based on a flag at +0x184 (bit 1)
            if ((this->flags & 2) != 0) {
                this->onInsertedSorted(); // FUN_00460840
            } else {
                this->onInsertedUnsorted(); // FUN_00460880
            }
        }
    }
    // Return true if inserted (not found), false if already existed
    return !found;
}