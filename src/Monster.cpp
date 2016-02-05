#include "Monster.h"
#include "objectLoader.h"

using namespace glm;

Monster::Monster(std::string fileMonster, std::string const vertexShader, std::string const fragmentShader, std::string const texture) :
         m_shader(vertexShader, fragmentShader), m_texture(texture),m_fileMonster(fileMonster)
{
    // Chargement du shader

    m_shader.charger();


    // Chargement de la texture

    m_texture.charger();

    loadOBJ(fileMonster.c_str(),m_vertices,m_coordTexture,m_normals);



}

Monster::~Monster()
{

}


// Méthodes


void Monster::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    // Activation du shader

    glUseProgram(m_shader.getProgramID());


        // Envoi des vertices

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, &m_vertices[0]);
        glEnableVertexAttribArray(0);


        // Envoi des coordonnées de texture

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, &m_coordTexture[0]);
        glEnableVertexAttribArray(2);


        // Envoi des matrices

        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


        // Verrouillage de la texture

        glBindTexture(GL_TEXTURE_2D, m_texture.getID());


        // Rendu

        glDrawArrays(GL_TRIANGLES, 0, m_vertices.size()-1);


        // Déverrouillage de la texture

        glBindTexture(GL_TEXTURE_2D, 0);


        // Désactivation des tableaux

        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(0);


    // Désactivation du shader

    glUseProgram(0);
}
