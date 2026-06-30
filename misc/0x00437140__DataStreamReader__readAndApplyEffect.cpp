// FUNC_NAME: DataStreamReader::readAndApplyEffect
// Address: 0x00437140
// Reads a typed data stream, extracts a value based on type (2 or 7), and applies a float effect.
// Structure at param_1 (StreamBuffer):
//   +0x08: end pointer (one past last valid element)
//   +0x0c: current read pointer

int DataStreamReader::readAndApplyEffect(StreamBuffer* stream) {
    int* current = *(int**)(stream + 0x0C);
    int* end     = *(int**)(stream + 0x08);

    // Must have valid data
    if (end <= current || current == nullptr) {
        return 0;
    }

    // Top‑level type must be 7 or 2
    if (*current != 7 && *current != 2) {
        return 0;
    }

    // Move past the type word and one data word (2 ints)
    int* subElement = current + 2;
    if (end <= subElement || subElement == nullptr) {
        return 0;
    }

    // Sub‑element type: 3 is valid, 4 requires a skip call
    if (*subElement != 3) {
        if (*subElement != 4) {
            return 0;
        }
        // Advance the stream (skip the current element) – passes address of stream pointer
        int skipResult = skipElementInStream(&stream);
        if (skipResult == 0) {
            return 0;
        }
    }

    // Re‑read current (may have changed after skip)
    current = *(int**)(stream + 0x0C);
    int value = 0;
    if (current < end && current != nullptr) {
        if (*current == 2) {
            value = current[1];               // direct value
        } else if (*current == 7) {
            value = current[1] + 0x10;        // offset by 0x10
        }
    }

    // Read a float associated with this element (parameter 2 indicates some mode)
    float floatVal = (float)readFloatFromStream((int)stream, 2);

    // Apply the effect using the extracted value and float
    applyEffectToEntity(value, floatVal);

    return 0;
}