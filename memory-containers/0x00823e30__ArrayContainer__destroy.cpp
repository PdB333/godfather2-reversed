// FUNC_NAME: ArrayContainer::destroy
void __thiscall ArrayContainer::destroy(void)
{
    int count = this->count;
    while (count > 0)
    {
        count--;
        if (this->data[count] != 0)
        {
            // Release/destroy the element at index count (each element is 8 bytes)
            FUN_004daf90(&this->data[count]);
        }
    }
    this->count = 0;
    FUN_009c8f10(this->data); // Free the array memory
    this->data = 0;
    this->capacity = 0; // Assuming offset +0x08 is capacity
}