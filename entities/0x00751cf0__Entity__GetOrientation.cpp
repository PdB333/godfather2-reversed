// FUNC_NAME: Entity::GetOrientation
bool __thiscall Entity::GetOrientation(int* this, float* outOrientation) {
    // this[0] is a pointer to an owner object, this[1] is a pointer to transform data (4 floats)
    float* transformPtr = (float*)this[1];
    bool success = false;

    // Check if transformPtr is valid, owner object exists, and its type byte at offset 6 equals 4 (some valid state)
    if (transformPtr != nullptr && this[0] != 0 && *(char*)(this[0] + 6) == 4) {
        outOrientation[0] = transformPtr[0]; // x
        outOrientation[1] = transformPtr[1]; // y
        outOrientation[2] = transformPtr[2]; // z
        outOrientation[3] = transformPtr[3]; // w
        success = true;
    }

    return success;
}