// FUNC_NAME: BucketManager::insertNode
// Function address: 0x007ee180
// Role: Inserts a node into the bucket with the smallest current count.
//       Used for load-balanced allocation across multiple buckets.
//       Each bucket is a linked list (head/tail) with a count of nodes.

struct Bucket {
    uint count;  // +0x00
    uint head;   // +0x04 (pointer to first node)
    uint tail;   // +0x08 (pointer to last node)
};

struct Node {
    uint unknown0;    // +0x00
    uint next;        // +0x04 (next node in bucket list)
    uint bucketIndex; // +0x08 (index of bucket containing this node)
};

class BucketManager {
public:
    int m_totalCount;   // +0x10
    int m_numBuckets;   // +0x14
    Bucket* m_buckets;  // +0x1c

    // Finds the bucket with the smallest count and inserts the given node.
    // Returns a pointer to the bucket's count field.
    Bucket* __thiscall insertNode(Node* node);
};

Bucket* __thiscall BucketManager::insertNode(Node* node) {
    Bucket* buckets = m_buckets;
    uint smallestCount = buckets[0].count;  // count of first bucket
    uint bestBucket = 0;

    // Find bucket with smallest count (linear scan)
    if (m_numBuckets > 1) {
        uint i = 1;
        do {
            if (buckets[i].count < smallestCount) {
                bestBucket = i;
                smallestCount = buckets[i].count;
            }
            i++;
        } while (i < m_numBuckets);
    }

    // Insert node into the chosen bucket's linked list
    node->next = buckets[bestBucket].head;  // +0x04
    if (buckets[bestBucket].head == 0) {
        buckets[bestBucket].tail = (uint)node;  // first node, set tail
    }
    buckets[bestBucket].head = (uint)node;
    node->bucketIndex = bestBucket;  // +0x08

    // Update counts
    buckets[bestBucket].count++;
    m_totalCount++;

    // Return pointer to the bucket's count field
    return &buckets[bestBucket];
}