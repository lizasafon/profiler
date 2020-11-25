#include <iostream>
using namespace std;

struct uzel {
    int key;
    uzel* left;
    uzel* right;
    uzel* parent;
    bool color; //true - RED, false - BLACK
};

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


class BinSearchTree {
    public:
        uzel* start;
        BinSearchTree() {
            start = NULL;
        }

        void insert(int numb) {
            if (start != NULL) {
                insert(numb, start);
            }
            else {
                start = new uzel;
                start->key = numb;
                start->left = NULL;
                start->right = NULL;
                start->parent = NULL;
                start->color = false;
            }
        }
        void erase(int numb) {
            erase(numb, start);
        }
        uzel* find(int numb) {
            return find(numb, start);
        }

    protected:
        uzel* find(int numb, uzel* point) {
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
        }

        void insert(int numb, uzel* point) {
            if (numb < point->key) {
                if (point->left != NULL) {
                    insert(numb, point->left);
                }
                else {
                    point->left = new uzel;
                    point->left->key = numb;
                    point->left->left = NULL;
                    point->left->right = NULL;
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
                    point->right = new uzel;
                    point->right->key = numb;
                    point->right->left = NULL;
                    point->right->right = NULL;
                    point->right->parent = point;
                    point->right->color = true;
                    balance_insert(point->right);
                }
            }
        }

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
                        delete point;
                        //balance_delete(); balance uzel point->parent
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
                        //here uzel with 2 children should be deleted
                    }
                }
            }
        }

        void balance_insert(uzel* point) {}
        void balance_delete(uzel* point) {}
};
