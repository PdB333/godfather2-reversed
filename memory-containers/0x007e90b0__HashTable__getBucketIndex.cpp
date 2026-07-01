// FUNC_NAME: HashTable::getBucketIndex
uint __thiscall HashTable::getBucketIndex(int this, uint *key, uint value)
{
    // Compute bucket index using modulo of capacity at offset +0x4
    uint bucket = *key % *(uint *)(this + 4);
    // Call internal function to handle the bucket (e.g., insert or lookup)
    FUN_007e8ed0(key, value, bucket);
    return 0;
}