// FUN_005668a0: Transform::setTransformAndCallback
void Transform::setTransformAndCallback(const TransformData* data)
{
    // Copy 44 bytes of transform data into the object at offset +0x30
    // Structure: 5 * 8 bytes (quaternion/position?) + 1 * 4 bytes
    // data layout:
    // +0x00: 8 bytes (likely two floats)
    // +0x08: 8 bytes
    // +0x10: 8 bytes
    // +0x18: 8 bytes
    // +0x20: 8 bytes (lower 4 bytes = function pointer, upper 4 = unused?)
    // +0x28: 4 bytes
    *(uint64*)(this + 0x30) = *(uint64*)&data[0];
    *(uint64*)(this + 0x38) = *(uint64*)&data[1];
    *(uint64*)(this + 0x40) = *(uint64*)&data[2];
    *(uint64*)(this + 0x48) = *(uint64*)&data[3];
    *(uint64*)(this + 0x50) = *(uint64*)&data[4]; // callback pointer at +0x50
    *(int32*)(this + 0x58) = *(int32*)&data[5];

    // Call a math function with mixed components from the transform data
    // Parameters are extracted from the copied fields (offsets +0x44, +0x34, +0x40, +0x3c, +0x48)
    int mathResult = FUN_00b03980(
        *(int32*)(this + 0x44), // upper half of third 8-byte
        *(int32*)(this + 0x34), // upper half of first 8-byte
        *(int32*)(this + 0x40), // lower half of third 8-byte
        *(int32*)(this + 0x3c), // upper half of second 8-byte
        *(int32*)(this + 0x48)  // lower half of fourth 8-byte
    );

    // Invoke the callback stored at +0x50 (function pointer) with the math result
    ((void (*)(int))*(void**)(this + 0x50))(mathResult);

    // Free/cleanup the math result object
    FUN_00b0c100(mathResult);

    // Obtain a singleton/object and store its pointer at +0x0c
    void* someObject = (void*)FUN_00ad8d50();
    *(void**)(this + 0x0c) = someObject;
    if (someObject != nullptr) {
        // Call its first virtual function (likely constructor/initializer)
        (*(void (**)())*someObject)();
    }
}