// FUNC_NAME: EARS::Framework::Serializer::writeFieldDescriptions
void Serializer::writeFieldDescriptions()
{
    // Global serialization context pointer (DAT_01206880) contains a cursor at +0x14
    SerializerContext* ctx = reinterpret_cast<SerializerContext*>(DAT_01206880);
    int*& cursor = *reinterpret_cast<int**>(reinterpret_cast<uint>(ctx) + 0x14);

    // Write field: int32 with value 0xF (likely field type ID or fixed point factor)
    *cursor = reinterpret_cast<int>(&PTR_LAB_01126bb8); // type descriptor
    cursor++;
    *cursor = 0xF;
    cursor++;

    // Write field: pointer to string (nil) — maybe a null field name
    *cursor = reinterpret_cast<int>(&PTR_LAB_01126be0);
    cursor++;

    // Align to 4 bytes and write zero integer
    cursor = reinterpret_cast<int*>((reinterpret_cast<uint>(cursor) + 3) & ~3);
    *cursor = 0;
    cursor++;

    // Write field: another string (nil) — maybe a second name
    *cursor = reinterpret_cast<int>(&PTR_LAB_01126c08);
    cursor++;

    // Align and write a null byte (boolean false? or string terminator)
    cursor = reinterpret_cast<int*>((reinterpret_cast<uint>(cursor) + 3) & ~3);
    *reinterpret_cast<char*>(cursor) = 0;
    cursor = reinterpret_cast<int*>((reinterpret_cast<uint>(cursor) + 4) & ~3);

    // Write field: boolean true (1)
    *cursor = reinterpret_cast<int>(&PTR_LAB_01126b68);
    cursor++;

    cursor = reinterpret_cast<int*>((reinterpret_cast<uint>(cursor) + 3) & ~3);
    *cursor = 1;
    cursor++;

    // Write field: boolean from global flag (DAT_0120568c)
    *cursor = reinterpret_cast<int>(&PTR_LAB_01126cd0);
    cursor++;

    *reinterpret_cast<bool*>(cursor) = (DAT_0120568c != 0);
    cursor = reinterpret_cast<int*>((reinterpret_cast<uint>(cursor) + 4) & ~3);

    // Write field: byte zero (maybe another boolean)
    *cursor = reinterpret_cast<int>(&PTR_LAB_01126af0);
    cursor++;

    *reinterpret_cast<char*>(cursor) = 0;
    cursor = reinterpret_cast<int*>((reinterpret_cast<uint>(cursor) + 4) & ~3);

    // Write field: integer 5 (likely count or enum)
    *cursor = reinterpret_cast<int>(&PTR_LAB_01126b90);
    cursor++;

    // Write a null byte (alignment)
    *reinterpret_cast<char*>(cursor) = 0;
    cursor = reinterpret_cast<int*>((reinterpret_cast<uint>(cursor) + 4) & ~3);

    // Write integer 5
    *cursor = 5;
    cursor++;

    // Final null byte and align
    *reinterpret_cast<char*>(cursor) = 0;
    cursor = reinterpret_cast<int*>((reinterpret_cast<uint>(cursor) + 4) & ~3);

    // Update global cursor
    *reinterpret_cast<int**>(reinterpret_cast<uint>(ctx) + 0x14) = cursor;
}