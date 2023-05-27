void main()
{
    vec4 position = gl_Vertex;
    float x = position.x;

    position.y = sin(x) / x;

    gl_Position = gl_ModelViewProjectionMatrix * position;
}
