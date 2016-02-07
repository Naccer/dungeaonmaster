#ifndef HERO_H
#define HERO_H



// Includes GLM


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Autres includes

#include "Input.h"
#include "Map.h"


// Classe

class Hero
{
    public:

    Hero();
    Hero(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical, float vitesse);
    ~Hero();

    void orienter(int xRel, int yRel);
    void deplacer(Input const &input,Map &m_map);
    void lookAt(glm::mat4 &modelview);

    void setPointcible(glm::vec3 pointCible);
    void setPosition(glm::vec3 position);


    float getVitesse() const;


    void setVitesse(float vitesse);
    glm::vec3 getPosition()const;

    int life;



    private:






    float m_phi;
    float m_theta;
    glm::vec3 m_orientation;

    glm::vec3 m_axeVertical;
    glm::vec3 m_deplacementLateral;

    glm::vec3 m_position;
    glm::vec3 m_pointCible;

    //float m_sensibilite;
    float m_vitesse;
};

#endif
