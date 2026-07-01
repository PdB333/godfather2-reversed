// FUNC_NAME: Vector::insertAt
void __thiscall Vector::insertAt(int *this, int insertionPosPtr, uint count, int *data)
{
    // this[0] = start pointer, this[1] = end pointer, this[2] = capacity end pointer
    int *start = (int *)this[0];
    int *end = (int *)this[1];
    int *capacityEnd = (int *)this[2];
    int elementSize = 0x50; // 80 bytes per element

    int curSize = (end - start) / elementSize;
    int capacity = (capacityEnd - start) / elementSize;

    if (capacity < curSize + (int)count) {
        // Need to reallocate: grow capacity
        int newCapacity = curSize * 2;
        if (curSize == 0) {
            newCapacity = 1;
        }
        int desiredCapacity = curSize + (int)count;
        if (desiredCapacity > newCapacity) {
            newCapacity = desiredCapacity;
        }

        // Allocate new block (element size 0x50, alignment 0x10, heap tag "EASTL")
        int *newStart = (int *)FUN_0068abc0(newCapacity * elementSize, 0x10, 0, "EASTL", 0, 0);
        int *newEnd = newStart;

        // Copy elements before insertion point
        newEnd = memmoveHelper(&newEnd, start, insertionPosPtr, newEnd, newEnd);
        // Insert new data
        newEnd = memcopyHelper(newEnd, count, data);
        // Copy elements after insertion point
        newEnd = memmoveHelper(&newEnd, insertionPosPtr, end, count * elementSize + newEnd, newEnd);

        // Free old block if it exists
        if (start != 0) {
            FUN_009c8f10(start);
        }

        // Update this pointers
        this[0] = newStart;
        this[1] = newEnd;
        this[2] = newCapacity * elementSize + newStart;
    }
    else if (count != 0) {
        // Capacity is sufficient; insert into existing space
        int savedData[20]; // enough to hold one element (80 bytes = 20*4)
        memcpy(savedData, data, elementSize); // backup the data to insert
        int oldEnd = (int)end;

        int afterInsertCount = (oldEnd - (int)insertionPosPtr) / elementSize;
        if (count < afterInsertCount) {
            // Insertion point is not at the end; shift elements after insertion
            int newEndTemp = (int)end + count * -elementSize;
            memmoveHelper(&newEndTemp, end, (int)end, (int)end, newEndTemp);
            this[1] = (int)end + count * elementSize;
            memmoveHelper((int *)insertionPosPtr, newEndTemp, (int)end);
            memcopyHelper((int *)insertionPosPtr, count * elementSize + (int)insertionPosPtr, savedData);
            return;
        }
        // Insertion at the end (or trailing)
        int elementsAfter = afterInsertCount;
        if (count >= elementsAfter) {
            // Extend into unused capacity
            int extraCount = count - elementsAfter;
            memcopyHelper((int)end, extraCount, savedData);
            this[1] = (int)end + extraCount * elementSize;
            memmoveHelper(&newEndTemp, insertionPosPtr, (int)end, this[1], newEndTemp);
            this[1] = this[1] + elementsAfter * elementSize;
            memcopyHelper((int)insertionPosPtr, (int)end, savedData);
            return;
        }
    }
}