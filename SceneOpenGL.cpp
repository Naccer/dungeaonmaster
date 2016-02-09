#include "SceneOpenGL.h"
#include "Mure.h"
#include "Map.h"

#include "_AbstractMonster.h"



// Permet d'éviter la ré-écriture du namespace glm::

using namespace glm;


// Constructeur de Destucteur

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),
                                                                                             m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0), m_input()
{

    m_nombreObjets=2;


}


SceneOpenGL::~SceneOpenGL()
{
    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();
}


// Méthodes

bool SceneOpenGL::initialiserFenetre()
{
    // Initialisation de la SDL

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Version d'OpenGL

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


    // Double Buffer

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    // Création de la fenêtre

    m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Création du contexte OpenGL

    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

    if(m_contexteOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();

        return false;
    }

    return true;
}


bool SceneOpenGL::initGL()
{
    #ifdef WIN32

        // On initialise GLEW

        GLenum initialisationGLEW( glewInit() );


        // Si l'initialisation a échoué :

        if(initialisationGLEW != GLEW_OK)
        {
            // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

            std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;


            // On quitte la SDL

            SDL_GL_DeleteContext(m_contexteOpenGL);
            SDL_DestroyWindow(m_fenetre);
            SDL_Quit();

            return false;
        }

    #endif


    // Activation du Depth Buffer

    glEnable(GL_DEPTH_TEST);


    // Tout s'est bien passé, on retourne true

    return true;
}

















