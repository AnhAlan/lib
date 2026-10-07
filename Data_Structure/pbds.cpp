#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
using pbds = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
/*
   pbds<int> s;
   s.insert(x)
   s.erase(x);
   *s.find_by_order(x) // x-th smallest with 0-index
   s.order_of_key(x) // count num less < x
*/