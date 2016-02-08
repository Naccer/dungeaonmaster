#include "Map.h"

Map::Map(std::string fileMap):m_fileMap(fileMap),m_hauteurMap(0),m_largeurMap(0)
{


}

Map::~Map()
{

}



void Map::charger() {


    std::fstream myFile(m_fileMap.c_str(), std::ios_base::in);


    char *type = new char[2];
    myFile >> type;
//    std::cout << "Function read PPM:" << std::endl;
//    std::cout << "type:" << type << std::endl;

    myFile >>  m_largeurMap;
    myFile >> m_hauteurMap;





//    std::cout << "lines:" << m_hauteurMap<< std::endl;
//    std::cout << "coluns:" << m_largeurMap << std::endl;

    int max;
    myFile >> max;
    std::cout << "max:" << max << std::endl;


    const unsigned int HAUTEUR =m_hauteurMap/16;
    const unsigned int LARGEUR =m_largeurMap/16;





    int co=0;

    for (int i = 0; i < m_hauteurMap; i++)
    {
        for(int j=0;j<m_largeurMap;j++)
        {


            unsigned char r;
            unsigned char g;
            unsigned char b;
            myFile >> r;
            myFile >> g;
            myFile >>  b;
           // std::cout << "(" <<(int) r<<","<<(int)g <<"),"<<(int) b++<<std::endl;

            if((i%16 == 0) and (j%16 == 0))
            {
                int _j=i/16;
                int _i=j/16;
                //cout<< co++ <<"  " ;

                if ((int)r == 0 and (int)g == 0 and (int)b == 0)
                    m_matrix[_i][_j] = 0;
                else if ((int)r == 255 and (int)g == 255 and (int)b == 255)
                {
//                    cout<< "one";
                    m_matrix[_i][_j] = 1;
                }

                // initial point

                 else if ((int)r == 255 and (int)g == 0 and (int)b == 0)
                {

                    m_matrix[_i][_j] = 2;//start point
                    m_xStartPoint= _i;
                    m_yStartPoint=_j;
                    m_startPoint.x = _i;
                    m_startPoint.y = _j;
                }

                // End point

                else if ((int)r == 0 and (int)g == 255 and (int)b == 0)
                {
                    //cout<<"end point at "<< i/16<<","<<j/16<<endl;
                    m_matrix[_i][_j] = 3; // end point

                    m_xEndPoint= _i;
                    m_yEndPoint=_j;
                }

            }

        }
    }

   // cout<<endl;





    for (int i = 0; i < m_largeurMap/16; i++)
    {
        for(int j=0;j<m_hauteurMap/16;j++)
        {
            int tmp=m_matrix[i][j];
            m_matrix[i][j] = m_matrix[i][m_hauteurMap/16-j-1];
            m_matrix[i][m_hauteurMap/16-j-1] = tmp;

        }
     //   cout<<endl;
    }





    myFile.close();

}


bool Map::isStartPoint(Point point)
{
    return ((point.x == m_startPoint.x) and (point.y == m_startPoint.y));

}

bool Map::isStartPoint(int _x, int _y)
{
    return ((_x == m_startPoint.x) and (_y == m_startPoint.y));

}

bool Map::isEndPoint()
{

}

int Map::getValue(int _x, int _y)
{
    return m_matrix[_x][_y];
}

void Map::setValue(int _x, int _y,int value)
{
     m_matrix[_x][_y]=value;
}




