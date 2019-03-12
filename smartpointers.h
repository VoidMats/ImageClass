#ifndef SMARTPOINTERS_H
#define SMARTPOINTERS_H

#include <memory>

//*** Smart pointers unique ***
template <class T>
using u_Ptr = std::unique_ptr<T>;

// This should be added if C++11, because it does not exist
//template<typename T, typename... Args>
//std::unique_ptr<T> make_unique(Args&&... args) {
//    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
//}

//*** Smart pointer share ***
template <class T>
using s_Ptr = std::shared_ptr<T>;

// Used if there is a vector in a smartpointer
template<typename T>
auto inline begin(std::shared_ptr<T> ptr) -> typename T::iterator {
    return ptr->begin();
}
template<typename T>
auto inline end(std::shared_ptr<T> ptr) -> typename T::iterator {
    return ptr->end();
}

//*** Smart pointer weak ***
template <class T>
using w_Ptr = std::weak_ptr<T>;



#endif // SMARTPOINTERS_H
