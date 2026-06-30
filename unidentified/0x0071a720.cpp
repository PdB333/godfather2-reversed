// FUN_0071a720: SomeClass::getVector
void SomeClass::getVector(int index, Vector3& outVec)
{
    // +0x88: type/mode indicator (0x08 = use indexed data, else use default)
    if (*(char*)(this + 0x88) == 0x08) {
        int id = call_0071a640(this, index);   // get identifier from index
        Vector3* src = (Vector3*)call_006e5dd0(id); // retrieve data by id
        outVec = *src;
    } else {
        Vector3* src = (Vector3*)call_006e5dc0(); // get default static data
        outVec = *src;
    }
}