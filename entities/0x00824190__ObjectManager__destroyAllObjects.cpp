// FUNC_NAME: ObjectManager::destroyAllObjects
void ObjectManager::destroyAllObjects(void)
{
    uint index = 0;
    if (s_objectCount != 0) {
        do {
            // s_objectArray is an array of 8-byte entries; first 4 bytes is a pointer to an object
            Object* obj = *(Object**)(s_objectArray + index * 8);
            // Save the object's back-pointer (offset +4) into a local (unused)
            // Then set that back-pointer to point to the local variable (for destruction tracking)
            if (obj != nullptr) {
                obj->backPointer = &obj; // +0x04: pointer to the slot that holds this object
            }
            // Check if the object has the "active" flag (bit 0 at offset 0x24)
            if ((obj->flags & 1) != 0) {
                preDestroyCallback(); // FUN_004df590
            }
            // Destroy the object; the function will nullify the local pointer via &obj
            if (obj != nullptr) {
                destroyObject(&obj); // FUN_004daf90
            }
            index++;
        } while (index < s_objectCount);
    }
}