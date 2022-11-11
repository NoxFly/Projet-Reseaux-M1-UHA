#ifndef ANTENNA_HPP
#define ANTENNA_HPP

class Antenna {
    public :
        Antenna(const int x, const int y, const int distance);
        ~Antenna();
        
        int getX() const;
        int getY() const;
        int getRange() const;

        void setX(const int x);
        void setY(const int y);
        void setRange(const int distance);

        double Intensity(); // Censé calculer la puissance de l'antenne (cf cours) pas sûr que ce soit l'intensité mais quelque chose de ce genre

    private :
        int m_x, m_y, m_distance;
};

#endif // ANTENNA_HPP