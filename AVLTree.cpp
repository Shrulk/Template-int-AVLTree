//
// Created by Arsen on 12.05.2020.
//

#include "AVLTree.h"

template<typename A>
Node<A>::Node() : data(0), l(NULL), r(NULL), h(0) {}

template<typename A>
Node<A>::Node(const A i) : data(i), l(NULL), r(NULL), h(0) {}

template<typename A>
Node<A>::Node(const Node &x) : data(x.data), l(x.l), r(x.r), h(x.h) {}

template<typename A>
Node<A>::~Node() {
    //if (l) delete l;
    //if (r) delete r;
}


template<typename T>
AVLTree<T>::AVLTree() {
    root = NULL;
}

template<typename T>
void AVLTree<T>::remove(const T &value) {
    Doremi(root, value);
}

template<typename T>
bool AVLTree<T>::exists(const T &value) const{
    return _exists(root, value);
}

template<typename T>
void AVLTree<T>::insert(const T &value) {
    root = _insert(root, value);
}

template<typename T>
void AVLTree<T>::Display() {
    _display(root);
}

template<typename T>
void AVLTree<T>::Delete() {
    _delete(root);
}

template<typename T>
void AVLTree<T>::print() {
    for (int i = 0; i < _height(root) + 1; i++) {
        viewTreeLevel(i, root);
        cout << endl;
    }
}

/*
template<typename T>
Node<T> *AVLTree<T>::Find(AVLTree t, T key) {

    return _find(t.root, key);
}
*/
template<typename T>
AVLTree<T>::~AVLTree() {
    delete root;
}

template<typename T>
bool AVLTree<T>::_exists(Node<T> *pNode, const T &key) const {
    return _find(pNode, key) != NULL;
}

template<typename T>
int AVLTree<T>::_height(const Node<T> *pNode) {
    //t++;
    return pNode ? pNode->h : 0;
}

template<typename T>
int AVLTree<T>::_balance(const Node<T> *pNode) {
    return pNode ? (pNode->l ? pNode->l->h : 0) - (pNode->r ? pNode->r->h : 0) : 0;
}

template<typename T>
Node<T> *AVLTree<T>::_l_rotation(Node<T> *pNode) {
    Node<T> *tmpNode = pNode->r;
    pNode->r = tmpNode->l;
    tmpNode->l = pNode;
    pNode->h = max(_height(pNode->l), _height(pNode->r)) + 1;
    tmpNode->h = max(_height(tmpNode->l), _height(tmpNode->r)) + 1;
    return tmpNode;
}

template<typename T>
Node<T> *AVLTree<T>::_r_rotation(Node<T> *pNode) {
    Node<T> *tmpNode = pNode->l;
    pNode->l = tmpNode->r;
    tmpNode->r = pNode;
    pNode->h = max(_height(pNode->l), _height(pNode->r)) + 1;
    tmpNode->h = max(_height(tmpNode->l), _height(tmpNode->r)) + 1;
    return tmpNode;
}

template<typename T>
Node<T> *AVLTree<T>::_R_rotation(Node<T> *pNode) {
    Node<T> *tmpNode = pNode->l;
    pNode->l = _l_rotation(tmpNode);
    return _r_rotation(pNode);
}

template<typename T>
Node<T> *AVLTree<T>::_L_rotation(Node<T> *pNode) {
    Node<T> *tmpNode = pNode->r;
    pNode->r = _r_rotation(tmpNode);
    return _l_rotation(pNode);
}

template<typename T>
Node<T> *AVLTree<T>::_balancing(Node<T> *pNode) {
    int b_factor = _balance(pNode);
    if (b_factor > 1) {
        if (_balance(pNode->l) >= 0) pNode = _r_rotation(pNode);
        else pNode = _R_rotation(pNode);
    } else {
        if (b_factor < -1) {
            if (_balance(pNode->r) <= 0) pNode = _l_rotation(pNode);
            else pNode = _L_rotation(pNode);
        }
    }
    return pNode;
}

template<typename T>
Node<T> *AVLTree<T>::_insert(Node<T> *pNode, const T &key) {
    if (!pNode) return new Node<T>(key);
    else if (key < pNode->data) {
        pNode->l = _insert(pNode->l, key);
        pNode = _balancing(pNode);
    } else if (key > pNode->data) {
        pNode->r = _insert(pNode->r, key);
        pNode = _balancing(pNode);
    } else {
        //Already existed
        return NULL;
    }
    pNode->h = max(_height(pNode->l), _height(pNode->r)) + 1;
    return pNode;
}

