#include "OrderedList.hpp"

template <typename T>
void OrderedList<T>::add(T value) {
    if (list.isEmpty()) {
        list.addFront(value);
        return;
    }

    for (int i = 0; i < list.getSize(); i++) {
        if (list[i] >= value) {
            list.addAt(value, i);
            return;
        }
    }

    list.addBack(value);
}

template <typename T>
void OrderedList<T>::remove() {
    list.removeFront();
}

template <typename T>
bool OrderedList<T>::find(T value) const {
    return list.find(value);
}

template <typename T>
void OrderedList<T>::makeEmpty() {
    list.makeEmpty();
}
template <typename T>
bool OrderedList<T>::isEmpty() const {
    if (list.isEmpty()) {
        return true;
    } else {
        return false;
    }
}

template <typename T>
void OrderedList<T>::printAscending() const {
    for (int i = 0; i < list.getSize(); i++) {
        if (i != list.getSize() - 1) {
            std::cout << list[i] << " -> ";
        } else {
            std::cout << list[i];
        }
    }
    std::cout << std::endl;
}
template <typename T>
void OrderedList<T>::printDescending() const {
    for (int i = list.getSize() - 1; i >= 0; i--) {
        if (i > 0) {
            std::cout << list[i] << " -> ";
        } else {
            std::cout << list[i];
        }
    }
    std::cout << std::endl;
}

template <typename T>
OrderedList<T> OrderedList<T>::merge(const List<T> &list1,
                                     const List<T> &list2) {
    OrderedList<T> mergedList;

    // std::cout << "[DEBUG] Merging lists: list1 size=" << list1.getSize()
    //           << ", list2 size=" << list2.getSize() << std::endl;

    for (int i = 0; i < list1.getSize(); i++) {
        // std::cout << "[DEBUG] Accessing list1[" << i
        //           << "], list1 size: " << list1.getSize() << std::endl;
        mergedList.add(list1[i]);
    }

    for (int i = 0; i < list2.getSize(); i++) {
        // std::cout << "[DEBUG] Accessing list2[" << i
        //           << "], list2 size: " << list2.getSize() << std::endl;
        mergedList.add(list2[i]);
    }

    return mergedList;
}
