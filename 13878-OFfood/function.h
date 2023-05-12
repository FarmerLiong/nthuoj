#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

enum position{
    FLOOR,
    STOMACH,
    TRASHCAN
};

class Food;
class Fruit;
class Meat;

class Food{
    protected:
        string name;
        int fly;
        int pos;
    public:
        // constructor
        Food();
        Food(string&);
        // copy constructor
        Food(const Food&);
        // functions
        // eaten: the food is eaten, change its position
        // thrown: the food is thrown, change its position
        // on_floor: return whether the food is on the floor
        // get_name: return the Food's name
        // get_fly: return the amount of the fly
        void eaten();
        void thrown();
        bool on_floor();
        string get_name();
        int get_fly();
        // operators
        // < : use this operator to sort the food so the output of on-floor food satisfy the requirement
        // == : determine whether the food's name is same as a string
        // << : output the food as the mentioned output format
        bool operator < (const Food&);
        bool operator == (const string&);
        friend ostream& operator << (ostream&, Food);
};

class Fruit: public Food{
    public:
        Fruit();
        Fruit(string&);
        // five_min_pass: 5 min passes
        // sickness: return whether the fruit makes someone sick
        // += : mix the food together
        void five_min_pass();
        bool sickness();
        void operator += (Fruit&);
        void operator += (Meat&);
};

class Meat: public Food{
    public:
        Meat();
        Meat(string&);
        // five_min_pass: 5 min passes
        // sickness: return whether the meat makes someone sick
        // += : mix the food together
        void five_min_pass();
        bool sickness();
        void operator += (Fruit&);
        void operator += (Meat&);
};
