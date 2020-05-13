//
// Created by Arsen on 12.05.2020.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include "Container.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

template<class A>
class Node {
private:
    A data;
    Node<A> *l, *r;
    int h;
public:
    template<class T> friend
    class AVLTree;

    Node();

    Node(A i = 0);

    Node(const Node &x);

    ~Node();
};

template<class T>
class AVLTree : public Container<T> {
public:
    AVLTree<T>();

    void remove(const T &value) override;

    bool exists(const T &value) const override;

    void insert(const T &value) override;

    void Display();

    void Delete();

    void print();

    //Node<T> *Find(AVLTree t, T key);


    ~AVLTree();

private:
    Node<T> *root;

    bool _exists(Node<T> *pNode, const T &key) const;

    int _height(const Node<T> *pNode);

    int _balance(const Node<T> *pNode);

    Node<T> *_l_rotation(Node<T> *pNode);

    Node<T> *_r_rotation(Node<T> *pNode);

    Node<T> *_R_rotation(Node<T> *pNode);

    Node<T> *_L_rotation(Node<T> *pNode);

    Node<T> *_balancing(Node<T> *pNode);

    Node<T> *_insert(Node<T> *pNode, const T &key);

    void _display(Node<T> *pNode);

    void _delete(Node<T> *pNode);

    Node<T> *_find_min(Node<T> *pNode);

    Node<T> *_find_max(Node<T> *pNode);

    Node<T> *_find(Node<T> *pNode, const T &key) const;

    Node<T> *_findelem(Node<T> *pNode, const T &key) const;

    Node<T> *_removemin(Node<T> *p);

    void _remove(Node<T> *pNode, const T &key);

    Node<T> *Doremi(Node<T> *x, const T &k);

    Node<T> *SearchMin(Node<T> *x);

    Node<T> *DeleteMin(Node<T> *x);

    void viewTreeLevel(int i, const Node<T> *pNode);
};

template
class AVLTree<int>;

template
class AVLTree<string>;

#endif //AVLTREE_AVLTREE_H
