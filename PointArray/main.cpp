#include <assert.h>
#include <iostream> // cout
#include "geometry.h"

using namespace std;

// ============== test for Point ======================

void testDefaultPointArrayConstructor(){
    PointArray pointArray;
    assert(pointArray.getSize() == 0);
}
void testCopyPointArrayConstructor(){
    Point points[10];
    for(int i = 0; i < 10; i++){
        points->setX(i);
        points->setY(2 * i);
    }
    PointArray pointArray(points, 10);
    assert(pointArray.getSize() == 10);
    for(int i = 0; i < 10; i++){
        assert(pointArray.get(i)->getX() == points[i].getX());
        assert(pointArray.get(i)->getY() == points[i].getY());
    }
}
void testPushBack(){
    PointArray pointArray;
    for(int i = 0; i < 10; i++)
        pointArray.push_back(Point(i, 2 * i));
    assert(pointArray.getSize() == 10);
    for(int i = 0; i < 10; i++) {
        assert(pointArray.get(i)->getX() == i);
        assert(pointArray.get(i)->getY() == 2 * i);
    }
}
void testInsert(){
    PointArray pointArray;
    for(int i = 0; i < 10; i++)
        pointArray.push_back(Point(i, i));
    pointArray.insert(0, Point(-1, 0));
    assert(pointArray.get(0)->getX() == -1);
    assert(pointArray.get(0)->getY() == 0);
    for(int i = 1; i < pointArray.getSize(); i++){
        assert(pointArray.get(i)->getX() == (i - 1));
        assert(pointArray.get(i)->getY() == (i - 1));
    }
    pointArray.insert(5, Point(20, -20));
    assert(pointArray.get(5)->getX() == 20);
    assert(pointArray.get(5)->getY() == -20);
    for(int i = 6; i < pointArray.getSize(); i++){
        assert(pointArray.get(i)->getX() == i - 2);
        assert(pointArray.get(i)->getY() == i - 2);
    }
    pointArray.insert(pointArray.getSize() - 1, Point(-2, -2));
    assert(pointArray.get(pointArray.getSize() - 1)->getX() == 9);
    assert(pointArray.get(pointArray.getSize() - 1)->getY() == 9);
}
void testRemove(){
    PointArray pointArray;
    pointArray.push_back(Point(1, 1));
    pointArray.push_back(Point(2, 2));
    pointArray.push_back(Point(3, 3));
    pointArray.push_back(Point(4, 4));
    assert(pointArray.getSize() == 4);
    pointArray.remove(2);
    assert(pointArray.getSize() == 3);
    assert(pointArray.get(2)->getX() == 4);
    assert(pointArray.get(2)->getY() == 4);
}
void testClear(){
    PointArray pointArray;
    pointArray.push_back(Point(1, 1));
    pointArray.push_back(Point(2, 2));
    pointArray.push_back(Point(3, 3));
    pointArray.push_back(Point(4, 4));
    pointArray.clear();
    assert(pointArray.getSize() == 0);
}
void testCopyConstructor(){
    PointArray pa1;
    pa1.push_back(Point(1, 1));
    pa1.push_back(Point(2, 2));
    PointArray pa2(pa1);
    assert(pa2.getSize() == pa1.getSize());
    assert(pa2.get(0)->getX() == 1);
    assert(pa2.get(0)->getY() == 1);
}
int main(int argc, char** argv) {
    testDefaultPointArrayConstructor();
    testCopyPointArrayConstructor();
    testPushBack();
    testInsert();
    testRemove();
    testClear();
    testCopyConstructor();
    return EXIT_SUCCESS;
}

