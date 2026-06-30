// FUNC_NAME: IDList::removeByID
void IDList::removeByID(int idToRemove) {
    // this->buffer at +0x40, this->count at +0x44
    unsigned int count = *(unsigned int*)((char*)this + 0x44);
    unsigned int i = 0;

    if (count != 0) {
        int offset = 0;
        do {
            // each element is 16 bytes, first 4 bytes are the ID
            int currentID = *(int*)(offset + *(int*)((char*)this + 0x40));
            if (currentID == idToRemove) {
                // remove by swapping with the last element (if not already last)
                if (i != count - 1) {
                    int* buffer = *(int**)((char*)this + 0x40);
                    // copy last element (at index count-1) into current position
                    buffer[i * 4 + 0] = buffer[(count - 1) * 4 + 0];
                    buffer[i * 4 + 1] = buffer[(count - 1) * 4 + 1];
                    buffer[i * 4 + 2] = buffer[(count - 1) * 4 + 2];
                    buffer[i * 4 + 3] = buffer[(count - 1) * 4 + 3];
                }
                // decrement count
                *(int*)((char*)this + 0x44) = count - 1;
                count = *(unsigned int*)((char*)this + 0x44);
                // continue loop (i stays same because we moved the last element here, need to check it)
                // Note: after swapping, we do not increment i, so the loop rechecks the swapped element
            } else {
                i++;
                offset += 16;
            }
        } while (i < count);
    }
}