//
//  main.cpp
//  cs32-hw3
//
//  Created by Margaret Capetz on 2/3/22.
//

#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here

class Sport {
public:
    virtual bool isOutdoor() const {return true;}
    string name() const {return m_name;}
    virtual string icon() const = 0;
    
    Sport(string name) {
        m_name = name;
    }
    virtual ~Sport() {};
private:
    string m_name;
};


class FigureSkating: public Sport {
public:
    FigureSkating(string name) : Sport(name) {}
    ~FigureSkating() {
        cout << "Destroying the FigureSkating object named " << name() << "." << endl;
    }
    
    virtual bool isOutdoor() const {return false;}
    virtual string icon() const {
        return "a skater in the Biellmann position";
    }
private:
    
};

class Snowboarding: public Sport {
public:
    Snowboarding(string name) : Sport(name) {}
    ~Snowboarding() {
        cout << "Destroying the Snowboarding object named " << name() << "." << endl;
    }
    
    virtual string icon() const {
        return "a descending snowboarder";
    }
private:
    
};

class Biathlon: public Sport {
public:
    Biathlon(string name, double distance) : Sport(name) {
        m_distance = distance;
    }
    ~Biathlon() {
        cout << "Destroying the Biathlon object named " << name() << ", distance " << m_distance << " km." << endl;
    }
    
    virtual string icon() const {
        return "a skier with a rifle";
    }

private:
    double m_distance;
};



void display(const Sport* sp)
{
    cout << sp->name() << " is ";
    if (sp->isOutdoor())
        cout << "an outdoor sport ";
    else
        cout << "an indoor sport ";
    cout << "with an icon showing " << sp->icon() << "." << endl;
}

int main()
{
    Sport* sports[4];
    sports[0] = new Snowboarding("Women's halfpipe");
      // Biathlon events have a distance in kilometers
    sports[1] = new Biathlon("Men's pursuit", 12.5);
    sports[2] = new Biathlon("Women's sprint", 7.5);
    sports[3] = new FigureSkating("Pair skating free");

    cout << "Here are the sports." << endl;
    for (int k = 0; k < 4; k++)
        display(sports[k]);

      // Clean up the sports before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete sports[k];
}
