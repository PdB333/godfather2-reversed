// FUNC_NAME: Vector2Length
float Vector2Length(float* vec)
{
    // Compute sqrt(x^2 + y^2) for a 2D vector
    float x = vec[0];
    float y = vec[1];
    return sqrt(x * x + y * y);
}