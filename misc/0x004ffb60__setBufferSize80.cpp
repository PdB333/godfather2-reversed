// FUNC_NAME: setBufferSize80
// Thin wrapper that passes constant buffer size 0x50 (80 bytes) to lower-level function.
void setBufferSize80(void* obj, void* param) {
    int bufferSize = 0x50; // 80 bytes
    FUN_004eba90(obj, param, &bufferSize, 1);
}