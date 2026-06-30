// FUNC_NAME: SpatialGrid::insertEntity

#include <cstdint>

// Forward declarations
struct Entity;
struct SpatialGrid;

// Global spatial grid instance and world dimensions
extern SpatialGrid* gSpatialGrid;  // Typically in EDI register
extern int32_t gWorldMaxX;         // DAT_012056b4
extern int32_t gWorldMaxY;         // DAT_012056b8

// Entity structure (partial, only relevant offsets)
// +0x04: state (0 = uninserted, 3 = inserted)
// +0x08: half-width or extent X
// +0x0C: half-height or extent Y
// +0x10: world X coordinate
// +0x14: world Y coordinate
// +0x18: spatial cell handle (allocated by SpatialGrid)
struct Entity {
    uint32_t field_0x00;
    int32_t state;          // +0x04
    int32_t halfWidth;      // +0x08
    int32_t halfHeight;     // +0x0C
    int32_t worldX;         // +0x10
    int32_t worldY;         // +0x14
    int32_t cellHandle;     // +0x18
    // ... other fields
};

// SpatialGrid structure (quadtree/grid node manager)
// +0x00: head of linked list (root node or free list)
// +0x0C: total node count
// +0x0E: current traversal depth level
struct SpatialGrid {
    Entity* head;           // +0x00
    Entity* current;        // +0x04 (temporary, used for iteration)
    int32_t field_0x08;
    int32_t nodeCount;      // +0x0C
    int32_t depthLevel;     // +0x0E
    // ... rest of structure
};

// Internal helpers (forward declarations)
int32_t checkAndInsert(SpatialGrid* grid, Entity* entity, Entity* node, int32_t level, int32_t arg);
SpatialGrid* getRootGrid();  // FUN_005d0ca0
void removeNode(SpatialGrid* grid, Entity* node); // FUN_005d12b0
int32_t allocateCellHandle(int32_t x, int32_t y); // FUN_005ce8e0

// Main insertion function: add entity into spatial partition
int32_t SpatialGrid::insertEntity(Entity* entity)
{
    SpatialGrid* grid = gSpatialGrid;

    // Bounds check against world dimensions
    if (entity->worldX > gWorldMaxX - 1 || entity->worldY > gWorldMaxY - 1) {
        return 0; // Out of bounds, insertion failed
    }

    // Mark entity as uninserted initially
    entity->state = 0;

    // Setup iteration from grid head
    grid->current = grid->head;

    // Phase 1: Try inserting at lower depth levels if grid not too full and depth == 2
    if (grid->head != 0 && (grid->head != entity || (*(int*)((int)grid->head + 0x20) != 0))) {
        if (grid->nodeCount < 256 && grid->depthLevel == 2) {
            for (int32_t level = 1; level < 4; level++) {
                Entity* node = grid->head;
                grid->current = node;
                while (node != 0) {
                    int32_t result = checkAndInsert(grid, entity, node, level, 0);
                    if (result != 0) {
                        return 1; // Insertion successful
                    }
                    node = *(Entity**)((int)node + 0x20); // next node
                    grid->current = node;
                }
                // level increments
            }
        }

        // Phase 2: Get root grid and iterate over depth levels
        SpatialGrid* rootGrid = getRootGrid();
        int32_t level = grid->depthLevel;
        do {
            if (level > 5) {
                // Level overflow: perform cleanup and allocate new cell
                Entity* node = grid->head;
                grid->current = node;
                while (node != 0) {
                    if (node == entity) {
                        // Skip entity itself
                        node = *(Entity**)((int)grid->current + 0x20);
                        grid->current = node;
                    } else {
                        grid->current = node;
                        if (node != 0) {
                            grid->current = *(Entity**)((int)node + 0x20);
                            if (grid->head == node) {
                                grid->head = *(Entity**)((int)grid->head + 0x20);
                            }
                            removeNode(grid, node);
                        }
                        if (grid->current == 0) {
                            grid->current = grid->head;
                        }
                        grid->nodeCount--;
                        node = grid->current;
                    }
                }
                // Allocate new cell for entity
                entity->state = 3;
                entity->halfWidth = 1;
                entity->halfHeight = 1;
                entity->cellHandle = allocateCellHandle(entity->worldX, entity->worldY);
                grid->depthLevel = 2;
                return 1;
            } else {
                // Normal level: iterate over nodes and attempt insertion
                grid->current = rootGrid;
                Entity* node = (Entity*)rootGrid;
                if (node != 0) {
                    do {
                        if (node != entity && *(int*)((int)node + 4) <= level) {
                            int32_t result = checkAndInsert(grid, entity, node, 4, level);
                            if (result != 0) {
                                if (result == 2) {
                                    // Remove node (collision resolved by removal)
                                    if (node != 0) {
                                        grid->current = node;
                                        grid->current = *(Entity**)((int)node + 0x20);
                                        if (grid->head == node) {
                                            grid->head = *(Entity**)((int)grid->head + 0x20);
                                        }
                                        removeNode(grid, node);
                                        if (grid->current == 0) {
                                            grid->current = grid->head;
                                        }
                                        grid->nodeCount--;
                                    }
                                } else {
                                    // Result is 1: remove all overlapping nodes
                                    int32_t height = entity->halfHeight;
                                    Entity* iterNode = grid->head;
                                    int32_t width = entity->halfWidth;
                                    uint32_t entityCell = *(uint32_t*)((int)entity + 0x18);
                                    int32_t stateField = *(int*)((int)entity + 8);
                                    int32_t fieldC = *(int*)((int)entity + 0xC);
                                    grid->current = iterNode;
                                    if (iterNode != 0) {
                                        do {
                                            if (iterNode != entity &&
                                                *(int*)((int)iterNode + 4) <= level &&
                                                (*(uint32_t*)((int)iterNode + 0x18) & entityCell) != 0 &&
                                                (*(int*)((int)iterNode + 0x14) + *(int*)((int)iterNode + 0xC) <= fieldC ||
                                                 height + fieldC <= *(int*)((int)iterNode + 0xC)) &&
                                                (*(int*)((int)iterNode + 0x10) + *(int*)((int)iterNode + 8) <= stateField ||
                                                 width + stateField <= *(int*)((int)iterNode + 8))) {
                                                // AABB overlap: remove iterNode
                                                grid->current = iterNode;
                                                grid->current = *(Entity**)((int)iterNode + 0x20);
                                                if (grid->head == iterNode) {
                                                    grid->head = *(Entity**)((int)grid->head + 0x20);
                                                }
                                                removeNode(grid, iterNode);
                                                if (grid->current == 0) {
                                                    grid->current = grid->head;
                                                }
                                                grid->nodeCount--;
                                                iterNode = grid->current;
                                            } else {
                                                iterNode = *(Entity**)((int)grid->current + 0x20);
                                                grid->current = iterNode;
                                            }
                                        } while (iterNode != 0);
                                    }
                                    return 1;
                                }
                                return 1;
                            }
                        }
                        grid->current = node;
                        node = *(Entity**)((int)node + 0x1C); // next sibling
                        grid->current = node;
                    } while (node != 0);
                }
                // Move to next depth level
                level++;
                grid->depthLevel = level;
            }
        } while (true);
    }

    // Fallback: if no head or empty, allocate new cell for entity
    entity->state = 3;
    entity->halfWidth = 1;
    entity->halfHeight = 1;
    entity->cellHandle = allocateCellHandle(entity->worldX, entity->worldY);
    return 1;
}