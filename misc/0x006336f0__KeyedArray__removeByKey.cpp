// FUNC_NAME: KeyedArray::removeByKey
// Address: 0x006336f0
// Removes an element with the given key from a fixed-size array. The array has 8-byte stride entries.
// Class layout (relative to 'this'):
//   +0x0c: baseKey (uint) - base key value for index calculation
//   +0x14: descriptor (uint*) - pointer to array descriptor: [0] = first key, [1] = last key (exclusive)
// Note: Array entries are 8 bytes each, with key as the first 4-byte field.

void __thiscall KeyedArray::removeByKey(uint key)
{
    uint* descriptor = *(uint**)((char*)this + 0x14);
    uint currentKey = *descriptor;
    int output;

    do {
        if (descriptor[1] <= currentKey) {
            this->cleanup();
            return;
        }

        if (key == currentKey) {
            int baseKey = *(int*)((char*)this + 0x0c);
            int index = (int)(key - baseKey) >> 3;
            int result = this->processEntry(descriptor, index, &output);
            if (result != 0) {
                this->cleanup();
                return;
            }
            this->cleanup();
            return;
        }

        currentKey += 8;
    } while (true);
}