#ifndef __CART_MANAGER_HH__
#define __CART_MANAGER_HH__

#include"Object.hpp"
#include"Error.hpp"
#include<vector>

class CartManager {
public:
    CartManager();
    ~CartManager();
    void add_item(int id, int cost, int weight);
    void add_box(int id);
    void add_to_box(int box_id, int id);
    int evaluate_cart();
private:
    std::vector<Object*> items;

    int find_item(int id);
    void check_duplicate_id(int id);
};

#endif
