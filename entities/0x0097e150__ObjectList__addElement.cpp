// FUNC_NAME: ObjectList::addElement
// Function address: 0x0097e150
// Adds an element with the given ID to the list if not already present.
// The list stores 16-byte elements: [8 bytes handle, 4 bytes unknown, 4 bytes ID].
// Offsets: +0xB4 = pointer to element array, +0xB8 = count, +0xBC = capacity.

void __thiscall ObjectList::addElement(int id)
{
    uint i;
    int newCapacity;
    int* pIdField;
    Element* newElement;

    // Search for existing element with the same ID
    i = 0;
    if (m_count != 0) {
        pIdField = (int*)(m_pArray + 0xc); // Point to first element's ID field (+0x0C)
        do {
            if (*pIdField == id) {
                // Element already exists, do nothing
                return;
            }
            i++;
            pIdField += 4; // Move to next element's ID field (each element is 0x10 bytes)
        } while (i < m_count);
    }

    // Check if we need to grow the array
    newCapacity = m_capacity;
    if (m_count == m_capacity) {
        if (m_capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = m_capacity * 2;
        }
        reallocateArray(newCapacity); // FUN_0097bd80 - resizes the array
    }

    // Calculate address of new element
    newElement = (Element*)(m_pArray + m_count * 0x10);
    m_count++;

    // Zero-initialize the new element (16 bytes)
    newElement->handle = 0;
    newElement->field_0x8 = 0;

    // Initialize the element with a handle from some manager
    int handle = getSomeHandle(); // FUN_00950b20
    if (handle != 0) {
        initializeElement(newElement, handle, g_SomeGlobal, 0x2bb07a8a); // FUN_0097c010
    }

    // Set the ID field
    newElement->id = id;
}