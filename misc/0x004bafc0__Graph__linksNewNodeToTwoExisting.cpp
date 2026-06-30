// FUNC_NAME: Graph::linksNewNodeToTwoExisting
class Graph {
public:
    struct Node {
        int field_0x00;                  // +0x00 unknown
        int field_0x04;                  // +0x04 pointer to something?
        int id;                          // +0x08 node ID
        int* adjacencyListA;            // +0x0c first adjacency list (pointers to node IDs)
        int countA;                     // +0x10
        int capacityA;                  // +0x14
        int* adjacencyListB;            // +0x18 second adjacency list
        int countB;                     // +0x1c
        int capacityB;                  // +0x20
        int* adjacencyListC;            // +0x24 third adjacency list
        int countC;                     // +0x28
        int capacityC;                  // +0x2c
        int field_0x30;                  // +0x30 unknown
    };

    Node* nodes;                // +0x04
    int numNodes;               // +0x08
    int nextNodeId;             // +0x14? actually used as "number of nodes" in the code
    // other fields...

    // This function links the newly created node (with ID = nextNodeId-1) 
    // to two existing nodes identified by IDs stored in edgeDescriptor.
    // param2 and param3 are output pointers to those two nodes.
    void linksNewNodeToTwoExisting(EdgeDescriptor* edge, Node** outNode1, Node** outNode2);
};

struct EdgeDescriptor {
    int field_0x00;
    int field_0x04;
    int field_0x08;
    int field_0x0c;
    int sourceId;    // +0x10
    int targetId;    // +0x14
};

// External function for reallocation (size in bytes)
extern "C" void* reallocArray(int size); // FUN_00486800
extern void initEdgeDescriptor(EdgeDescriptor* edge); // FUN_004bc440

void Graph::linksNewNodeToTwoExisting(EdgeDescriptor* edge, Node** outNode1, Node** outNode2) {
    initEdgeDescriptor(edge);

    *outNode1 = nullptr;
    *outNode2 = nullptr;

    if (numNodes == 0)
        return;

    // Search for nodes matching the source and target IDs from the edge descriptor
    for (int i = 0; i < numNodes; ++i) {
        Node* current = reinterpret_cast<Node*>(reinterpret_cast<char*>(nodes) + i * sizeof(Node));
        // nodes is an array of Node structs (each 0x34 bytes)

        if (*outNode1 == nullptr && current->id == edge->sourceId) {
            *outNode1 = current;
        }
        if (*outNode2 == nullptr && current->id == edge->targetId) {
            *outNode2 = current;
        }

        // Early exit if both found
        if (*outNode1 != nullptr && *outNode2 != nullptr)
            break;
    }

    int newNodeId = nextNodeId - 1;

    if (*outNode1 != nullptr) {
        Node* node1 = *outNode1;

        // Add newNodeId to node1's first adjacency list (listA)
        if (node1->countA == node1->capacityA) {
            int newCapacity = (node1->capacityA == 0) ? 1 : node1->capacityA * 2;
            node1->adjacencyListA = reinterpret_cast<int*>(reallocArray(newCapacity));
            node1->capacityA = newCapacity;
        }
        int* slotA = &node1->adjacencyListA[node1->countA];
        node1->countA++;
        if (slotA != nullptr) {
            *slotA = newNodeId;
        }

        // Add newNodeId to node1's third adjacency list (listC)
        if (node1->countC == node1->capacityC) {
            int newCapacity = (node1->capacityC == 0) ? 1 : node1->capacityC * 2;
            node1->adjacencyListC = reinterpret_cast<int*>(reallocArray(newCapacity));
            node1->capacityC = newCapacity;
        }
        int* slotC = &node1->adjacencyListC[node1->countC];
        node1->countC++;
        if (slotC != nullptr) {
            *slotC = newNodeId;
        }
    }

    if (*outNode2 != nullptr) {
        Node* node2 = *outNode2;

        // Add newNodeId to node2's second adjacency list (listB)
        if (node2->countB == node2->capacityB) {
            int newCapacity = (node2->capacityB == 0) ? 1 : node2->capacityB * 2;
            node2->adjacencyListB = reinterpret_cast<int*>(reallocArray(newCapacity));
            node2->capacityB = newCapacity;
        }
        int* slotB = &node2->adjacencyListB[node2->countB];
        node2->countB++;
        if (slotB != nullptr) {
            *slotB = newNodeId;
        }

        // Only add to listC if node2 is different from node1
        if (node2 != *outNode1) {
            if (node2->countC == node2->capacityC) {
                int newCapacity = (node2->capacityC == 0) ? 1 : node2->capacityC * 2;
                node2->adjacencyListC = reinterpret_cast<int*>(reallocArray(newCapacity));
                node2->capacityC = newCapacity;
            }
            int* slotC2 = &node2->adjacencyListC[node2->countC];
            node2->countC++;
            if (slotC2 != nullptr) {
                *slotC2 = newNodeId;
            }
        }
    }
}