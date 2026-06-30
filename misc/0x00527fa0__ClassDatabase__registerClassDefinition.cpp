// FUNC_NAME: ClassDatabase::registerClassDefinition
void ClassDatabase::registerClassDefinition() {
    // 0x00527fa0
    // This function registers a class definition using a global vtable pointer.
    // It calls a virtual method at offset 4 to get the class hash, then uses it
    // to look up or store something via FUN_0060d740. Then calls another virtual
    // at offset 0x10, updates global pointers and increments a counter.

    // Call virtual function at vtable+4 (likely GetHash or GetName)
    uint32 classHash = ((uint32 (*)())(*(uint32 **)(PTR_PTR_01125b90 + 4)))();

    // Look up or transform the hash (FUN_0060d740 likely does a hash lookup or conversion)
    g_classHashStore[(uint32)classHash] = FUN_0060d740(classHash); // _DAT_01125b98

    // Call virtual function at vtable+0x10 (likely PostRegister or Init)
    ((void (*)())(*(uint32 **)(PTR_PTR_01125b90 + 0x10)))();

    // Save current global class pointer into the class database field (+0x94?)
    g_classDatabase->somePointer = DAT_012058ec; // _DAT_01125b94

    // Increment global class counter
    s_classCounter++; // DAT_012058f8

    // Set the global class pointer to the address of the vtable pointer (self-reference)
    DAT_012058ec = &PTR_PTR_01125b90;

    // Store the class counter as an ID in the class database (+0x9c?)
    g_classDatabase->classID = s_classCounter; // _DAT_01125b9c
}