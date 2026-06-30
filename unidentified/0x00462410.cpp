// FUN_00462410: ZoneManager::collectMatchingNodes(ZoneFilter* filter, ZoneCollection* outputCollection)

// Lock for thread safety (EA mutex pattern)
void ZoneManager::collectMatchingNodes(ZoneFilter* filter, ZoneCollection* outputCollection)
{
    uint numZones = *(uint*)(this + 0x14);  // +0x14: number of zones
    uint i = 0;
    bool foundAny = false;
    
    FUN_00ab4db0(&DAT_00e2e3d4); // Lock mutex
    
    if (numZones != 0) {
        do {
            ZoneNode* currentNode = *(ZoneNode**)(*(int*)(this + 0x10) + i * 4); // +0x10: array of zone pointers
            bool match = false;
            
            // Match by primary filter ID (at +0x0c) with node's type (at +0x08)
            if (*(int*)(filter + 0x0c) == *(int*)(currentNode + 8)) {
                match = true;
            } else {
                // Check secondary filter (at +0x08) against node's sub-zone list
                int subZoneCount = *(int*)(currentNode + 0x44); // +0x44: number of sub-zones
                if (subZoneCount > 0) {
                    int* subZones = *(int**)(currentNode + 0x48); // +0x48: array of sub-zone IDs
                    for (int j = 0; j < subZoneCount; j++) {
                        if (*(int*)(filter + 0x08) == subZones[j]) {
                            match = true;
                            break;
                        }
                    }
                }
            }
            
            if (match) {
                // Found a matching zone, now add to output collection if not duplicate
                if (outputCollection != nullptr) {
                    uint searchCount = *(uint*)(this + 0x20); // +0x20: number of existing collections? No, this is different.
                    
                    // Search for duplicate in output collection's existing entries? Hmm...
                    // Actually this seems to search through another list at this+0x1c (collections?) but doesn't match outputCollection itself.
                    // Let's reinterpret: outputCollection is a dynamic array structure.
                    // The code iterates over this+0x1c (array of some structures) looking for an entry that matches the outputCollection's key fields,
                    // and within that entry, checks if the current node already exists in its sub-list.
                    
                    // This part is confusing. Possibly outputCollection is part of a hash map or collection of collections.
                    // For now, we'll implement as seen.
                    
                    bool alreadyExists = false;
                    uint collectionIndex = 0;
                    if (*(uint*)(this + 0x20) != 0) {
                        int* collectionArray = *(int**)(this + 0x1c); // +0x1c: array of collection metadata (each 10 ints)
                        do {
                            if ((collectionArray != (int*)outputCollection) &&   // Skip if same pointer
                                (collectionArray[0] == *(int*)outputCollection) &&
                                (collectionArray[1] == *(int*)(outputCollection + 4)) &&
                                (collectionArray[2] == *(int*)(outputCollection + 8)) &&
                                (collectionArray[3] == *(int*)(outputCollection + 12))) {
                                
                                int* subNodeList = (int*)collectionArray[6]; // +24? offset 6*4 = 24 bytes
                                int subNodeCount = collectionArray[7];      // +28
                                for (uint k = 0; k < (uint)subNodeCount; k++) {
                                    if (subNodeList[k] == (int)currentNode) {
                                        alreadyExists = true;
                                        break;
                                    }
                                }
                                if (alreadyExists) break;
                            }
                            collectionIndex++;
                            collectionArray += 10; // each entry is 10 ints (40 bytes)
                        } while (collectionIndex < *(uint*)(this + 0x20));
                    }
                    
                    if (!alreadyExists) {
                        // Add currentNode to outputCollection's array
                        int* countPtr = (int*)(outputCollection + 7*4); // +0x1c? Actually outputCollection is an int*, offset in bytes: 7*4=28
                        int count = *countPtr;
                        int capacity = *(int*)(outputCollection + 8*4); // +0x20
                        if (count == capacity) {
                            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
                            FUN_004630a0(newCapacity); // Resize function
                        }
                        int* array = *(int**)(outputCollection + 6*4); // +0x18: pointer to array
                        if (array != nullptr) {
                            array[count] = (int)currentNode;
                        }
                        *countPtr = count + 1;
                        
                        // Notify node and filter
                        FUN_00570790(currentNode);
                        FUN_00462ae0(*(int*)(filter + 0x20)); // +0x20: some callback
                    }
                }
                
                foundAny = true;
            }
            
            i++;
        } while (i < numZones);
    }
    
    FUN_00ab4e70(); // Unlock mutex
    return foundAny ? 1 : 0;
}