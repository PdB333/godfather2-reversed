// FUNC_NAME: DebugPrintHashRecords
void __fastcall DebugPrintHashRecords(int *records) {
    // records[0] is count, each record is 5 ints (20 bytes)
    // Fields: record[0]=count (only for first), record[1..4] = data used for hash
    // Computation: hash = (((field1*0x21 + field2)*0x21 + field3)*0x21 + field4)
    // This is a base-33 packing of four 32-bit values into a single value.
    int count = records[0];
    int index = count - 1;
    if (index >= 0) {
        uint *currentField3 = (uint *)&records[index * 5 + 3]; // point to field3 of current record
        do {
            uint field3 = *currentField3;
            // field1 and field2 are two ints before field3
            // Multiply by 0x21 (33) repeatedly to pack fields
            longlong part1 = (longlong)currentField3[-2] * 0x21 + (longlong)currentField3[-1];
            longlong part2 = part1 * 0x21 + field3;
            longlong hash = part2 * 0x21 + currentField3[1]; // add field4
            // Output: 2 = log level, hash, 1, 1 (maybe source/type)
            FUN_00814550(2, (int)hash, 1, 1);
            index--;
            currentField3 -= 5; // move to previous record
        } while (index >= 0);
    }
}