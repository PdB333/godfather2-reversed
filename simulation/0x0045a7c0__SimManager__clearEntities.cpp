// FUNC_NAME: SimManager::clearEntities
// Function address: 0x0045a7c0
// Role: Clears two arrays of entities (likely characters and vehicles) and sets a dirty flag.
// Offsets:
//   +0x24: flags (uint32) - bit 3 (0x8) marks dirty
//   +0x40: firstCount (uint16) - number of entries in first array
//   +0x42: secondCount (uint16) - number of entries in second array
//   +0x78: firstArray (uint8*) - array of structs of size 0x28
//   +0x7c: secondArray (uint8*) - array of structs of size 0x34

void __thiscall SimManager::clearEntities() {
    uint32 i;

    // Destroy all items in the first array (e.g., characters)
    if (this->firstCount != 0) {
        for (i = 0; i < this->firstCount; ++i) {
            freeFirstItem(this->firstArray + i * 0x28);
        }
    }

    // Destroy all items in the second array (e.g., vehicles)
    if (this->secondCount != 0) {
        for (i = 0; i < this->secondCount; ++i) {
            freeSecondItem(this->secondArray + i * 0x34);
        }
    }

    // Set flag to indicate lists need refresh
    this->flags |= 0x8;
}