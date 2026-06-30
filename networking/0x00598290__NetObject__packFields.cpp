// FUNC_NAME: NetObject::packFields
void __thiscall NetObject::packFields(void) {
    // Serializes the object's fields into the network packet buffer.
    // Returns the total size of serialized data (0x14 = 20 bytes).
    // The global pointer DAT_01205590 points to the serialization manager.

    // Class identifier for this type
    int classId = 0x801;                          // +0x00
    int fieldSize1 = 0x14;                         // size of this object

    // Write the classId as a 2-byte field
    int typeCode1 = 2;
    void* dataPtr1 = &classId;
    int returnAddr1 = 0x5982bb;
    (*(code**)(*DAT_01205590 + 0x10))();           // call manager->serializeField(typeCode1, dataPtr1)

    // Write field at offset +2 (1 byte? treated as 2 bytes here)
    int typeCode2 = 2;
    void* dataPtr2 = reinterpret_cast<char*>(this) + 2;
    int returnAddr2 = 0x5982d3;
    (*(code**)(*DAT_01205590 + 0x10))();

    // Write field at offset +4 (4 bytes)
    int typeCode3 = 4;
    void* dataPtr3 = reinterpret_cast<int*>(this) + 1;   // +4
    int returnAddr3 = 0x5982eb;
    (*(code**)(*DAT_01205590 + 0x10))();

    // Write a boolean flag derived from the 'this' pointer (unusual, likely field at +8 is a bool)
    int typeCode4 = 4;
    bool isThisValid = (this != nullptr);
    void* dataPtr4 = &isThisValid;
    int returnAddr4 = 0x598310;
    (*(code**)(*DAT_01205590 + 0x10))();

    // Write field at offset +0xC (4 bytes)
    int typeCode5 = 4;
    void* dataPtr5 = reinterpret_cast<char*>(this) + 0xC;
    int returnAddr5 = 0x59832b;
    (*(code**)(*DAT_01205590 + 0x10))();

    // Write field at offset +0x10 and an additional flag (size 4)
    void* extraFlag = reinterpret_cast<void*>(static_cast<uint32_t>(static_cast<char>(uStack_2c) != 0));
    (*(code**)(*DAT_01205590 + 0x10))(reinterpret_cast<char*>(this) + 0x10, &extraFlag, 4);
    // Note: The final call takes three arguments: this+0x10, pointer to flag, 4

    return 0x14;
}