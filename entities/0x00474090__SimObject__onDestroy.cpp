// FUNC_NAME: SimObject::onDestroy

#include <cstdint>

// Forward declarations of helper functions
void cleanupWithFlag(int flag); // FUN_00474680
void releaseSubObject(uint32_t* obj); // FUN_004086d0
void finalizeSubObject(uint32_t* obj); // FUN_00408310
void finalDestruct(); // FUN_0046c640

// SimObject base class destructor/cleanup routine
// Called when object is being destroyed (sets vtable pointers and cleans sub-objects)
// Address: 0x00474090
void __fastcall SimObject::onDestroy(uint32_t* thisPtr)
{
    // Set vtable pointers for multiple interfaces (offset 0x0, 0x3C, 0x48, 0x50)
    // These are base class vtables for proper cleanup in inheritance chain
    *thisPtr = (uint32_t)&PTR_FUN_00e32b6c;                      // +0x00: vtable
    thisPtr[0xF] = (uint32_t)&PTR_LAB_00e32b98;                 // +0x3C: vtable
    thisPtr[0x12] = (uint32_t)&PTR_LAB_00e32ba8;                // +0x48: vtable
    thisPtr[0x14] = (uint32_t)&PTR_LAB_00e32bac;                // +0x50: vtable

    // Check if some flag or pointer at offset 0xE8 (0x3A * 4) is non-zero
    if (thisPtr[0x3A] != 0) {
        cleanupWithFlag(1);
    }

    // Release and finalize sub-objects at offsets 0x54, 0x5C, 0x134 (0x15, 0x17, 0x4D * 4)
    releaseSubObject(&thisPtr[0x15]);   // +0x54: sub-object 1
    releaseSubObject(&thisPtr[0x17]);   // +0x5C: sub-object 2
    releaseSubObject(&thisPtr[0x4D]);   // +0x134: sub-object 3

    finalizeSubObject(&thisPtr[0x15]);  // +0x54
    finalizeSubObject(&thisPtr[0x17]);  // +0x5C
    finalizeSubObject(&thisPtr[0x4D]);  // +0x134
    finalizeSubObject(&thisPtr[0x19]);  // +0x64: additional sub-object

    // Clean up a global object
    releaseSubObject((uint32_t*)&DAT_012069c4);

    // Switch vtable pointer at +0x50 to a different cleanup vtable
    thisPtr[0x14] = (uint32_t)&PTR_LAB_00e32854;

    // Final destruction step
    finalDestruct();

    return;
}