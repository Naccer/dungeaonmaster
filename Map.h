#ifndef MAP_H
#define MAP_H



#include <iostream>
#include <fstream>
#include <string>
using namespace std;



typedef struct {
     unsigned char red,green,blue;
} PPMPixel;

typedef struct{
    int x;
    int y;

}Point;




class Map
{
    public:
        Map(std::string fileMap);
        virtual ~Map();

        void charger();
        bool isStartPoint(Point point);
        bool isStartPoint(int _x, int _y);
        int getValue(int _x,int _y);
        void setValue(int _x, int _y,int value);

          //TODO: create accessors fot these methods
        int m_xStartPoint;
        int m_yStartPoint;



        bool isEndPoint();




    private:

        int m_matrix[25][15];// la matrice doit etre transpose pour correspendre au map de l'opnGl
        Point m_startPoint;

        int m_xEndPoint;
        int m_yEndPoint;

        std::string m_fileMap;
        unsigned int m_largeurMap;
        unsigned int m_hauteurMap;
};

#endif // MAP_H
