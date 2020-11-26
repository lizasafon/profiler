#include <iostream>
#include "tree.cpp"
using namespace std;

class RedBlackTree : public BinSearchTree {
    private:
//balance functions
        void balance_insert(uzel* point) {
            insert_1(point);
        }
        void balance_delete(uzel* point) {
            delete_1(point);
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
