#ifndef MONSTER_H
#define MONSTER_H



// Includes OpenGL

#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

#include <vector>
// Includes GLM

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Autres includes

#include "Shader.h"
#include "Texture.h"


// Classe Monster

class Monster
{
    public:

    Monster(std::string fileMonster, std::string const vertexShader, std::string const fragmentShader, std::string const texture);
    ~Monster();

    void afficher(glm::mat4 &projection, glm::mat4 &modelview);


    private:

    std::string m_fileMonster;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector <glm::vec2> m_coordTexture;

    Shader m_shader;
    Texture m_texture;

};

#endif // MONSTER_H
