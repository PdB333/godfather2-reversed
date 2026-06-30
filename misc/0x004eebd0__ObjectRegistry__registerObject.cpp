// FUNC_NAME: ObjectRegistry::registerObject
void __cdecl ObjectRegistry::registerObject(void)
{
    // Call virtual function at vtable+4 to create/get an instance (likely returns an object pointer or ID)
    undefined4 instancePtr = (*(code **)(DAT_01219940 + 4))();

    // Convert the instance to a unique identifier (e.g., hash, string, or pointer)
    _DAT_01219948 = FUN_0060d740(instancePtr);  // +0x8: storage for ID/result

    // Call virtual function at vtable+0x10 to initialize/register the object
    (*(code **)(DAT_01219940 + 0x10))();

    // Insert this object at the head of a global singly-linked list.
    // _DAT_01219944 (at +0x4) is the "next" pointer; here we store the previous head.
    _DAT_01219944 = DAT_012058ec;               // +0x4: previous head (oldest)

    // Increment a global object counter
    DAT_012058f8 = DAT_012058f8 + 1;            // +0x1c? (global counter)

    // Update the head pointer to point to the current object's vtable base
    DAT_012058ec = &DAT_01219940;               // +0x8? (head of list)

    // Store the new counter value in this object's field at +0xC
    _DAT_0121994c = DAT_012058f8;               // +0xC: assigned ID/sequence

    return;
}