void SceneOpenGL::bouclePrincipale()
{
    // Variables

    unsigned int frameRate (1000 / 50);
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);

    bool win=false;




    // Chargement du map

    Map map("Maps/maze_ex.ppm");
    map.charger();

    // Mise en place objets dans leurs coordonnes dans le map

    map.setValue(6,13,5);// ici on affecte aux cordonne 6 et 13 la valeur 5 qui correspend a l'objet cristal
    map.setValue(1,4,5);
    // Mise en place des monstres dans le map

    map.setValue(6,13,7);
    map.setValue(5,12,7);

    mat4 projection;
    mat4 modelview;

    projection = perspective(100.0, (double) m_largeurFenetre / m_hauteurFenetre, 1.0, 100.0);
    modelview = mat4(1.0);

   // cout<<endl<<"x start*****"<< map.m_xStartPoint<<" "<<map.m_yStartPoint;

    Hero hero(vec3(map.m_xStartPoint*16+8.0, 8.0, map.m_yStartPoint*16+8.0), vec3(map.m_xStartPoint*16+8.0, 8.0,  map.m_yStartPoint*16+8.0-1.0), vec3(0, 1, 0), 16);
   // m_input.afficherPointeur(false);
   // m_input.capturerPointeur(true);


    Sol solTerreux(400.0, 240.0, 15, 17, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/floor086.jpg");
    Sol roof(400.0, 240.0, 30, 15, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/Sol.jpg");
    Mure mure(16.0, 16.0, 5, 5, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/brick019.jpg");

    _AbstractMonster _abstractMonster1("Monsters/monster1/waster.obj","Shaders/texture.vert","Shaders/texture.frag","Monsters/Monster1/WasterDiffuse.jpg");
    _AbstractMonster _abstractMonster2("Monsters/Monster2/slasher.obj","Shaders/texture.vert","Shaders/texture.frag","Monsters/Monster2/slasher.bmp");
   // _AbstractMonster _AbstractMonster3("_AbstractMonsters/_AbstractMonster3/alieCannecromorph.obj","Shaders/texture.vert","Shaders/texture.frag","_AbstractMonsters/_AbstractMonster3/Alien_Necromorph_D.tga");
   // Cristal cristal1("Shaders/texture.vert", "Shaders/texture.frag", "Textures/Cristal.tga",5);

    Cristal cristal2("Shaders/texture.vert", "Shaders/texture.frag", "Textures/Cristal.tga",5);


    float angle(0.0);

    while(!m_input.terminer())
    {

        debutBoucle = SDL_GetTicks();

        m_input.updateEvenements();

        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
            break;

        hero.deplacer(m_input,map,m_nombreObjets);

        // Nettoyage de l'écran

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        hero.lookAt(modelview);



        /* ***** Rendu ***** */

        mat4 sauvegardeModelview = modelview;

            modelview = translate(modelview, vec3(400.0/2, -0.01, 240.0/2));
            solTerreux.afficher(projection, modelview);


        modelview = sauvegardeModelview;

        sauvegardeModelview = modelview;


            modelview = translate(modelview, vec3(400.0/2, 16.0, 240.0/2));
            roof.afficher(projection, modelview);


        modelview = sauvegardeModelview;

        sauvegardeModelview = modelview;

        glm::vec3 position = hero.getPosition();

           // modelview = scale(modelview,vec3(4.0,4.0,4.0));

            modelview = translate(modelview, vec3(6*16+8.0,4.0,13*16+8.0));
            modelview = rotate(modelview, 180.0f,vec3(0, 1, 0));
            modelview = scale(modelview,vec3(2,2,2));
           // _AbstractMonster1.afficher(projection,modelview);

        modelview = sauvegardeModelview;

        sauvegardeModelview = modelview;



           // modelview = translate(modelview, vec3(position.x,4.0,position.z-1));
            modelview = rotate(modelview, 180.0f,vec3(0, 1, 0));
          //  _abstractMonster2.deplacer(m_input,map,hero,modelview);
            _abstractMonster2.afficher(projection,modelview);

        modelview = sauvegardeModelview;

        sauvegardeModelview = modelview;


         angle++;   //effet de rotation pour les objets

            if(angle > 360)
                angle -= 360;



   // Boucle pour le rendu des mures(id->0)  Est west nord et sud pour une ball de distance d8 a partir de la position actuelle

   // + rendu des objets id->5
   // rendu monster id->4

        for (int _i=-1;_i<=1;_i++)
        {
            for(int _j=-1;_j<=1;_j++)
            {

                int i=(int)position.x/16+_i;
                int  j=(int)position.z/16+_j;

                if(map.getValue(i,j)>=1){

                    if(map.getValue(i+1,j) == 0)
                    {
                        modelview = translate(modelview,vec3(position.x+8+_i*16,8.0,position.z+_j*16));
                        modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        mure.afficher(projection, modelview);
                     //   cout<<"loop1"<<endl;
                    }
                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;

                    if(map.getValue(i+1,j) == 5)
                    {
                        modelview = translate(modelview,vec3(position.x+8+_i*16,2.0,position.z+_j*16));
                        //modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        cristal2.afficher(projection, modelview);
                     //   cout<<"loop1"<<endl;
                    }
                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;

                    if(map.getValue(i+1,j) == 7)
                    {
                        modelview = translate(modelview,vec3(position.x+8+_i*16,6.0,position.z+_j*16));
                        modelview = scale(modelview,vec3(3,3,3));

                        modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        modelview = rotate(modelview, 180.0f,vec3(0, 1, 0));
                        vec3 positionMonstre(vec3(position.x+8+_i*16,6.0,position.z+_j*16));
                        _abstractMonster2.deplacer(map,hero,positionMonstre,modelview);

                        _abstractMonster1.afficher(projection, modelview);

                     //   cout<<"loop1"<<endl;
                    }
                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;




                    if(map.getValue(i-1,j) == 0)
                    {
                        modelview = translate(modelview,vec3(position.x-8+_i*16 ,8.0,position.z+_j*16));
                        modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        mure.afficher(projection, modelview);
                       // cout<<"loop2"<<endl;
                    }

                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;

                     if(map.getValue(i-1,j) == 5)
                    {
                        modelview = translate(modelview,vec3(position.x-8+_i*16 ,2.0,position.z+_j*16));
                        //modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        cristal2.afficher(projection, modelview);
                       // cout<<"loop2"<<endl;
                    }

                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;


                    if(map.getValue(i,j+1) == 0)
                    {
                        modelview = translate(modelview,vec3(position.x+_i*16,8.0,position.z+8+_j*16));
                        //modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        mure.afficher(projection, modelview);
                       // cout<<"loop3"<<endl;

                    }
                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;


                     if(map.getValue(i,j+1) == 5)
                    {
                        modelview = translate(modelview,vec3(position.x+_i*16,2.0,position.z+8+_j*16-8.0));
                        //modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        modelview = rotate(modelview, angle, vec3(0, 1, 0));
                        cristal2.afficher(projection, modelview);
                       // cout<<"loop3"<<endl;

                    }
                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;




                    if(map.getValue(i,j-1) == 0)
                    {
                        modelview = translate(modelview,vec3(position.x+_i*16 ,8.0,position.z-8+_j*16));
                        // modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        mure.afficher(projection, modelview);
                        //cout<<"loop4"<<endl;
                    }

                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;

                     if(map.getValue(i,j-1) == 5)
                    {
                        modelview = translate(modelview,vec3(position.x+_i*16 ,2.0,position.z-8+_j*16-8.0));
                        // modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        modelview = rotate(modelview, angle, vec3(0, 1, 0));
                        cristal2.afficher(projection, modelview);

                        //cout<<"loop4"<<endl;
                    }

                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;


                    }


                }
            }


            modelview = sauvegardeModelview;
            sauvegardeModelview = modelview;




        modelview = sauvegardeModelview;


        // Actualisation de la fenêtre

        SDL_GL_SwapWindow(m_fenetre);


        //verfication si on a collecter tous les objets et on et a la sortie

        if(m_nombreObjets ==0 && (int)position.x /16 ==map.m_xEndPoint && (int)position.z/16 == map.m_yEndPoint)
        {
            win=true;
            break;
        }


        // Calcul du temps écoulé

        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;


        // Si nécessaire, on met en pause le programme

        if(tempsEcoule < frameRate)
            SDL_Delay(frameRate - tempsEcoule);
    }


    if(win == true)
        cout<<"you win";
}