template<typename T>
void AVLTree<T>::_display(Node<T> *pNode) {
    if (!pNode) return;
    _display(pNode->l);
    cout << pNode->data << ' ';
    _display(pNode->r);
}

template<typename T>
void AVLTree<T>::_delete(Node<T> *pNode) {
    if (pNode != NULL) {
        if (pNode->l != NULL) {
            _delete(pNode->l);
        }
        if (pNode->r != NULL) {
            _delete(pNode->r);
        }
        delete pNode;
    }
}

template<typename T>
Node<T> *AVLTree<T>::_find_min(Node<T> *pNode) {
    return pNode->l ? _find_min(pNode->l) : pNode;
}

template<typename T>
Node<T> *AVLTree<T>::_find_max(Node<T> *pNode) {

    return pNode->r ? _find_max(pNode->r) : pNode;
}

template<typename T>
Node<T> *AVLTree<T>::_find(Node<T> *pNode, const T &key) const {
    if (pNode == NULL) return NULL;
    if (pNode->data == key) return pNode;
    else return pNode->data > key ? _find(pNode->l, key) : _find(pNode->r, key);
}

template<typename T>
Node<T> *AVLTree<T>::_findelem(Node<T> *pNode, const T &key) const {
    if(pNode == NULL) return NULL;
    if(pNode->data > key) return _findelem(pNode->l, key);
    if(pNode->data < key) return _findelem(pNode->r, key);
    return pNode;
}

template<typename T>
Node<T> *AVLTree<T>::_removemin(Node<T> *p) // удаление узла с минимальным ключом из дерева p
{
    if (p->l == NULL)
        return p->r;
    p->l = _removemin(p->l);
    return _balancing(p);
}

template<typename T>
void AVLTree<T>::_remove(Node<T> *pNode, const T &key) {
    Node<T> *tmpNode = _find(pNode, key);
    if (tmpNode == NULL) {
        delete tmpNode;
        return;
    }
    //Left and right subtree
    if (tmpNode->l && tmpNode->r) {
        Node<T> *minTmpNode = _find_min(tmpNode->r);
        minTmpNode->r = _removemin(tmpNode->r);
        minTmpNode->l = tmpNode->l;
        /*minTmpNode->l = pNode->l;
        minTmpNode->r = pNode->r;
        pNode = minTmpNode;*/
        //tmpNode->data = minTmpNode->data;
        pNode = minTmpNode;
        delete tmpNode, minTmpNode;

        return;
    }

    //Only left subtree
    if (tmpNode->l && !(tmpNode->r)) {
        //Node* leftTmpNode = pNode->l;
        pNode = pNode->l;
        delete tmpNode;
        return;
    }
    //Only right subtree
    if (tmpNode->r && !(tmpNode->l)) {
        pNode = pNode->r;
        delete tmpNode;
        return;
    }
    //No subtrees
    if (!(tmpNode->l && tmpNode->r)) {
        pNode = NULL;
        delete tmpNode;
        return;
    }

}

template<typename T>
Node<T> *AVLTree<T>::Doremi(Node<T> *x, const T &k) //~_remove
{
    if (!x) return NULL;
    if (k < x->data) x->l = Doremi(x->l, k);
    else if (k > x->data) x->r = Doremi(x->r, k);
    else {
        Node<T> *y = x->l;
        Node<T> *z = x->r;
        delete x;
        if (!z) return y;
        Node<T> *min = SearchMin(z);
        min->r = DeleteMin(z);
        min->l = y;
        return _balancing(min);
    }
    return _balancing(x);
}

template<typename T>
Node<T> *AVLTree<T>::SearchMin(Node<T> *x) {
    if (x->l) return SearchMin(x->l);
    else return x;
}

template<typename T>
Node<T> *AVLTree<T>::DeleteMin(Node<T> *x) {
    if (x->l == NULL) return x->r;
    x->l = DeleteMin(x->l);
    return _balancing(x);
}

template<typename T>
void AVLTree<T>::viewTreeLevel(int i, const Node<T> *pNode) {
    if (i == 0) cout << pNode->data << ' ';
    else {
        if (pNode->l) viewTreeLevel(i - 1, pNode->l);
        if (pNode->r) viewTreeLevel(i - 1, pNode->r);
    }
}