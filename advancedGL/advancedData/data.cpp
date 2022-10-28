int main()
{
    // parameters: target, offset, size of data, actual data
    // fill specific regions of the buffer
    glBufferSubData(GL_ARRAY_BUFFER, 24, sizeof(data), &data);

    // return a pointer to the buffer's memory
    void *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(ptr, data, sizeof(data));
    // pointer become invalid, return GL_TRUE if OpenGL map data successfully to the buffer
    bool ret = glUnmapBuffer(GL_ARRAY_BUFFER);

    // batch vertex attributes
    float positions[] = {...};
    float normals[] = {...};
    float tex[] = {...};
    // fill buffer
    // parameters: target, offset, size, data
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), &positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(normals), &normals);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normals), sizeof(tex), &tex);
    //update vertex attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(sizeof(positions)));
    glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)(sizeof(positions) + sizeof(normals)));

    // copying buffer
    glBindBuffer(GL_COPY_READ_BUFFER, vbo1);
    glBindBuffer(GL_COPY_WRITE_BUFFER, vbo2);
    //parameter: read target, write target, read offset, write offset, size
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, 8 * sizeof(float));
}