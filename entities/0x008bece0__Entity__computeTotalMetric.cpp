// FUNC_NAME: Entity::computeTotalMetric
// Address: 0x008bece0
// Role: Sums a metric over all items in an internal collection, likely for scoring or aggregation.

class Entity {
public:
    // Offset +0x10c: number of items in an internal collection
    unsigned int m_itemCount; // +0x10c

    // Helper function that returns a metric for the item at the given index (FUN_006b1a20)
    int getItemMetric(unsigned int index);

    // Computes the total metric across all items
    int __thiscall computeTotalMetric() {
        int total = 0;
        for (unsigned int i = 0; i < this->m_itemCount; i++) {
            total += this->getItemMetric(i);
        }
        return total;
    }
};