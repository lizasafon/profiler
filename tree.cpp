#include <iostream>
using namespace std;

struct uzel {
    int key;
    uzel* left;
    uzel* right;
    uzel* parent;
    bool color; //true - RED, false - BLACK
    uint16_t height=1;
    uzel(int k) {key = k; left = NULL; right = NULL; parent = NULL; height = 1; color = false;}
};

class BinSearchTree {
    public:
        uzel* start;
        BinSearchTree() {start = NULL;}
        void insert(int numb) {
            if (start != NULL) {
                insert(numb, start);
            }
            else {
                start = new uzel(numb);
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
        virtual void insert(int numb, uzel* point);
        virtual void erase(int numb, uzel* point);
};
