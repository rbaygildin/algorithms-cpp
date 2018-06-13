#include <assert.h>
#include <iostream>
#include "BidiLinkedList.h"
using namespace std;

void testSize();
void testAppendEl();
void testGetLastNode();
void testGetHead();
void testCutNodes();
void testCutNode();
void testInsertNodeAfter();
void testInsertNodesAfter();
void testExceptions();

typedef typename BidiLinkedList<int>::Node ListNode;
typedef BidiLinkedList<int> List;

int main(int argc, const char** argv){
    testSize();
    testAppendEl();
    testGetLastNode();
    testGetHead();
    testCutNodes();
    testCutNode();
    testInsertNodeAfter();
    testInsertNodesAfter();
    testExceptions();
}

void testSize(){
    BidiLinkedList<int> list;
    assert(list.getSize() == 0);
}
void testAppendEl(){
    BidiLinkedList<int> list;
    list.appendEl(0);
    list.appendEl(1);
    list.appendEl(1);
    assert(list.getSize() == 3);
    int size = 0;
    list.findAll(list.getHeadNode(), 0, size);
    assert(size == 1);
    list.findAll(list.getHeadNode(), 1, size);
    assert(size == 2);
}
void testGetLastNode(){
    BidiLinkedList<int> list;
    list.appendEl(0);
    list.appendEl(1);
    assert(list.getLastNode()->getValue() == 1);
}
void testGetHead(){
    BidiLinkedList<int> list;
    list.appendEl(1);
    list.appendEl(2);
    assert(list.getHeadNode()->getValue() == 1);
}
void testCutNodes(){
    BidiLinkedList<int> list;
    typename BidiLinkedList<int>::Node** nodeList = new typename BidiLinkedList<int>::Node*[5];
    for(int i = 0; i < 5; i++){
        nodeList[i] = new typename BidiLinkedList<int>::Node(i);
        nodeList[i] = list.insertNodeAfter(list.getLastNode(), nodeList[i]);
    }
    assert(list.getSize() == 5);
    list.cutNodes(nodeList[0], nodeList[1]);
    assert(list.getSize() == 3);
    assert(list.getHeadNode()->getValue() == 2);
    list.cutNodes(nodeList[3], nodeList[4]);
    assert(list.getSize() == 1);
    assert(list.getHeadNode()->getValue() == 2);
    assert(nodeList[1]->getNext() == nullptr);
    assert(nodeList[3]->getPrev() == nullptr);
}
void testCutNode(){
    BidiLinkedList<int> list;
    typename BidiLinkedList<int>::Node** nodeList = new typename BidiLinkedList<int>::Node*[5];
    for(int i = 0; i < 5; i++){
        nodeList[i] = new typename BidiLinkedList<int>::Node(i);
        nodeList[i] = list.insertNodeAfter(list.getLastNode(), nodeList[i]);
    }
    assert(list.getSize() == 5);
    list.cutNode(nodeList[3]);
    assert(list.getSize() == 4);
    assert(nodeList[2]->getNext() == nodeList[4]);
    assert(nodeList[4]->getPrev() == nodeList[2]);
    list.cutNode(nodeList[0]);
    assert(list.getSize() == 3);
    assert(list.getHeadNode() == nodeList[1]);
    assert(list.getLastNode() == nodeList[4]);
    list.cutNode(nodeList[4]);
    assert(list.getSize() == 2);
    assert(list.getLastNode() == nodeList[2]);
    assert(nodeList[2]->getPrev() == list.getHeadNode());
    assert(list.getHeadNode()->getNext() == nodeList[2]);
    list.cutNode(nodeList[1]);
    list.cutNode(nodeList[2]);
    assert(list.getSize() == 0);
}
void testInsertNodeAfter() {
    BidiLinkedList<int> list;
    ListNode *node1 = new ListNode(1);
    ListNode *node2 = new ListNode(2);
    ListNode *node3 = new ListNode(3);
    ListNode *node4 = new ListNode(4);
    node1 = list.insertNodeAfter(list.getLastNode(), node1);
    node3 = list.insertNodeAfter(list.getLastNode(), node3);
    node2 = list.insertNodeAfter(list.getHeadNode(), node2);
    node4 = list.insertNodeAfter(node2, node4);
    assert(list.getSize() == 4);
    assert(list.getHeadNode() == node1);
    assert(list.getLastNode() == node3);
    assert(list.getHeadNode()->getNext() == node2);
    assert(list.getLastNode()->getPrev() == node4);
}
void testInsertNodesAfter(){
    List list;
    ListNode** nodes = new ListNode*[7];
    for(int i = 0; i < 7; i++){
        nodes[i] = new ListNode(i);
        nodes[i] = list.insertNodeAfter(list.getLastNode(), nodes[i]);
    }
    assert(list.getSize() == 7);
    list.cutNodes(nodes[1], nodes[3]);
    list.insertNodesAfter(nodes[4], nodes[1], nodes[3]);
    assert(list.getSize() == 7);
    assert(list.getHeadNode()->getNext() == nodes[4]);
    assert(nodes[3]->getNext() == nodes[5]);
    assert(nodes[1]->getPrev() == nodes[4]);
    assert(nodes[5]->getPrev() == nodes[3]);
}
void testExceptions(){
    List list;
    try {
        try {
            list.appendEl(0);
            list.insertNodeAfter(list.getLastNode(), nullptr);
        }
        catch (invalid_argument){
            cout << "InsertNodeAfter: OK" << endl;
        }
        try{
            list.insertNodesAfter(list.getLastNode(), nullptr, nullptr);
        }
        catch (invalid_argument){
            cout << "InsertNodesAfter: OK" << endl;
        }
        try{
            list.cutNodes(nullptr, nullptr);
        }
        catch (invalid_argument){
            cout << "cutNodes: OK" << endl;
        }
    }
    catch(std::exception){
        cerr << "testException FAILED!" << endl;
    }
}