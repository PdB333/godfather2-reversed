// FUNC_NAME: ActiveObjectList::findFirstActive

// Represents a pool/array of object pointers (possibly game entities).
// The iterator stores current index and current non-null object.
// This function resets the iterator to the beginning and finds the first active (non-null) object.
class ActiveObjectList
{
public:
    struct ObjectArrayData
    {
        void** objects; // +0x00: pointer to array of object pointers
        int   count;    // +0x04: number of elements in the array
    };

private:
    ObjectArrayData* m_arrayData; // +0x00: pointer to array descriptor (nullptr if none)
    int             m_currentIndex; // +0x04: current iteration index
    void*           m_currentObject; // +0x08: current object pointer (or nullptr)

public:
    // Resets the iterator to index 0 and advances until a non-null object is found.
    // After the call, m_currentObject holds the first non-null pointer (or nullptr if none).
    // m_currentIndex is set to the index after that pointer (or count if exhausted).
    void findFirstActive()
    {
        m_currentIndex = 0;
        m_currentObject = nullptr;

        if (m_arrayData == nullptr)
            return;

        do
        {
            uint32_t idx = m_currentIndex;
            if (idx >= (uint32_t)m_arrayData->count)
                return; // reached end of array

            m_currentObject = m_arrayData->objects[idx];
            m_currentIndex = idx + 1;
        } while (m_currentObject == nullptr);
    }
};