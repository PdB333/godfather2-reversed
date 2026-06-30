// FUNC_NAME: Sphere::overlaps
bool Sphere::overlaps(const Sphere& other) {
    // Squared distance between centers
    float dx = other.x - x;           // offset +0x00 (x for this)
    float dy = other.y - y;           // offset +0x04 (y)
    float dz = other.z - z;           // offset +0x08 (z)
    float distSq = dx*dx + dy*dy + dz*dz;

    // Sum of radii squared
    float radSum = radius + other.radius; // offset +0x0C (radius)
    return distSq <= radSum * radSum;
}