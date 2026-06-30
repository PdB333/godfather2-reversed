// FUN_004bbef0: SomeClass::readRecords
void __thiscall SomeClass::readRecords(void *this, int *arrayDescriptor) {
    int count;
    int temp1;
    int value1;
    int value2;
    int value3;
    int value4;
    int *newData;
    ArrayElement *element;

    // Get number of records to read
    count = readNextValue(0x20, &count);  // FUN_0064b9e0(0x20, &local_3c)

    // Initialize temps
    int savedValue1 = 0xffffffff;
    int savedValue2 = 0xffffffff;
    int savedValue3 = 0xffffffff;

    // Clear temporary buffers
    clearBuffer(&temp1);    // FUN_00498500(&local_28)
    clearBuffer(&temp2);    // FUN_00498500(&local_1c)
    clearBuffer(&temp3);    // FUN_00498500(&local_10)

    for (; count != 0; count--) {
        // Read the four values for this record
        value1 = readNextValue(0x20, &value1);  // local_48
        value2 = readNextValue(0x20, &value2);  // local_38, gets stored in savedValue2
        value3 = readNextValue(0x20, &value3);  // local_44
        value4 = readNextValue(0x20, &value4);  // local_40

        // Save for unknown reason
        savedValue2 = value2;
        savedValue1 = value1;
        savedValue3 = value3;

        // Array descriptor: arrayDescriptor[0] = data pointer, [1] = size, [2] = capacity
        if (arrayDescriptor[1] == arrayDescriptor[2]) {
            // Need to grow
            int newCapacity;
            if (arrayDescriptor[2] == 0) {
                newCapacity = 1;
            } else {
                newCapacity = arrayDescriptor[2] * 2;
            }
            newData = growArray(newCapacity);  // FUN_004bca00(newCapacity)
        }

        // Calculate pointer to next slot (struct size 0x34)
        element = (ArrayElement *)(arrayDescriptor[0] + arrayDescriptor[1] * 0x34);
        arrayDescriptor[1]++;

        if (element != nullptr) {
            element->field0 = value1;  // offset +0x00
            element->field4 = value2;  // offset +0x04
            element->field8 = value3;  // offset +0x08

            // Clear temporary buffers
            clearBuffer(&temp1);
            clearBuffer(&temp2);
            clearBuffer(&temp3);

            element->fieldC = value4;  // offset +0x0C
        }
    }
}