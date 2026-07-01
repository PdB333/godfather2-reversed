// FUNC_NAME: ObjectManager::removeFlaggedObjects
// Function address: 0x008c3d90
// Removes objects from internal array that have bit 0 set at offset 0x5f (flagged for removal).
// Calls destroyObject on each removed object, and if successful, calls setDirty(1).

void ObjectManager::removeFlaggedObjects()
{
    unsigned int count = this->m_count;
    while (count-- > 0)
    {
        int* obj = this->m_array[count];
        // Check flag at offset 0x5f (bit 0 = pending removal)
        if ((*(byte*)(obj + 0x5f) & 1) != 0)
        {
            unsigned int idx = count;
            // Shift remaining elements to close the gap
            if (count < this->m_count - 1)
            {
                do {
                    this->m_array[idx] = this->m_array[idx + 1];
                    idx++;
                } while (idx < this->m_count - 1);
            }
            this->m_count--;
            int result = this->destroyObject(obj);
            if (result != 0)
            {
                this->setDirty(1);
            }
        }
    }
}