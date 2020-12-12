#include <iostream>
using namespace std;

template <class Type>
struct uzel {
    Type key;
    uzel<Type>* left;
    uzel<Type>* right;
    uzel<Type>* parent;
    bool color; //true - RED, false - BLACK
    uzel(Type k) {
        key = k;
        left = NULL;
        right = NULL;
        parent = NULL;
        color = true;
    }

};
template <class Type>
uzel<Type>* grandparent(uzel<Type>* point) {
    if ((point != NULL) && (point->parent != NULL)) {
        return point->parent->parent;
    }
    else {
        return NULL;
    }
}
template <class Type>
uzel<Type>* uncle(uzel<Type>* point) {
    uzel<Type>* g = grandparent(point);
    if (g == NULL) {
        return NULL;
    }
    if (point->parent == g->left) {
        return g->right;
    }
    else {
        return g->left;
    }
}
template <class Type>
uzel<Type>* brother(uzel<Type>* point) {
    if (point == point->parent->left) {
        return point->parent->right;
    }
    else {
        return point->parent->left;
    }
}
template <class Type>
bool iscolor(uzel<Type>* point) {
    if (point != NULL) {
        return point->color;
    }
    else {
        return false;
    }
}


template <class Type>
class RedBlackTree {
    public:
        uzel<Type>* start;
        RedBlackTree() {
            start = NULL;
        }
        void insert(Type numb) {
            if (start != NULL) {
                insert_it(numb, start);
            }
            else {
                start = new uzel<Type>(numb);
                start->color = false;
            }
        }
        void erase(Type numb) {
            erase_it(find(numb));
        }
        uzel<Type>* find(Type numb) {
            return find_it(numb, start);
        }
    private:
//searching function
        uzel<Type>* find_it(Type numb, uzel<Type>* point) {
            if (point != NULL) {
                if (numb == point->key) {
                    return point;
                }
                else if (numb < point->key) {
                    return find_it(numb, point->left);
                }
                else if (numb > point->key) {
                    return find_it(numb, point->right);
                }
                else {
                    return NULL;
                }
            }
        }
//insert function
        void insert_it(Type numb, uzel<Type>* point) {
            if (numb < point->key) {
                if (point->left != NULL) {
                    insert_it(numb, point->left);
                }
                else {
                    point->left = new uzel<Type>(numb);
                    point->left->parent = point;
                    balance_insert(point->left);
                }
            }
            else if (numb >= point->key) {
                if (point->right != NULL) {
                    insert_it(numb, point->right);
                }
                else {
                    point->right = new uzel<Type>(numb);
                    point->right->parent = point;
                    balance_insert(point->right);
                }
            }
        }
//erase function
        void erase_it(uzel<Type>* point) {
            uzel<Type>* x;
            uzel<Type>* y;
            if (point == NULL) {
                return;
            }
            if ((point->left == NULL) || (point->right == NULL)) {
                    y = point;
                }
            else {
                y = find_min(point->right);
            }
            if (!((point->left == NULL) && (point->right == NULL))) {
                if (y->left != NULL) {
                    x = y->left;
                }
                else {
                    x = y->right;
                }
                x->parent = y->parent;
                if (y->parent != NULL) {
                    if (y == y->parent->left) {
                        y->parent->left = x;
                    }
                    else {
                        y->parent->right = x;
                    }
                }
                else {
                    start = x;
                }
                if (y != point) {
                    point->key = y->key;
                }
                if (y->color == false) {
                    balance_delete(x);
                }
                delete y;
            }
            else {
                if (y->parent != NULL) {
                    x = y->parent;
                    if (y == x->left) {
                        x->left = NULL;
                    }
                    else {
                        x->right = NULL;
                    }
                }
                else {
                    delete y;
                    start = NULL;
                }
            }
        }
//balance functions
        void balance_insert(uzel<Type>* point) {
            insert_1(point);
        }
        void balance_delete(uzel<Type>* point) {
            delete_1(point);
        }
//find minimum
        uzel<Type>* find_min(uzel<Type>* point) {
            if (point->left == NULL) {
                return point;
            }
            else {
                find_min(point->left);
            }
        }
//tree turns
        void turn_left(uzel<Type>* point) {
            uzel<Type>* t = point->right;
            point->right = t->left;
            if (t->left != NULL) {
                t->left->parent = point;
            }
            if (t != NULL) {
                t->parent = point->parent;
            }
            if (point->parent != NULL) {
                if (point == point->parent->left) {
                    point->parent->left = t;
                }
                else {
                    point->parent->right = t;
                }
            }
            else {
                start = t;
            }
            t->left = point;
            if (point != NULL) {
                point->parent = t;
            }
        }
        void turn_right(uzel<Type>* point) {
            uzel<Type>* t = point->left;
            point->left = t->right;
            if (t->right != NULL) {
                t->right->parent = point;
            }
            if (t != NULL) {
                t->parent = point->parent;
            }
            if (point->parent != NULL) {
                if (point == point->parent->right) {
                    point->parent->right = t;
                }
                else {
                    point->parent->left = t;
                }
            }
            else {
                start = t;
            }
            t->right = point;
            if (point != NULL) {
                point->parent = t;
            }
        }
//cases for insert
        void insert_1(uzel<Type>* point) {
            if (point->parent == NULL) {
                point->color = false;
            }
            else {
                insert_2(point);
            }
        }
        void insert_2(uzel<Type>* point) {
            if (point->parent->color == false) {
                return;
            }
            else {
                insert_3(point);
            }
        }
        void insert_3(uzel<Type>* point) {
            uzel<Type>* u = uncle(point);
            if (u != NULL) {
                if (u->color == true) {
                    point->parent->color = false;
                    u->color = false;
                    uzel<Type>* g = grandparent(point);
                    g->color = true;
                    insert_1(g);
                }
                else {
                    insert_4(point);
                }
            }
            else {
                insert_4(point);
            }
        }
        void insert_4(uzel<Type>* point) {
            uzel<Type>* g = grandparent(point);
            if ((point == point->parent->right) && (point->parent == g->left)) {
                turn_left(point->parent);
                point = point->left;
            }
            else if ((point == point->parent->left) && (point->parent == g->right)) {
                turn_right(point->parent);
                point = point->right;
            }
            insert_5(point);
        }
        void insert_5(uzel<Type>* point) {
            uzel<Type>* g = grandparent(point);
            point->parent->color = false;
            g->color = true;
            if ((point == point->parent->left) && (point->parent == g->left)) {
                turn_right(g);
            }
            else if ((point == point->parent->right) && (point->parent == g->right)) {
                turn_left(g);
            }
        }
//cases for delete
        void delete_1(uzel<Type>* point) {
            if(point->parent != NULL) {
                delete_2(point);
            }
        }
        void delete_2(uzel<Type>* point) {
            uzel<Type>* b = brother(point);
            if(iscolor(b) == true) {
                point->parent->color = true;
                if (b != NULL) {b->color = false;}
                if (point == point->parent->left) {
                    turn_left(point->parent);
                }
                else {
                    turn_right(point->parent);
                }
            }
            delete_3(point);
        }
        void delete_3(uzel<Type>* point) {
            uzel<Type>* b = brother(point);
            if((iscolor(point->parent) == false) && (iscolor(b) == false) && (iscolor(b->left) == false) && (iscolor(b->right) == false)) {
                if (b != NULL) {b->color = true;}
                delete_1(point->parent);
            }
            else {
                delete_4(point);
            }
        }
        void delete_4(uzel<Type>* point) {
            uzel<Type>* b = brother(point);
            if((iscolor(point->parent) == true) && (iscolor(b) == false) && (iscolor(b->left) == false) && (iscolor(b->right) == false)) {
                if (b != NULL) {b->color = true;}
                point->parent->color = false;
            }
            else {
                delete_5(point);
            }
        }
        void delete_5(uzel<Type>* point) {
            uzel<Type>* b = brother(point);
            if(b->color = false) {
                if ((point->parent->left == point) && (iscolor(b->left) == true) && (iscolor(b->right) == false)) {
                    if (b != NULL) {b->color = true;}
                    if ((b != NULL) && (b->left != NULL)) {b->left->color = false;}
                    turn_right(b);
                }
                else if ((point->parent->right == point) && (iscolor(b->left) == false) && (iscolor(b->right) == true)) {
                    if (b != NULL) {b->color = true;}
                    if ((b != NULL) && (b->right != NULL)) {b->right->color = false;}
                    turn_left(b);
                }
            }
            delete_6(point);
        }
        void delete_6(uzel<Type>* point) {
            uzel<Type>* b = brother(point);
            if (b != NULL) {b->color = point->parent->color;}
            point->parent->color = false;
            if(point == point->parent->left) {
                if ((b != NULL) && (b->right != NULL)) {b->right->color = false;}
                turn_left(point->parent);
            }
            else {
                if ((b != NULL) && (b->left != NULL)) {b->left->color = true;}
                turn_right(point->parent);
            }
        }
};
