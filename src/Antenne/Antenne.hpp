#ifndef ANTENNE_HPP
#define ANTENNE_HPP

class Antenne {
    public :
        Antenne(int x, int y, int distance);
        ~Antenne();
        int getX();
        int getY();
        int getDistance();
        void setX(int x);
        void setY(int y);
        void setDistance(int distance);
        double Intensite(); //Censé calculer la puissance de l'antenne (cf cours) pas sûr que ce soit l'intensité mais quelque chose de ce genre
    private :
        int d_x, d_y, d_distance;
};

#endif //ANTENNE_HPP