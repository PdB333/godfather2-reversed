// FUNC_NAME: EARSContainer::removeElement
void __thiscall EARSContainer::removeElement(int *this, uint index) {
    // Remove an element from the container by shifting subsequent elements left
    // this[0] points to the element data array (allocated buffer)
    // this[1] holds the current element count
    // index must be less than (count - 1) to shift, otherwise just decrement count
    
    if (index < this[1] - 1U) {
        do {
            // Shift element at (index+1) to position index
            *(undefined4 *)(*this + index * 4) = *(undefined4 *)(*this + 4 + index * 4);
            index = index + 1;
        } while (index < this[1] - 1U);
    }
    // Decrement the element count by 1
    this[1] = this[1] + -1;
}