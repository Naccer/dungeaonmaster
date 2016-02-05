#include "SceneOpenGL.h"
#include "Mure.h"
#include "Map.h"

#include "Monster.h"



// Permet d'éviter la ré-écriture du namespace glm::

using namespace glm;


// Constructeur de Destucteur

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),
                                                                                             m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0), m_input()
{


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


//void SceneOpenGL::bouclePrincipale()
//{
//    // Variables
//
//    unsigned int frameRate (1000 / 50);
//    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);
//
//
//    // Matrices
//
//    Map map("Maps/maze_ex.ppm");
//    map.charger();
//
//    mat4 projection;
//    mat4 modelview;
//
//    projection = perspective(100.0, (double) m_largeurFenetre / m_hauteurFenetre, 1.0, 100.0);
//    modelview = mat4(1.0);
//
//
//    // Caméra mobile
//
//    cout<<endl<<"x start*****"<< map.m_xStartPoint<<" "<<map.m_yStartPoint;
//
//    Monster monster("Monsters/monster1/waster.obj","Shaders/texture.vert","Shaders/texture.frag","Monsters/monster2/Slasher.jpg");
//
//
//
//
//
//
//
//
//
//    // Boucle principale
//
//    while(!m_input.terminer())
//    {
//        // On définit le temps de début de boucle
//
//        debutBoucle = SDL_GetTicks();
//
//
//        // Gestion des évènements
//
//        m_input.updateEvenements();
//
//        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
//            break;
//
//
//        // Nettoyage de l'écran
//
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//        // Gestion de la caméra
//
//
//    modelview = lookAt(vec3(0,0,-5),vec3(0,0,0),vec3(0,1,0));
//
//
//        /* ***** Rendu ***** */
//
//      //  mat4 sauvegardeModelview = modelview;
//
//           // modelview = rotate(modelview,200.0f,vec3(0,1,0));
//
//
//            monster.afficher(projection,modelview);
//
//
//
//
//
//        // Actualisation de la fenêtre
//
//        SDL_GL_SwapWindow(m_fenetre);
//
//
//        // Calcul du temps écoulé
//
//        finBoucle = SDL_GetTicks();
//        tempsEcoule = finBoucle - debutBoucle;
//
//
//        // Si nécessaire, on met en pause le programme
//
//        if(tempsEcoule < frameRate)
//            SDL_Delay(frameRate - tempsEcoule);
//    }
//}















void SceneOpenGL::bouclePrincipale()
{
    // Variables

    unsigned int frameRate (1000 / 50);
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);


    // Matrices

    Map map("Maps/maze_ex.ppm");
    map.charger();

    mat4 projection;
    mat4 modelview;

    projection = perspective(100.0, (double) m_largeurFenetre / m_hauteurFenetre, 1.0, 100.0);
    modelview = mat4(1.0);

    cout<<endl<<"x start*****"<< map.m_xStartPoint<<" "<<map.m_yStartPoint;

    Hero hero(vec3(map.m_xStartPoint*16+8.0, 4, map.m_yStartPoint*16+8.0), vec3(map.m_xStartPoint*16+8.0, 4,  map.m_yStartPoint*16+8.0-1.0), vec3(0, 1, 0), 1, 16);
   // m_input.afficherPointeur(false);
   // m_input.capturerPointeur(true);


    Sol solTerreux(400.0, 240.0, 15, 17, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/floor086.jpg");
    Sol roof(400.0, 240.0, 30, 15, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/Sol.jpg");
    Mure mure(16.0, 16.0, 5, 5, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/brick019.jpg");
    Monster monster("Monsters/monster1/waster.obj","Shaders/texture.vert","Shaders/texture.frag","Monsters/monster2/Slasher.jpg");
    Cristal cristal("Shaders/texture.vert", "Shaders/texture.frag", "Textures/Cristal.tga");


    float angle(0.0);

    while(!m_input.terminer())
    {

        debutBoucle = SDL_GetTicks();

        m_input.updateEvenements();

        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
            break;

        hero.deplacer(m_input);

        // Nettoyage de l'écran

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        hero.lookAt(modelview);



        /* ***** Rendu ***** */

        mat4 sauvegardeModelview = modelview;

            modelview = translate(modelview, vec3(400.0/2, -0.01, 240.0/2));
            solTerreux.afficher(projection, modelview);


        modelview = sauvegardeModelview;

        sauvegardeModelview = modelview;


            modelview = translate(modelview, vec3(400.0/2, 8.0, 240.0/2));
            roof.afficher(projection, modelview);


        modelview = sauvegardeModelview;


        // Sauvegarde de la matrice

        glm::vec3 position = hero.getPosition();


        sauvegardeModelview = modelview;

            modelview = translate(modelview, vec3(position.x,4.0,position.z-4));
            modelview = rotate(modelview, 180.0f,vec3(0, 1, 0));
            monster.afficher(projection,modelview);

        modelview = sauvegardeModelview;


        sauvegardeModelview = modelview;



   // Boucle pour le dessins des mures Est west nord et sud pour une ball de distance d8 a partir de la position actuelle

        for (int _i=-1;_i<=1;_i++)
        {
            for(int _j=-1;_j<=1;_j++)
            {

                int i=(int)position.x/16+_i;
                int  j=(int)position.z/16+_j;

                if(map.getValue(i,j)==1){

                    if(map.getValue(i+1,j) == 0)
                    {
                        modelview = translate(modelview,vec3(position.x+8+_i*16,0,position.z+_j*16));
                        modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        mure.afficher(projection, modelview);
                        cout<<"loop1"<<endl;
                    }
                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;


                    if(map.getValue(i-1,j) == 0)
                    {
                        modelview = translate(modelview,vec3(position.x-8+_i*16 ,0,position.z+_j*16));
                        modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        mure.afficher(projection, modelview);
                        cout<<"loop2"<<endl;
                    }

                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;


                    if(map.getValue(i,j+1) == 0)
                    {
                        modelview = translate(modelview,vec3(position.x+_i*16,0,position.z+8+_j*16));
                        //modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        mure.afficher(projection, modelview);
                        cout<<"loop3"<<endl;

                    }
                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;




                    if(map.getValue(i,j-1) == 0)
                    {
                        modelview = translate(modelview,vec3(position.x+_i*16 ,0,position.z-8+_j*16));
                        // modelview = rotate(modelview,90.0f,vec3(0,1,0));
                        mure.afficher(projection, modelview);
                        cout<<"loop4"<<endl;
                    }

                    modelview = sauvegardeModelview;
                    sauvegardeModelview = modelview;


                    }


                }
            }








            // Rotation du cristal
//
//            angle++;
//
//            if(angle > 360)
//                angle -= 360;
//
//
//            // Affichage du cristal
//
//            modelview = translate(modelview, vec3(5, 10.1, 0));
//            modelview = rotate(modelview, angle, vec3(0, 1, 0));
//
//            cristal.afficher(projection, modelview);




        // Restauration de la matrice

        modelview = sauvegardeModelview;


        // Actualisation de la fenêtre

        SDL_GL_SwapWindow(m_fenetre);


        // Calcul du temps écoulé

        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;


        // Si nécessaire, on met en pause le programme

        if(tempsEcoule < frameRate)
            SDL_Delay(frameRate - tempsEcoule);
    }
}






















//void SceneOpenGL::bouclePrincipale()
//{
//    // Variables
//
//    unsigned int frameRate (1000 / 50);
//    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);
//
//
//    // Matrices
//
//    Map map("Maps/maze_ex.ppm");
//    map.charger();
//
//    mat4 projection;
//    mat4 modelview;
//
//    projection = perspective(100.0, (double) m_largeurFenetre / m_hauteurFenetre, 1.0, 14.0);
//    modelview = mat4(1.0);
//
//
//    // Caméra mobile
//
//    cout<<endl<<"x start*****"<< map.m_xStartPoint<<" "<<map.m_yStartPoint;
//
//    Hero hero(vec3(map.m_xStartPoint*16+8.0, 4, map.m_yStartPoint*16+8.0), vec3(map.m_xStartPoint*16+8.0, 4,  map.m_yStartPoint*16+8.0-1.0), vec3(0, 1, 0), 1, 16);
//   // m_input.afficherPointeur(false);
//  //  m_input.capturerPointeur(true);
//
//    Monster monster("Monsters/monster1/waster.obj","Shaders/texture.vert","Shaders/texture.frag","Monsters/monster2/Slasher.jpg");
//
//
//    // Cabanne
//
// //   Cabane cabane("Shaders/texture.vert", "Shaders/texture.frag");
//
//
//    // Sols
//
//    Sol solTerreux(400.0, 240.0, 30, 30, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/floor086.jpg");
//    Sol roof(400.0, 240.0, 30, 15, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/Sol.jpg");
//
//    Mure mure(16.0, 16.0, 5, 5, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/brick019.jpg");
//
//
//    Cristal cristal("Shaders/texture.vert", "Shaders/texture.frag", "Textures/Cristal.tga");
//
//
//    float angle(0.0);
//
//
//
//
//    // Boucle principale
//
//    while(!m_input.terminer())
//    {
//        // On définit le temps de début de boucle
//
//        debutBoucle = SDL_GetTicks();
//
//
//        // Gestion des évènements
//
//        m_input.updateEvenements();
//
//        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
//            break;
//
//        hero.deplacer(m_input);
//
//
//        // Nettoyage de l'écran
//
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//        // Gestion de la caméra
//
//        hero.lookAt(modelview);
//
//
//
//        /* ***** Rendu ***** */
//
//        mat4 sauvegardeModelview = modelview;
//
//            modelview = translate(modelview, vec3(400.0/2, -0.01, 240.0/2));
//            solTerreux.afficher(projection, modelview);
//
//
//        modelview = sauvegardeModelview;
//
//        sauvegardeModelview = modelview;
//
//            modelview = translate(modelview, vec3(400.0/2, 8.0, 240.0/2));
//            roof.afficher(projection, modelview);
//
//
//        modelview = sauvegardeModelview;
//
//        glm::vec3 position = hero.getPosition();
//
//
//        sauvegardeModelview = modelview;
//
//            modelview = translate(modelview, vec3(position.x-16,0,position.z-16));
//            monster.afficher(projection,modelview);
//
//        modelview = sauvegardeModelview;
//
//        sauvegardeModelview = modelview;
//
//
//        int i=(int)position.x/16;
//        int  j=(int)position.z/16;
//        std::cout<<"++++++++"<<map.getValue(i,j)<<endl;
//
//
//
//        if(map.getValue(i,j)==1){
//
//            if(map.getValue(i+1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+8,0,position.z));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop1"<<endl;
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//            if(map.getValue(i-1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-8 ,0,position.z));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop2"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//
//            if(map.getValue(i,j+1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x,0,position.z+8));
//                //modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop3"<<endl;
//
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//            if(map.getValue(i,j-1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x ,0,position.z-8));
//               // modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop4"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//        }
//
//        i=(int)position.x/16;
//        j=(int)position.z/16-1;
//        std::cout<<"++++++++"<<map.getValue(i,j)<<endl;
//
//
//
//        if(map.getValue(i,j)==1){
//
//            if(map.getValue(i+1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+8,0,position.z-16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop1"<<endl;
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//            if(map.getValue(i-1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-8 ,0,position.z-16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop2"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//
//            if(map.getValue(i,j+1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x,0,position.z+8-16));
//                //modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop3"<<endl;
//
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//            if(map.getValue(i,j-1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x,0,position.z-8-16));
//               // modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop4"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//        }
//
//        i=(int)position.x/16+1;
//        j=(int)position.z/16-1;
//
//
//          if(map.getValue(i,j)==1){
//
//            if(map.getValue(i+1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+8+16,0,position.z-16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop1"<<endl;
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//            if(map.getValue(i-1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-8+16 ,0,position.z-16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop2"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//
//            if(map.getValue(i,j+1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+16,0,position.z+8-16));
//                //modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop3"<<endl;
//
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//            if(map.getValue(i,j-1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+16 ,0,position.z-8-16));
//               // modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop4"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//        }
//
//
//        i=(int)position.x/16+1;
//          j=(int)position.z/16;
//
//
//         if(map.getValue(i,j)==1){
//
//            if(map.getValue(i+1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+8+16,0,position.z));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop1"<<endl;
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//            if(map.getValue(i-1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-8+16 ,0,position.z));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop2"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//
//            if(map.getValue(i,j+1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+16,0,position.z+8));
//                //modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop3"<<endl;
//
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//            if(map.getValue(i,j-1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+16 ,0,position.z-8));
//               // modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop4"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//        }
//
//
//
//
//          i=(int)position.x/16-1;
//          j=(int)position.z/16-1;
//
//
//         if(map.getValue(i,j)==1){
//
//            if(map.getValue(i+1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+8-16,0,position.z-16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop1"<<endl;
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//            if(map.getValue(i-1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-8-16 ,0,position.z-16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop2"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//
//            if(map.getValue(i,j+1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-16,0,position.z+8-16));
//                //modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop3"<<endl;
//
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//            if(map.getValue(i,j-1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-16 ,0,position.z-8-16));
//               // modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop4"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//        }
//
//        i=(int)position.x/16-1;
//        j=(int)position.z/16;
//
//
//         if(map.getValue(i,j)==1){
//
//            if(map.getValue(i+1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+8-16,0,position.z));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop1"<<endl;
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//            if(map.getValue(i-1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-8-16 ,0,position.z));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop2"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//
//            if(map.getValue(i,j+1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-16,0,position.z+8));
//                //modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop3"<<endl;
//
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//            if(map.getValue(i,j-1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-16 ,0,position.z-8));
//               // modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop4"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//        }
//
//
//
//
//
//
//
//
//         i=(int)position.x/16+1;
//          j=(int)position.z/16+1;
//        std::cout<<"++++++++"<<map.getValue(i,j)<<endl;
//
//
//
//        if(map.getValue(i,j)==1){
//
//            if(map.getValue(i+1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+8+16,0,position.z+16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop1"<<endl;
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//            if(map.getValue(i-1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-8+16 ,0,position.z+16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop2"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//
//            if(map.getValue(i,j+1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+16,0,position.z+8+16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop3"<<endl;
//
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//            if(map.getValue(i,j-1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+16 ,0,position.z-8+16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop4"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//        }
//
//
//
//
//
//      i=(int)position.x/16;
//          j=(int)position.z/16+1;
//        std::cout<<"++++++++"<<map.getValue(i,j)<<endl;
//
//
//
//        if(map.getValue(i,j)==1){
//
//            if(map.getValue(i+1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+8,0,position.z+16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop1"<<endl;
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//            if(map.getValue(i-1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-8 ,0,position.z+16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop2"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//
//            if(map.getValue(i,j+1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x,0,position.z+8+16));
//                //modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop3"<<endl;
//
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//            if(map.getValue(i,j-1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x ,0,position.z-8+16));
//               // modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop4"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//        }
//
//
//        i=(int)position.x/16-1;
//          j=(int)position.z/16+1;
//        std::cout<<"++++++++"<<map.getValue(i,j)<<endl;
//
//
//
//        if(map.getValue(i,j)==1){
//
//            if(map.getValue(i+1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x+8,0,position.z+16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop1"<<endl;
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//            if(map.getValue(i-1,j) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x-8 ,0,position.z+16));
//                modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop2"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//
//            if(map.getValue(i,j+1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x,0,position.z+8+16));
//                //modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop3"<<endl;
//
//            }
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//
//
//            if(map.getValue(i,j-1) == 0)
//            {
//                modelview = translate(modelview,vec3(position.x ,0,position.z-8+16));
//               // modelview = rotate(modelview,90.0f,vec3(0,1,0));
//                mure.afficher(projection, modelview);
//                cout<<"loop4"<<endl;
//            }
//
//            modelview = sauvegardeModelview;
//            sauvegardeModelview = modelview;
//
//
//        }
//
//
//
//
//
//
//
//            // Rotation du cristal
////
////            angle++;
////
////            if(angle > 360)
////                angle -= 360;
////
////
////            // Affichage du cristal
////
////            modelview = translate(modelview, vec3(5, 10.1, 0));
////            modelview = rotate(modelview, angle, vec3(0, 1, 0));
////
////            cristal.afficher(projection, modelview);
//
//
//
//
//        // Restauration de la matrice
//
//        modelview = sauvegardeModelview;
//
//
//        // Actualisation de la fenêtre
//
//        SDL_GL_SwapWindow(m_fenetre);
//
//
//        // Calcul du temps écoulé
//
//        finBoucle = SDL_GetTicks();
//        tempsEcoule = finBoucle - debutBoucle;
//
//
//        // Si nécessaire, on met en pause le programme
//
//        if(tempsEcoule < frameRate)
//            SDL_Delay(frameRate - tempsEcoule);
//    }
//}
//
