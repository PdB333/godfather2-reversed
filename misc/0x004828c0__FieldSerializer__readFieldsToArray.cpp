// FUNC_NAME: FieldSerializer::readFieldsToArray
// Address: 0x004828c0
// Reads fields from a source object using field descriptors and stores results in an output array.
// The fields are defined by a table (gFieldDescriptorTable) accessed via indices stored in the serializer.
// Each field descriptor contains an alignment hint (word0), size (byte1), and a reader function pointer (at +8 bytes).
// The reader function either reads directly to output array entry (if flag bit0 is 0) or copies through a temporary aligned buffer.

#include <cstdint>

extern uint8_t* gFieldDescriptorTable; // DAT_01223490

class FieldSerializer {
public:
    void readFieldsToArray(void* source, uint32_t* outArray); // param_2 = source, param_3 = outArray

private:
    uint32_t m_callCount;      // +0x04, incremented each call
    uint16_t m_fieldCount;     // +0x0C, number of fields
    uint8_t* m_fieldFlags;     // +0x20C, array of flags per field (bit0 = use alignment)
    uint16_t* m_fieldIndices;  // +0x210, array of indices into field descriptor table
};

void FieldSerializer::readFieldsToArray(void* source, uint32_t* outArray)
{
    m_callCount++;
    outArray[0] = 0;

    uint16_t* fieldTable = *(uint16_t**)(gFieldDescriptorTable + 4); // base of field descriptors (each 0x10 bytes)
    uint32_t fieldIdx = 0;
    uint16_t* tempBuffer = reinterpret_cast<uint16_t*>(outArray + m_fieldCount + 1); // scratch area beyond output array
    uint16_t* alignedTemp = tempBuffer; // will be aligned per field

    if (m_fieldCount != 0) {
        do {
            uint16_t fieldId = m_fieldIndices[fieldIdx]; // index into descriptor table
            // descriptor address = fieldTable + fieldId * 0x10 + 4 (offset to skip alignment word?)
            uint16_t* desc = reinterpret_cast<uint16_t*>(
                reinterpret_cast<uintptr_t>(fieldTable) + fieldId * 0x10 + 4);
            uint32_t fieldSize = (uint32_t)((uint8_t)(desc[1])); // size in bytes

            uint8_t flags = m_fieldFlags[fieldIdx];
            uint32_t result;
            if ((flags & 1) == 0) {
                // No alignment needed – read directly
                auto reader = reinterpret_cast<uint32_t (*)(void*, int, uint32_t)>(desc + 4);
                result = reader(source, 0, fieldSize);
            } else {
                // Align temp buffer
                uint32_t alignment = (uint32_t)desc[0]; // alignment value
                if ((uintptr_t)alignedTemp & (fieldSize - 1)) {
                    alignedTemp = reinterpret_cast<uint16_t*>(
                        (uintptr_t)alignedTemp + (fieldSize - ((uintptr_t)alignedTemp & (fieldSize - 1))));
                }
                auto reader = reinterpret_cast<uint32_t (*)(void*, void*, uint32_t)>(desc + 4);
                result = reader(source, alignedTemp, fieldSize);
                alignedTemp += alignment; // advance by alignment (original word0)
            }
            outArray[fieldIdx + 1] = result;
            fieldIdx++;
        } while (fieldIdx < m_fieldCount);
    }
}