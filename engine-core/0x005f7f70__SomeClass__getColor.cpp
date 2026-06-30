//FUNC_NAME: SomeClass::getColor
void SomeClass::getColor(void) {
    // +0x20: index used to compute offset into color table
    int index = *(int *)(this + 0x20);
    // Output buffer for RGB color (3 ints)
    int color[3] = {0, 0, 0};
    // +0x10: function pointer to retrieve color data
    // Call with offset = index * 12 (each color entry is 12 bytes)
    (*(void (**)(int, int *))(*(int **)(this + 0x10)))(index * 12, color);
}