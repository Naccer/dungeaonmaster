#include "Hero.h"


using namespace std;
// Permet d'�viter la r�-�criture du namespace glm::

using namespace glm;


// Constructeurs et Destructeur

Hero::Hero() : m_phi(0.0), m_theta(0.0), m_orientation(), m_axeVertical(0, 0, 1), m_deplacementLateral(), m_position(), m_pointCible(), m_sensibilite(0.0), m_vitesse(0.0),m_map("Maps/maze_ex.ppm")
{


}


Hero::Hero(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical, float sensibilite, float vitesse) : m_phi(0.0), m_theta(0.0), m_orientation(),
                                                                                                                    m_axeVertical(axeVertical), m_deplacementLateral(),
                                                                                                                    m_position(position), m_pointCible(pointCible),
                                                                                                                    m_sensibilite(sensibilite), m_vitesse(vitesse),  m_map("Maps/maze_ex.ppm")
{

       m_map.charger();
    // Actualisation du point cibl�

    setPointcible(pointCible);
}


Hero::~Hero()
{

}


// M�thodes

void Hero::orienter(int xRel, int yRel)
{
    // R�cup�ration des angles

    m_phi += -yRel ;
    m_theta += -xRel;

    std::cout << m_theta;


    // Limitation de l'angle phi

    if(m_phi > 89.0)
        m_phi = 89.0;

    else if(m_phi < -89.0)
        m_phi = -89.0;


    // Conversion des angles en radian

    float phiRadian = m_phi * M_PI / 180;
    float thetaRadian = m_theta * M_PI / 180;


    // Si l'axe vertical est l'axe X

    if(m_axeVertical.x == 1.0)
    {
        // Calcul des coordonn�es sph�riques

        m_orientation.x = sin(phiRadian);
        m_orientation.y = cos(phiRadian) * cos(thetaRadian);
        m_orientation.z = cos(phiRadian) * sin(thetaRadian);
    }


    // Si c'est l'axe Y

    else if(m_axeVertical.y == 1.0)
    {
        // Calcul des coordonn�es sph�riques

        m_orientation.x = cos(phiRadian) * sin(thetaRadian);
        m_orientation.y = sin(phiRadian);
        m_orientation.z = cos(phiRadian) * cos(thetaRadian);
    }


    // Sinon c'est l'axe Z

    else
    {
        // Calcul des coordonn�es sph�riques

        m_orientation.x = cos(phiRadian) * cos(thetaRadian);
        m_orientation.y = cos(phiRadian) * sin(thetaRadian);
        m_orientation.z = sin(phiRadian);
    }


    // Calcul de la normale

    m_deplacementLateral = cross(m_axeVertical, m_orientation);
    m_deplacementLateral = normalize(m_deplacementLateral);


    // Calcul du point cibl� pour OpenGL

    m_pointCible = m_position + m_orientation;
}


void Hero::deplacer(Input const &input)
{
    // Gestion de l'orientation




    // Avanc�e de la cam�ra

    int i=(int)m_position.x/16+8.0;
    int  j=(int)m_position.z/16+8.0;

    if(input.getTouche(SDL_SCANCODE_UP))
    {
        vec3 position = m_position+m_orientation * m_vitesse;
        int i=(int)position.x/16;
        int  j=(int)position.z/16;


        if(m_map.getValue(i,j) == 1)
        {

        m_position = m_position + m_orientation * m_vitesse;
        m_pointCible = m_position + m_orientation;
        SDL_Delay(100);
        }
    }


    // Recul de la cam�ra

    if(input.getTouche(SDL_SCANCODE_DOWN))
    {
        m_position = m_position - m_orientation * m_vitesse;
        m_pointCible = m_position + m_orientation;
        SDL_Delay(100);
    }


    // D�placement vers la gauche

    if(input.getTouche(SDL_SCANCODE_LEFT))
    {

        orienter(-90,0);
        SDL_Delay(100);
    }


    // D�placement vers la droite

    if(input.getTouche(SDL_SCANCODE_RIGHT))
    {

        orienter(90,0);
        SDL_Delay(100);
    }


}


void Hero::lookAt(glm::mat4 &modelview)
{
    // Actualisation de la vue dans la matrice

    modelview = glm::lookAt(m_position, m_pointCible, m_axeVertical);
}


// Getters et Setters

void Hero::setPointcible(glm::vec3 pointCible)
{
    // Calcul du vecteur orientation

    m_orientation = m_pointCible - m_position;
    m_orientation = normalize(m_orientation);


    // Si l'axe vertical est l'axe X

    if(m_axeVertical.x == 1.0)
    {
        // Calcul des angles

        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.y / cos(m_phi));

        if(m_orientation.y < 0)
            m_theta *= -1;
    }


    // Si c'est l'axe Y

    else if(m_axeVertical.y == 1.0)
    {
        // Calcul des angles

        m_phi = asin(m_orientation.y);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if(m_orientation.z < 0)
            m_theta *= -1;
    }


    // Sinon c'est l'axe Z

    else
    {
        // Calcul des angles

        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if(m_orientation.z < 0)
            m_theta *= -1;
    }


    // Conversion en degr�s

    m_phi = m_phi * 180 / M_PI;
    m_theta = m_theta * 180 / M_PI;
}


void Hero::setPosition(glm::vec3 position)
{
    // Mise � jour de la position

    m_position = position;


    // Actualisation du point cibl�

    m_pointCible = m_position + m_orientation;
}


float Hero::getSensibilite() const
{
    return m_vitesse;
}


float Hero::getVitesse() const
{
    return m_vitesse;
}


void Hero::setSensibilite(float sensibilite)
{
    m_sensibilite = sensibilite;
}


void Hero::setVitesse(float vitesse)
{
    m_vitesse = vitesse;
}

glm::vec3 Hero::getPosition() const
{
   // std::cout <<m_position.x/16 <<" " << m_position.z/16<<std::endl;
    return m_position;
}
