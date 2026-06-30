// FUNC_ADDRESS: 0x004a9e90
// FUNC_NAME: DataStreamWriter::writeArrayOf8ByteLists
// Writes a list of arrays of 8‑byte elements to the data stream.
// The list is described by:
//   struct ListDescriptor {
//       void* elements;   // +0x00: pointer to array of 16‑byte elements
//       int   count;      // +0x04: number of elements
//   };
// Each 16‑byte element is:
//   struct ArrayOf8ByteElements {
//       void* data;    // +0x00: pointer to the 8‑byte items
//       int   itemCount; // +0x04: number of 8‑byte items (total bytes = itemCount * 8)
//       // +0x08 and +0x0C are unused in this function
//   };
// WriteData(size, ptr) writes 'size' bytes from 'ptr' to the stream.
// When a data pointer is null, a global empty buffer (0x0120546e) is used instead.

void DataStreamWriter::writeArrayOf8ByteLists(void* thisPointer, ListDescriptor* listInfo)
{
    int elementCount = listInfo->count;
    // Write the element count (the 0x20 size may be a fixed header length; original code writes 0x20 bytes from stack).
    WriteData(0x20, &elementCount);

    if (elementCount != 0) {
        int offset = 0;
        do {
            // Read the number of 8‑byte items from the element at offset +4
            int itemCount = *(int*)((char*)listInfo->elements + 4 + offset);
            ArrayOf8ByteElements* currentElement = (ArrayOf8ByteElements*)((char*)listInfo->elements + offset);

            // Write the item count (again with the same header size)
            WriteData(0x20, &itemCount);

            // Get the data pointer; default to empty buffer if null
            char* dataPtr = (char*)currentElement->data;
            if (dataPtr == nullptr) {
                dataPtr = globalEmptyBuffer; // Address 0x0120546e
            }

            // Write the actual data: itemCount * 8 bytes
            WriteData(itemCount * 8, dataPtr);

            offset += 16; // Each element is 16 bytes
            elementCount--;
        } while (elementCount != 0);
    }
}