// FUNC_NAME: Vector::removeUnordered
void __thiscall Vector::removeUnordered(int index)
{
    // If the element to remove is not the last one, overwrite it with the last element.
    if (index != this->size - 1) {
        this->data[index] = this->data[this->size - 1];
    }
    // Decrease the size (count) to effectively remove the element.
    this->size--;
}