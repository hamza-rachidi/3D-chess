#include "object.h"

#include <iostream>
#include "renderer.h"
#ifdef WINDOWS
#include "glm/gtc/matrix_transform.hpp"
#else
#include "glm/gtx/transform.hpp"
#endif

#include <exception>


Object::Object(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> colors, std::vector<glm::vec3> XZPositios, std::string texturePath):m_vb(0), m_uvsb(0), m_cb(0), m_texture(0), position(0,0,0), rotationAngles(0,0,0)
{
    m_vb = new VertexBuffer(vertices);
    m_uvsb = new UVBuffer(uvs);

    m_cb = new VertexBuffer(colors);
    Pos_b = new VertexBuffer(XZPositios);

    m_texture = new Texture(texturePath);


}


Object::~Object()
{
    delete m_vb;
    if (m_uvsb) delete m_uvsb;
    if (m_texture) delete m_texture;
    if (m_cb) delete m_cb;
    if (Pos_b) delete Pos_b;
}

void Object::Bind() const
{
    m_vb->Bind(0);
    if (m_uvsb) m_uvsb->Bind(1);
    if (m_texture) m_texture->Bind(0);
    if (m_cb) m_cb->Bind(2);
    if (Pos_b) Pos_b->Bind(3);
}

void Object::Unbind() const
{
    m_vb->Unbind();
    if (m_uvsb) m_uvsb->Unbind();
    if (m_cb) m_cb->Unbind();
    if (Pos_b) Pos_b->Unbind();
    if (m_texture) m_texture->Unbind();
}



void Object::Draw() const
{
    GLCall(glDrawArrays(GL_TRIANGLES,0, m_vb->getSize()));
}

glm::mat4 Object::getModelMatrix()
{
    glm::mat4 m = glm::rotate(glm::translate(glm::mat4(1), position), rotationAngles.x, glm::vec3(1,0,0));
    m=glm::rotate(m, rotationAngles.y, glm::vec3(0,1,0));
    m=glm::rotate(m, rotationAngles.z, glm::vec3(0,0,1));
    return m;
}
