#include<iostream>
using namespace std;

template <class Type>
class uzel {
  public:
    Type key;
    uzel<Type>* left;
    uzel<Type>* right;
    int height=1;
    uzel(Type k) {
        key = k;
        left = right = NULL;
        height = 1;
    }
};
template <class Type>
class AVL_BinSearchTree {
  public:
    uzel<Type>* start;
    AVL_BinSearchTree() {
        start = NULL;
    }
    void insert(Type numb) {
        start = insert(numb, start);
    }
    void erase(Type numb) {
        start = erase(numb, start);
    }
    uzel<Type>* find(Type numb) {
        return find(numb, start);
    }

    void makeEmpty(uzel<Type>* t) {
        if(t == NULL) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    void display() {
        inorder(start);
        cout << endl;
    }

  protected:
    uzel<Type>* find(Type numb, uzel<Type>* point) {
        if (point != NULL) {
            if (numb == point->key) {
                return point;
            }
            else if (numb < point->key) {
                return find(numb, point->left);
            }
            else if (numb > point->key) {
                return find(numb, point->right);
            }
            else {
                return NULL;
            }
        }
        else {
            return NULL;
        }
    }
    uzel<Type>* insert(Type x, uzel<Type>* t)
    {
        if(t == NULL)
            t = new uzel<Type>(x);
        else if(x < t->key)
        {
            t->left = insert(x, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(x < t->left->key)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(x > t->key)
        {
            t->right = insert(x, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(x > t->right->key)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }
        t->height = max(height(t->left), height(t->right))+1;
        return t;
    }

    uzel<Type>* singleRightRotate(uzel<Type>* &t)
    {
        uzel<Type>* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(u->left), t->height)+1;
        return u;
    }

    uzel<Type>* singleLeftRotate(uzel<Type>* &t)
    {
        uzel<Type>* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(t->right), t->height)+1 ;
        return u;
    }

    uzel<Type>* doubleLeftRotate(uzel<Type>* &t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    uzel<Type>* doubleRightRotate(uzel<Type>* &t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    uzel<Type>* findMin(uzel<Type>* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    uzel<Type>* findMax(uzel<Type>* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    uzel<Type>* erase(Type x, uzel<Type>* t) {
            if(t==NULL) return NULL;
            if(x < t->key){
                t->left = erase(x, t->left);
            }
            else if(x > t->key) {
                t->right = erase(x, t->right);
            }
            else {
                uzel<Type>* r = t->right;
                if(t->right==NULL){
                    uzel<Type>* l = t->left;
                    delete(t);
                    t = l;
                }
                else if(t->left==NULL){
                    delete(t);
                    t = r;
                }
                else {
                    while(r->left!=NULL) r = r->left;
                    t->key = r->key;
                    t->right = erase(r->key, t->right);
                }
            }
            if(t==NULL) return t;
            t->height = 1 + max(height(t->left), height(t->right));
            int balanse_factor = height(t->left) - height(t->right);
            if(balanse_factor>1) {
                if(x > t->left->key) {
                    return singleRightRotate(t);
                }
                else {
                    t->left = singleLeftRotate(t->left);
                    return singleRightRotate(t);
                }
            }
            else if (balanse_factor < -1) {
                if(x < t->right->key){
                    return singleLeftRotate(t);
                }
                else {
                    t->right = singleRightRotate(t->right);
                    return singleLeftRotate(t);
                }
            }
            return t;
        }



    int height(uzel<Type>* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(uzel<Type>* t)
    {
        if(t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void inorder(uzel<Type>* t)
    {
        if(t != NULL) {
            inorder(t->left);
            cout << t->key << " ";
            inorder(t->right);
        }
    }

};
