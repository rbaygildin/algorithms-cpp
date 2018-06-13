/*
 * ФИО: Ярных Роман Вячеславович
 * Группа: БПИ141
 * Подгруппа: 2
 * Дата: 01.03.2016
 * Проект: реализация двусвязного списка
 * Номер проекта: 18
 * Среда: Clion (Mac OS X)
 * Язык программирования: C++11
 * Компилятор: gcc (g++)
 */

///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains pseudo-implementation part of bidirectional list structure 
/// template declared in the file's h-counterpart
///
/// © Sergey Shershakov 2015–2016
///
/// No part of this code can be used without an explicit permission of the author. 
/// The exception is done for educational goals of the course "Algorithms and Data 
/// Structures" provided by the School of Software Engineering of the Faculty 
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////

#include <stdexcept>
#include "BidiLinkedList.h"

//==============================================================================
// class BidiList<T>::Node
//==============================================================================

/**
 * Insert insNode after current node (set current node pointer to insNode)
 */
template <typename T>
typename BidiLinkedList<T>::Node*
    BidiLinkedList<T>::Node::insertAfterInternal(Node* insNode)
{
    Node* currentNext = this->_next;
    if(insNode) {
        this->_next = insNode;
        insNode->_prev = this;
        insNode->_next = currentNext;
    }
    if(currentNext)
        currentNext->_prev = insNode;
    return insNode;
}

//==============================================================================
// class BidiList<T>
//==============================================================================

/**
 * Destroy current double linked list instance
 */
template <typename T>
BidiLinkedList<T>::~BidiLinkedList()
{
    clear();
}

/**
 * Clear double linked list
 */
template <typename T>
void BidiLinkedList<T>::clear()
{
    Node* current = _head;
    while(current && current->_next){
        Node* nextNode = current->_next;
        delete current;
        current = nextNode;
    }
    invalidateSize();
}

/**
 * Get current size after all modifications
 */
template <typename T>
size_t BidiLinkedList<T>::getSize()
{
    if (_size == NO_SIZE)
        calculateSize();
    return _size;
}

/**
 * Calculate size after any modifications
 */
template <typename T>
void BidiLinkedList<T>::calculateSize()
{
    Node* current = _head;
    _size = 0;
    while(current != nullptr)
    {
        _size++;
        current = current->_next;
    }
}

/**
 * Get last node of list
 */
template <typename T>
typename BidiLinkedList<T>::Node* 
    BidiLinkedList<T>::getLastNode() const
{
    Node* last = _head;
    while(last && last->_next)
        last = last->_next;
    return last;
}

/**
 * Append value to end of list
 */
template <typename T>
typename BidiLinkedList<T>::Node* 
    BidiLinkedList<T>::appendEl(const T& val)
{
    Node* newNode = new Node(val);
    return insertNodeAfter(getLastNode(), newNode);    
}

/**
 * Insert insNode after defined node which is contained in list
 */
template <typename T>
typename BidiLinkedList<T>::Node* 
    BidiLinkedList<T>::insertNodeAfter(Node* node, Node* insNode)
{
    if (!insNode)
        throw std::invalid_argument("`insNode` is nullptr");

    if (!node)
        node = getLastNode();

    if (!node)
        _head = insNode;
    else
        node->insertAfterInternal(insNode);

    invalidateSize();

    return insNode;
}

/**
 * Insert node chain which begins from `beg` and ends by `end` after defined node
 * which is contained in list
 */
template <typename T>
void BidiLinkedList<T>::insertNodesAfter(Node* node, Node* beg, Node* end){
    if(!beg || !end)
        throw std::invalid_argument("Either `beg` or `end` is nullptr!");
    if(!node)
        node = getLastNode();

    //List is empty
    if(!node){
        insertNodeAfter(node, beg);
        beg->_prev = nullptr;
        end->_next = nullptr;
    }
    else {
        Node* nodeNext = node->_next;
        node->_next = beg;
        beg->_prev = node;
        end->_next = nodeNext;
        if(nodeNext)
            nodeNext->_prev = end;
    }
    invalidateSize();
}


#ifdef IWANNAGET10POINTS


template <typename T>
typename BidiLinkedList<T>::Node*
    BidiLinkedList<T>::insertNodeBefore(Node* node, Node* insNode)
{



    // !...
    // Реализуй метод, если хочешь получит оценку повыше!
    // !...



}


template <typename T>
void BidiLinkedList<T>::insertNodesBefore(Node* node, Node* beg, Node* end)
{
    // !...
    // Реализуй метод, если хочешь получит оценку повыше!
    // !...

}



#endif // IWANNAGET10POINTS

/**
 * Cut nodes from list
 */
template <typename T>
void BidiLinkedList<T>::cutNodes(Node* beg, Node* end)
{
    if (!beg || !end)
        throw std::invalid_argument("Either `beg` or `end` is nullptr");

    //If beg and end are in the middle of list
    if(beg->_prev && end->_next)
    {
        beg->_prev->_next = end->_next;
        end->_next->_prev = beg->_prev;
        beg->_prev = nullptr;
        end->_next = nullptr;
    }
    //If beg equals _head
    else if(!beg->_prev)
    {
        _head = end->_next;
        end->_next->_prev = nullptr;
        end->_next = nullptr;
    }
    //If end equals last node
    else if(!end->_next)
    {
        beg->_prev->_next = nullptr;
        beg->_prev = nullptr;
    }
    invalidateSize();
}

/**
 * Cut node from list
 */
template <typename T>
typename BidiLinkedList<T>::Node* 
    BidiLinkedList<T>::cutNode(Node* node)
{
    if(!node)
        throw std::invalid_argument("Argument `node` is nullptr!");
    if(node == getHeadNode())
    {
        if(node->_next)
            node->_next->_prev = nullptr;
        _head = node->_next;
        node->_next = nullptr;
    }
    else if(node == getLastNode())
    {
        if(node->_prev)
            node->_prev->_next = nullptr;
        node->_prev = nullptr;
        node->_next = nullptr;
    }
    else
    {
        node->_prev->_next = node->_next;
        node->_next->_prev = node->_prev;
        node->_prev = nullptr;
        node->_next = nullptr;
    }
    invalidateSize();
    return node;
}

/**
 * Find first node with defined value
 */
template <typename T>
typename BidiLinkedList<T>::Node* 
    BidiLinkedList<T>::findFirst(Node* startFrom, const T& val)
{
    if (!startFrom)
        return nullptr;
    int size = 0;
    Node** nodeChain = findAll(startFrom, val, size);
    if(size > 0)
        return nodeChain[0];
    else
        return nullptr;
}

/**
 * Find all nodes with defined value and return chain of found nodes with size
 */
template <typename T>
typename BidiLinkedList<T>::Node** 
    BidiLinkedList<T>::findAll(Node* startFrom, const T& val, int& size)
{
    if (!startFrom)
        return nullptr;

    Node** res = nullptr;
    size = 0;
    
    while (startFrom)
    {
        if(startFrom->_val == val)
        {
            size++;
            Node** temp = new Node*[size];
            for(int i = 0; i < size - 1; i++)
                temp[i] = res[i];
            if(res)
                delete res;
            res = temp;
        }
        startFrom = startFrom->_next;
    }
    return res;
}

// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS

template <typename T>
typename BidiLinkedList<T>::Node**  
BidiLinkedList<T>::cutAll(Node* startFrom, const T& val, int& size)
{

    // !...
    // Реализуй метод, если хочешь получит оценку повыше!
    // !...


}

#endif // IWANNAGET10POINTS