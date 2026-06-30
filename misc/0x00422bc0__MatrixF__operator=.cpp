// FUNC_NAME: MatrixF::operator=
void __thiscall MatrixF::operator=(MatrixF *this, const MatrixF &source, bool deepCopy) {
    // Copy 16 floats (4x4 matrix data)
    for (int i = 0; i < 16; ++i) {
        this->data[i] = source.data[i];
    }
    
    // If deepCopy flag is set, perform additional deep copy (e.g., reference counting)
    if (deepCopy) {
        FUN_0056c640(&source, &this->data[16]); // +0x40 offset (after matrix)
    }
    
    // Reference counting or cleanup routine
    FUN_00423900();
    
    // Check if current thread is the main thread via TLS
    // *(int *)(**(int **)(FS_OFFSET + 0x2c) + 0x34) == 0
    if (*(int *)(**(int **)(FS_OFFSET + 0x2c) + 0x34) == 0) {
        FUN_00422ad0(this, &source, deepCopy);
    }
}