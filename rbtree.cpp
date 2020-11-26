#include <iostream>
#include <tree.cpp>
using namespace std;

uzel* grandparent(uzel* point) {
    if ((point != NULL) && (point->parent != NULL)) {
        return point->parent->parent;
    }
    else {
        return NULL;
    }
}

uzel* uncle(uzel* point) {
    uzel* g = grandparent(point);
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

uzel* brother(uzel* point) {
    if (point == point->parent->left) {
        return point->parent->right;
    }
    else {
        return point->parent->left;
    }
}

class RedBlackTree : public BinSearchTree {
    private:
//insert function
        void insert(int numb, uzel* point) {
            if (numb < point->key) {
                if (point->left != NULL) {
                    insert(numb, point->left);
                }
                else {
                    point->left = new uzel(numb);
                    point->left->parent = point;
                    point->left->color = true;
                    balance_insert(point->left);
                }
            }
            else if (numb >= point->key) {
                if (point->right != NULL) {
                    insert(numb, point->right);
                }
                else {
                    point->right = new uzel(numb);
                    point->right->parent = point;
                    point->right->color = true;
                    balance_insert(point->right);
                }
            }
        }
//erase function
        void erase(int numb, uzel* point) {
            if (point == NULL) {
                return;
            }
            else {
                if (numb < point->key) {
                    erase(numb, point->left);
                }
                else if (numb > point->key) {
                    erase(numb, point->right);
                }
                else if (numb == point->key) {
                    if ((point->left == NULL) && (point->right == NULL)) {
                        if (point->parent->left == point) {
                            point->parent->left = NULL;
                        }
                        else {
                            point->parent->right = NULL;
                        }
                        uzel* u = point->parent;
                        delete point;
                        balance_delete(u);
                    }
                    else if ((point->left == NULL) && (point->right != NULL)) {
                        point->left = point->right->left;
                        point->right = point->right->right;
                        point->key = point->right->key;
                        point->right->left->parent = point;
                        point->right->right->parent = point;
                        delete point->right;
                        balance_delete(point);
                    }
                    else if ((point->left != NULL) && (point->right == NULL)) {
                        point->left = point->left->left;
                        point->right = point->left->right;
                        point->key = point->left->key;
                        point->left->left->parent = point;
                        point->left->right->parent = point;
                        delete point->left;
                        balance_delete(point);
                    }
                    else {
                        uzel* u = find_min(point->right);
                        point->key = u->key;
                        erase(u->key, u);
                    }
                }
            }
        }
//balance functions
        void balance_insert(uzel* point) {
            insert_1(point);
        }
        void balance_delete(uzel* point) {
            delete_1(point);
        }
//find minimum
        uzel* find_min(uzel* point) {
            if (point->left == NULL) {
                return point;
            }
            else {
                find_min(point->left);
            }
        }
//tree turns
        void turn_left(uzel* point) {
            uzel* n = point->right;
            n->parent = point->parent;
            if (point->parent != NULL) {
                if (point == point->parent->left) {
                    point->parent->left = n;
                }
                else {
                    point->parent->right = n;
                }
            }
            point->right = n->left;
            if (n->left != NULL) {
                n->left->parent = point;
            }
            point->parent = n;
            n->left = point;
        }
        void turn_right(uzel* point) {
            uzel* n = point->left;
            n->parent = point->parent;
            if (point->parent != NULL) {
                if (point == point->parent->left) {
                    point->parent->left = n;
                }
                else {
                    point->parent->right = n;
                }
            }
            point->left = n->right;
            if (n->right != NULL) {
                n->right->parent = point;
            }
            point->parent = n;
            n->right = point;
        }
//cases for insert
        void insert_1(uzel* point) {
            if (point->parent == NULL) {
                point->color = false;
            }
            else {
                insert_2(point);
            }
        }
        void insert_2(uzel* point) {
            if (point->parent->color == false) {
                return;
            }
            else {
                insert_3(point);
            }
        }
        void insert_3(uzel* point) {
            uzel* u = uncle(point);
            if ((u->color == true) && (u != NULL)) {
                point->parent->color = false;
                u->color = false;
                uzel* g = grandparent(point);
                g->color = true;
                insert_1(g);
            }
            else {
                insert_4(point);
            }
        }
        void insert_4(uzel* point) {
            uzel* g = grandparent(point);
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
        void insert_5(uzel* point) {
            uzel* g = grandparent(point);
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
        void delete_1(uzel* point) {
            if(point->parent != NULL) {
                delete_2(point);
            }
        }
        void delete_2(uzel* point) {
            uzel* b = brother(point);
            if(b->color == true) {
                point->parent->color = true;
                b->color = false;
                if (point == point->parent->left) {
                    turn_left(point->parent);
                }
                else {
                    turn_right(point->parent);
                }
            }
            delete_3(point);
        }
        void delete_3(uzel* point) {
            uzel* b = brother(point);
            if((point->parent->color == false) && (b->color = false) && (b->left->color = false) && (b->right->color = false)) {
                b->color = true;
                delete_1(point->parent);
            }
            else {
                delete_4(point);
            }
        }
        void delete_4(uzel* point) {
            uzel* b = brother(point);
            if((point->parent->color == true) && (b->color = false) && (b->left->color = false) && (b->right->color = false)) {
                b->color = true;
                point->parent->color = false;
            }
            else {
                delete_5(point);
            }
        }
        void delete_5(uzel* point) {
            uzel* b = brother(point);
            if(b->color = false) {
                if ((point->parent->left == point) && (b->left->color = true) && (b->right->color = false)) {
                    b->color = true;
                    b->left->color = false;
                    turn_right(b);
                }
                else if ((point->parent->right == point) && (b->left->color = false) && (b->right->color = true)) {
                    b->color = true;
                    b->right->color = false;
                    turn_left(b);
                }
            }
            delete_6(point);
        }
        void delete_6(uzel* point) {
            uzel* b = brother(point);
            b->color = point->parent->color;
            point->parent->color = false;
            if(point == point->parent->left) {
                b->right->color = false;
                turn_left(point->parent);
            }
            else {
                b->left->color = true;
                turn_right(point->parent);
            }
        }
};
