#include<iostream>
using namespace std;

template <class Type>
struct uzel {
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
    uzel<Type>* erase(Type x, uzel<Type>* t)
    {
        uzel<Type>* temp;
        if(t == NULL)
            return NULL;

        else if(x < t->key)
            t->left = erase(x, t->left);
        else if(x > t->key)
            t->right = erase(x, t->right);

        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->key = temp->key;
            t->right = erase(t->key, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right))+1;
        if(height(t->left) - height(t->right) == 2)
        {
            if(height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);

            else
                return doubleLeftRotate(t);
        }
        else if(height(t->right) - height(t->left) == 2)
        {
            if(height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);

            else
                return doubleRightRotate(t);
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
};
