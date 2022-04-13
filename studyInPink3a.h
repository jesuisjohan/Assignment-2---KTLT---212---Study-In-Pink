/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2022
* Author: Vu Van Tien
* Date: 15.02.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

class Point {
private:
    int x;
    int y;
public:
    Point(int x=0, int y=0);
    string toString() const;

    int distanceTo(const Point & otherPoint) const;
};

class Node {
private:
    Point point;
    Node * next;

    friend class Path;

public:
    Node(const Point & point=Point(), Node * next=NULL);
    string toString() const;
};

class Path {
private:
    Node * head;
    Node * tail;
    int count;
    int length;

public:
    Path();
    ~Path();

    void addPoint(int x, int y);
    string toString() const;
    Point getLastPoint() const;

    // recently added

    int getLength() const;
};

class Character {
private:
    string name;
    Path * path;

public:
    Character(const string & name="");
    ~Character();

    string getName() const;
    void setName(const string & name);

    void moveToPoint(int x, int y);
    string toString() const;

    // recently added

    Path* getPath() const;
};

/*
* @brief 
* @param chMuderer: object represents muderer
* @param chWatson:  object represents Watson
* @param maxLength: the maximum length that Watson’s path length is allowed to exceed
the criminal’s path length
* @param maxDistance:   maximum distance between Watson’s location and the criminal
* @param outDistance:   distance between Watson and the criminal
* @returns true if successed
*/
bool rescueSherlock(
        const Character & chMurderer,
        const Character & chWatson,
        int maxLength,
        int maxDistance,
        int & outDistance
        ) {

    int l1 = chWatson.getPath()->getLength();
    int l2 = chMurderer.getPath()->getLength();

    if (l1 - l2 > maxLength) {
        outDistance = -1;
        return false;
    }
    
    Point positionWatson = chWatson.getPath()->getLastPoint(),
        positionMurderer = chMurderer.getPath()->getLastPoint();
    outDistance = positionWatson.distanceTo(positionMurderer);

    if (outDistance > maxDistance) return false;

    return true;
}

// IMPLEMENTATION

// --POINT--

Point::Point(int x, int y) :x(x), y(y) {}

string Point::toString() const {
    return "<Point[" + to_string(x) + "," + to_string(y) + "]>";
}

/*
* @returns ceiled distance
*/
int Point::distanceTo(const Point& otherPoint) const {
    double d = sqrt(pow(otherPoint.x - x, 2) + pow(otherPoint.y - y, 2));
    return (int)ceil(d);
}

// --NODE--

Node::Node(const Point& point, Node* next) 
    : point(point), next(next) {}

string Node::toString() const {
    return "<Node[" + point.toString() + "]>";
}

// --PATH--

Path::Path() {
    head = NULL;
    tail = NULL;
    count = 0;
    length = -1;
}

Path::~Path() {
    Node* current = head;
    Node* next = NULL;

    while (current) {
        next = current->next;
        free(current);
        current = next;
    }

    head = NULL;
    tail = NULL;
    count = 0;
    length = -1;
}

void Path::addPoint(int x, int y) {
    Point tempPoint(x, y);
    Node* tempNode = new Node(tempPoint, NULL);

    if (head == NULL) {
        head = tempNode;
        tail = tempNode;
    }
    else {
        tail->next = tempNode;
        tail = tail->next;
    }

    count++;
    if (count == 0) {
        length = -1;
    }
    else if (count == 1) {
        length = 0;
    }
    else {
        int tempLength = 0;
        Node* traveler = head;
        while (traveler->next) {
            Point currentPoint = traveler->point,
                nextPoint = traveler->next->point;
            tempLength += currentPoint.distanceTo(nextPoint);
            traveler = traveler->next;
        }
        length = tempLength;
    }
}

string Path::toString() const {
    string strNodeList = "[";
    Node* traveler = head;
    while (traveler) {
        strNodeList += traveler->toString();
        if (traveler->next) 
            strNodeList += ",";
        traveler = traveler->next;
    }
    strNodeList += "]";

    return "<Path[count:" + to_string(count) 
        + ",length:" + to_string(length) 
        + "," + strNodeList
        + "]>";
}

Point Path::getLastPoint() const {
    return tail->point;
}

int Path::getLength() const {
    return length;
}

// --CHARACTER--

Character::Character(const string& name) : name(name) {
    path = new Path;
}

Character::~Character() {
    delete path;
    path = NULL;
}

string Character::getName() const { return name; }

void Character::setName(const string& name) {
    this->name = name;
}

void Character::moveToPoint(int x, int y) {
    path->addPoint(x, y);
}

string Character::toString() const {
    return "<Character[name:" + name 
        + ",path:" + path->toString() 
        + "]>";
}

Path* Character::getPath() const {
    return path;
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */