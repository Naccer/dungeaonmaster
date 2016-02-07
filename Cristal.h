#ifndef DEF_CRISTAL
#define DEF_CRISTAL


// Includes OpenGL

#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif


// Includes GLM

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Autres includes

#include "Shader.h"
#include "Texture.h"


// Classe Cristal

class Cristal
{
    public:

    Cristal(std::string const vertexShader, std::string const fragmentShader, std::string const texture,int bonus);
    Cristal();

    void afficher(glm::mat4 &projection, glm::mat4 &modelview);


    int m_bonus;
    int status; // gathered or not;


    private:

    Shader m_shader;
    Texture m_texture;



    float m_vertices[72];
    float m_coordTexture[48];
};

#endif
