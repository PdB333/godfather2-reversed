// FUNC_NAME: SomeClass::~SomeClass (destructor at 0x008b5040)
void __fastcall SomeClass::destructor(SomeClass *this)
{
    // Set vtable pointers for base classes during destruction
    this->vtable0 = &BASE_VTABLE_00d7afd0;          // +0x00
    this->vtable3C = &BASE_VTABLE_00d7afc0;         // +0x3C (offset 0xf)
    this->vtable48 = &BASE_VTABLE_00d7afbc;         // +0x48 (offset 0x12)
    this->vtable50 = &BASE_VTABLE_00d7af58;         // +0x50 (offset 0x14)

    // Release global string/data references (likely component-specific pools)
    dataManagerRelease(&DAT_0112f81c);               // e.g., string pool entry
    dataManagerRelease(&DAT_0112f814);
    dataManagerRelease(&DAT_0112f824);
    dataManagerRelease(&DAT_0112f788);

    // Call sub-destructor for internal data
    cleanupInternalData();

    // Release member pointer at offset 0x1AC (this[0x6b])
    if (this->ptrAt0x1AC != 0) {
        releasePointer(this->ptrAt0x1AC);
    }

    // Handle member at offset 0x198 (this[0x66]) – likely a nested object
    if (this->nestedObject != 0) {
        // Release a member inside that object at offset +0x14
        releasePointer(*(void **)(this->nestedObject + 0x14));
        // Delete the object itself
        deleteObject(this->nestedObject);
    }

    // Release pointer at offset 0x18C (this[99])
    if (this->ptrAt0x18C != 0) {
        releasePointer(this->ptrAt0x18C);
    }

    // Final cleanup (e.g., static counters or file handles)
    finalCleanup();

    return;
}