// FUNC_NAME: EventTranslator::translateMessage
#include <cmath>

// Structure for 8-byte message records in the buffer
struct MessageRecord {
    int   type;   // +0x00
    float value;  // +0x04
};

// Assumed class layout (offsets relative to this pointer)
// +0x08: MessageRecord* writePtr;  // next write slot
// +0x0C: MessageRecord* readPtr;   // next read slot
class EventTranslator {
public:
    // Translates one message from readPtr to writePtr
    // Returns true on success (always)
    bool translateMessage();
};

// External functions called
extern bool isValidType4(EventTranslator** self);       // Address 0x00636850
extern int getFilteredValueFromType4();                 // Address 0x004589a0

bool EventTranslator::translateMessage() {
    // Read and write pointers from the object
    MessageRecord* readPtr  = *(MessageRecord**)((int)this + 0xC);
    MessageRecord* writePtr = *(MessageRecord**)((int)this + 0x8);
    int resultValue = 0;

    // Check if there is a valid message to read
    bool canRead = (readPtr != nullptr) &&
                   (readPtr < writePtr) &&
                   ((readPtr->type == 3) ||
                    (readPtr->type == 4 && isValidType4((EventTranslator**)(&this))));

    if (!canRead) {
        // No valid message - will write default (type 3, value 0)
    } else {
        // Process the message
        float rawValue;
        if (readPtr->type == 3) {
            // Type 3: pass through the value directly
            rawValue = readPtr->value;
        } else if (readPtr->type == 4) {
            // Type 4: validate and potentially transform
            if (!isValidType4((EventTranslator**)(&this))) {
                rawValue = 0.0f;
            } else {
                // Validation succeeded – use the value from the validation function output
                // The validation function writes an 8-byte result into a temporary buffer
                // We read the float stored at offset +4 of that buffer.
                // (Implementation detail: the temporary buffer is a local variable,
                //  here we simulate by assuming isValidType4 updates a hidden field.)
                rawValue = *(float*)((int)(&reinterpret_cast<long long&>(local_temp)) + 4);
            }
        }

        // Round the float to an integer (nearest, ties to even?)
        int rounded = static_cast<int>(std::roundf(rawValue));

        // If the rounded value is less than 2, fetch from an external source
        if (rounded < 2) {
            resultValue = getFilteredValueFromType4();  // returns a filtered value
        } else {
            resultValue = 0;
        }
    }

    // Write the output message: type 3 with the result as float
    writePtr->type  = 3;
    writePtr->value = static_cast<float>(resultValue);

    // Advance the write pointer
    *(int*)((int)this + 0x8) = *(int*)((int)this + 0x8) + sizeof(MessageRecord);

    return true;
}