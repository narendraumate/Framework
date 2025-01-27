//
//  Buffer.cpp
//  Framework
//
//  Created by Narendra Umate on 1/15/16.
//
//

#include "Buffer.h"
////////////////////////////////////////////////////////////////////////////////
Buffer::Buffer()
: m_buffer(0)
, m_count(0)
, m_size(0) {
}

Buffer::~Buffer() {
}

unsigned int Buffer::getCount() {
    return m_count;
}

unsigned int Buffer::getSize() {
    return m_size;
}
////////////////////////////////////////////////////////////////////////////////
VertexBuffer::VertexBuffer(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texcoords)
: Buffer()
, m_positions(positions)
, m_normals(normals)
, m_texcoords(texcoords) {
    glGenVertexArrays(1, &m_vertexArray);
    glGenBuffers(1, &m_buffer);
	initialize();
}

VertexBuffer::~VertexBuffer() {
	deinitialize();
    glDeleteBuffers(1, &m_buffer);
    glDeleteVertexArrays(1, &m_vertexArray);
}

void VertexBuffer::bind() {
    glBindVertexArray(m_vertexArray);
    ////glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void VertexBuffer::unbind() {
    ////glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexBuffer::initialize() {
    m_count = (m_positions.size() / 3.0f) * 8.0f;
    m_size = m_count * sizeof(float);
	//
    glBindVertexArray(m_vertexArray);
    //
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER, m_size, NULL, GL_STATIC_DRAW);
    //
    float* m_vertexData = reinterpret_cast<float*>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY));
    unsigned int vertexCount = m_positions.size() / 3.0f;
    bool fillNormals = m_normals.size() > 0;
    bool fillTexcoords = m_texcoords.size() > 0;
    for (unsigned int i = 0; i < vertexCount; ++i) {
        m_vertexData[i * 8 + 0] = m_positions.at(i * 3 + 0);
        m_vertexData[i * 8 + 1] = m_positions.at(i * 3 + 1);
        m_vertexData[i * 8 + 2] = m_positions.at(i * 3 + 2);
        m_vertexData[i * 8 + 3] = fillNormals ? m_normals.at(i * 3 + 0) : 0.0f;
        m_vertexData[i * 8 + 4] = fillNormals ? m_normals.at(i * 3 + 1) : 0.0f;
        m_vertexData[i * 8 + 5] = fillNormals ? m_normals.at(i * 3 + 2) : 0.0f;
        m_vertexData[i * 8 + 6] = fillTexcoords ? m_texcoords.at(i * 2 + 0) : 0.0f;
        m_vertexData[i * 8 + 7] = fillTexcoords ? m_texcoords.at(i * 2 + 1) : 0.0f;
    }
	glUnmapBuffer(GL_ARRAY_BUFFER);
    //
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, BUFFER_OFFSET(sizeof(float) * 6));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	//
    glBindVertexArray(0);
}

void VertexBuffer::deinitialize() {
    m_count = 0;
    m_size = 0;
	//
    glBindVertexArray(m_vertexArray);
	//
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_size, NULL, GL_STATIC_DRAW);
	//
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	//
    glBindVertexArray(0);
}
////////////////////////////////////////////////////////////////////////////////
IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices)
: Buffer()
, m_indices(indices) {
    glGenBuffers(1, &m_buffer);
	initialize();
}

IndexBuffer::~IndexBuffer() {
	deinitialize();
    glDeleteBuffers(1, &m_buffer);
}

void IndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
}

void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::initialize() {
    m_count = m_indices.size();
    m_size = m_count * sizeof(unsigned int);
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, NULL, GL_STATIC_DRAW);
    //
    unsigned int* m_indexData = reinterpret_cast<unsigned int*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY));
    for (unsigned int i = 0; i < m_count; ++i) {
        m_indexData[i] = m_indices.at(i);
    }
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //
}

void IndexBuffer::deinitialize() {
    m_count = 0;
    m_size = 0;
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//
}
////////////////////////////////////////////////////////////////////////////////
Texture2D::Texture2D() {
	glGenTextures(1, &m_texture);
}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &m_texture);
}

void Texture2D::bind() {
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glEnable(GL_TEXTURE_2D);
}

void Texture2D::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void Texture2D::initialize(const int& width, const int& height, void* const data) {
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::deinitialize() {
	// TODO
}
////////////////////////////////////////////////////////////////////////////////
Material::Material()
: ambient_texname(NULL)
, diffuse_texname(NULL)
, specular_texname(NULL)
, specular_highlight_texname(NULL)
, bump_texname(NULL)
, displacement_texname(NULL)
, alpha_texname(NULL){
}

Material::~Material() {
}

void Material::enable() {
    if (ambient_texname) {
        glActiveTexture(GL_TEXTURE0);
        ambient_texname->bind();
    }
    if (diffuse_texname) {
        glActiveTexture(GL_TEXTURE1);
        diffuse_texname->bind();
    }
    if (specular_texname) {
        glActiveTexture(GL_TEXTURE2);
        specular_texname->bind();
    }
    if (specular_highlight_texname) {
        glActiveTexture(GL_TEXTURE3);
        specular_highlight_texname->bind();
    }
    if (bump_texname) {
        glActiveTexture(GL_TEXTURE4);
        bump_texname->bind();
    }
    if (displacement_texname) {
        glActiveTexture(GL_TEXTURE5);
        displacement_texname->bind();
    }
    if (alpha_texname) {
        glActiveTexture(GL_TEXTURE6);
        alpha_texname->bind();
    }
	glActiveTexture(0);
}

void Material::disable() {
    if (ambient_texname) {
        glActiveTexture(GL_TEXTURE0);
        ambient_texname->unbind();
    }
    if (diffuse_texname) {
        glActiveTexture(GL_TEXTURE1);
        diffuse_texname->unbind();
    }
    if (specular_texname) {
        glActiveTexture(GL_TEXTURE2);
        specular_texname->unbind();
    }
    if (specular_highlight_texname) {
        glActiveTexture(GL_TEXTURE3);
        specular_highlight_texname->unbind();
    }
    if (bump_texname) {
        glActiveTexture(GL_TEXTURE4);
        bump_texname->unbind();
    }
    if (displacement_texname) {
        glActiveTexture(GL_TEXTURE5);
        displacement_texname->unbind();
    }
    if (alpha_texname) {
        glActiveTexture(GL_TEXTURE6);
        alpha_texname->unbind();
    }
    glActiveTexture(0);
}

void Material::initialize() {
}

void Material::deinitialize() {
}
////////////////////////////////////////////////////////////////////////////////
