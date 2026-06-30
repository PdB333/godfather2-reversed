// FUNC_NAME: Variant::toInt
int Variant::toInt() {
    // Header structure: type (4 bytes) + value (4 bytes, stored as float for type 3)
    // mData is at this+0x08, header is mData-8
    Header* header = reinterpret_cast<Header*>((*reinterpret_cast<int*>(this + 8)) - 8);
    float floatVal = 0.0f;

    if (header != nullptr) {
        if (header->type == 3) {
            // Type 3: stored as float directly
            floatVal = *(float*)(&header->value);
        } else if (header->type == 4) {
            // Type 4: requires conversion to float
            float converted;
            bool success = convertToFloat(&converted); // FUN_00636850
            if (success) {
                // Build a temporary header with type 3 and the converted value
                int tempType = 3;
                int tempValue = *(int*)&converted; // Treat float bit pattern as int for Header value
                Header* tempHeader = reinterpret_cast<Header*>(&tempType);
                floatVal = *(float*)(&tempHeader->value);
            }
        }
        // else: floatVal stays 0.0
    }

    int result = static_cast<int>(floatVal);

    // Edge case: if result is zero, verify the header is a valid numeric type
    if (result == 0) {
        Header* header2 = reinterpret_cast<Header*>((*reinterpret_cast<int*>(this + 8)) - 8);
        if (header2 != nullptr) {
            int type = header2->type;
            if (type == 3) {
                // Already 0, keep result = 0
            } else if (type == 4) {
                float converted;
                bool success = convertToFloat(&converted);
                if (success) {
                    // Keep result = 0
                } else {
                    result = -1; // Not convertible
                }
            } else {
                result = -1; // Unknown type
            }
        } else {
            result = -1;
        }
    }

    debugPrintIntReturn(); // FUN_006255e0
    return result;
}