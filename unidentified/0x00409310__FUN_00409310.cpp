extern "C" void FUN_00409310(int* buckets)
{
    int bucketIndex = 0;
    do
    {
        int node = buckets[bucketIndex];
        while (node != 0)
        {
            int next = *reinterpret_cast<int*>(node + 8);
            *reinterpret_cast<int*>(node + 8) =
                reinterpret_cast<int>(reinterpret_cast<int*>(in_EAX)[static_cast<std::uint8_t>(*reinterpret_cast<std::uint8_t*>(node + 0x10))]);
            reinterpret_cast<int*>(in_EAX)[static_cast<std::uint8_t>(*reinterpret_cast<std::uint8_t*>(node + 0x10))] = node;
            node = next;
        }
        bucketIndex = bucketIndex + 1;
    } while (bucketIndex < 0x20);
}