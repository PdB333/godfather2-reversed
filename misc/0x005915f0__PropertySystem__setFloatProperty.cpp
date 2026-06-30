// FUNC_NAME: PropertySystem::setFloatProperty
// Address: 0x005915f0
// Role: Sets a float property on an object with type-dispatch and clamping.
// The property value is stored in an array with bounds checking.
// Uses a dispatch table indexed by a type ID from the property value.

// Assumed structures (not defined here):
// struct PropertyValue { float value; PropertyType* typeInfo; };
// struct PropertyArray { float* data; uint32 capacity; };

void PropertySystem::setFloatProperty(
    void* this,           // likely a PropertyOwner or object context
    PropertyValue* prop,  // property value with type info (float value reinterpreted)
    PropertyArray* arr    // array to store the property
)
{
    uint32* typeInfoPtr;
    uint32 typeId;
    void (*setter)(void*, uint32, float*);
    uint32 index;

    // Get type info from property value (offset 0x4 is a pointer to type descriptor)
    typeInfoPtr = *(uint32**)((int)prop + 4);
    typeId = typeInfoPtr[1]; // type ID at offset 0x4 within type descriptor

    // Validate type ID against dispatch table size
    if ((int)typeId >= 0 && (int)typeId < kMaxPropertyTypes) {
        setter = *(void (__cdecl **)(void*, uint32, float*))
                 (gPropertyDispatchTable + 4 + typeId * 12);
        if (setter != NULL) {
            // Dispatch to specific property setter, passing address of float value
            setter(this, typeId, &prop->value);
        }
    }

    index = *typeInfoPtr; // first field of typeInfo is index into array

    if (prop->value == 0.0f) {
        // Handle zero value: store a default constant
        if ((uint32)arr->capacity <= index) {
            // Assertion on out-of-bounds
            uint32 errorCode = 0;
            propertyOutOfBoundsHandler(&errorCode);
        }
        *((uint32*)(arr->data) + index) = kDefaultPropertyValue; // DAT_00e2e230
    } else {
        // Compute clamped value
        float newValue = kDivisionConstant / prop->value; // DAT_00e2b1a4

        if ((uint32)arr->capacity <= index) {
            uint32 errorCode = 0;
            propertyOutOfBoundsHandler(&errorCode);
        }
        *((float*)(arr->data) + index) = newValue;

        index = *typeInfoPtr; // re-read index (may have changed? but same)
        if ((uint32)arr->capacity <= index) {
            uint32 errorCode = 0;
            propertyOutOfBoundsHandler(&errorCode);
        }
        // Clamp to maximum threshold
        if (kMaxClampValue < *((float*)(arr->data) + index)) {
            if ((uint32)arr->capacity <= index) {
                uint32 errorCode = 0;
                propertyOutOfBoundsHandler(&errorCode);
            }
            *((float*)(arr->data) + index) = kMaxClampValue; // DAT_00e44658
        }
    }
}

// Constants (addresses from Ghidra)
// DAT_01205574: maxPropertyTypes (likely 0x100)
// DAT_01205570: base of dispatch table (each entry 12 bytes: 3 pointers)
// DAT_00e2e230: default int value (0?) for zero property
// DAT_00e2b1a4: division constant (float)
// DAT_00e44658: max clamp value (float)
// FUN_00591c00: propertyOutOfBoundsHandler (assertion)