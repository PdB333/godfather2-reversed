// FUNC_NAME: ArrayContainer::growCapacity

// Class: ArrayContainer
// Fields:
//   +0x00 m_data: int* (pointer to array of 8-byte elements)
//   +0x04 m_size: int (number of elements in use)
//   +0x08 m_capacity: int (allocated capacity)
//
// Each element is a struct { int* ptr; int* next; } where:
//   +0x00 ptr: pointer to an object or null
//   +0x04 next: if ptr != nullptr, this is the "next" pointer
//               of the object's intrusive list (points to array slot)
//
// External helpers:
extern void* allocMemory(size_t size); // FUN_009c8e80
extern void freeMemory(void* ptr);     // FUN_009c8f10
extern void destroyElement(int* element); // FUN_004daf90 (element is the 8-byte slot)

void __thiscall ArrayContainer::growCapacity(uint newCapacity)
{
    if ((uint)this->m_capacity < newCapacity)
    {
        int* newData = (int*)allocMemory(newCapacity * 8);
        if (this->m_data != 0)
        {
            uint i = 0;
            int* newSlot = newData;
            if (this->m_size != 0)
            {
                do
                {
                    int* oldSlot = (int*)(this->m_data + i * 8);
                    if (newSlot != 0)
                    {
                        int* objPtr = (int*)*oldSlot;
                        *newSlot = (int)objPtr;
                        newSlot[1] = 0;
                        if (objPtr != 0)
                        {
                            newSlot[1] = *(int*)(objPtr + 4); // preserve old next pointer
                            *(int**)(objPtr + 4) = newSlot;  // update object's next to point to new slot
                        }
                    }
                    if (*oldSlot != 0)
                    {
                        destroyElement(oldSlot);
                    }
                    i++;
                    newSlot += 2;
                } while (i < (uint)this->m_size);
            }
            freeMemory(this->m_data);
        }
        this->m_data = newData;
        this->m_capacity = newCapacity;
    }
}