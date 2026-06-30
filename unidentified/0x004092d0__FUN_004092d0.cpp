extern "C" void FUN_004092d0(int* buckets)
{
    int bucketIndex = 0;
    do
    {
        int node = buckets[bucketIndex];
        while (node != 0)
        {
            int next = *reinterpret_cast<int*>(node + 8);
            std::uint32_t index = *reinterpret_cast<std::uint32_t*>(node + 0x10) & 0x1f;
            *reinterpret_cast<int*>(node + 8) = reinterpret_cast<int*>(reinterpret_cast<int*>(in_EAX)[index]);
            reinterpret_cast<int*>(in_EAX)[index] = node;
            node = next;
        }
        bucketIndex = bucketIndex + 1;
    } while (bucketIndex < 4);
}