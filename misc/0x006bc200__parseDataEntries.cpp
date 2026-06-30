// FUNC_NAME: parseDataEntries
// Function address: 0x006bc200
// This function deserializes entries from a data stream, populating a single field
// at offset +0x184 for type 0 entries, and accumulating values into a list at +0x188
// for type 1 entries. The stream uses magic 0xe6a05c33.

void __thiscall parseDataEntries(int this, void* stream)
{
    int type;
    int* payload;
    uint value;

    resetStream(stream);
    setStreamMagic(stream, 0xe6a05c33);

    while (hasMoreData(stream))
    {
        getNextItem(stream);                     // advance into current item
        type = getItemType();
        if (type == 0)
        {
            payload = (int*)getNextItem(stream); // get payload pointer
            *(int*)(this + 0x184) = *(payload + 2); // +0x184 = value at payload[2]
        }
        else if (type == 1)
        {
            getNextItem(stream);                 // consume payload
            value = getItemValue(stream);
            addToList((List*)(this + 0x188), value);
        }
        advanceStream(stream);
    }
}