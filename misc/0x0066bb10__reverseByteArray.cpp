// FUNC_NAME: reverseByteArray
void reverseByteArray(uint8_t* buffer, int length) {
    int left = 0;
    int right = length - 1;
    while (left < right) {
        uint8_t temp = buffer[left];
        buffer[left] = buffer[right];
        buffer[right] = temp;
        left++;
        right--;
    }
}