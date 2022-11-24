#ifndef VECZ_HPP
#define VECZ_HPP

#include <iostream>
#include <vector>

//Class that represents a vector with interger index (positive and negative)

template <typename T>
class VecZ
{
    private:
        //vector of the positive values
        std::vector<T> vec_pos;

        //vector of the negative values
        std::vector<T> vec_neg;

        //min allocate index
        int min;

        //max allocate index
        int max;

        //minimum index in the vector
        int index_min;

        //maximum index in the vector
        int index_max;
    public:

        //Constructor
        VecZ();

        //Destructor
        ~VecZ();

        /**
         * @param i integer, index to insert your element
         * @param elt element to add
        */
        void insert(int i, T elt);

        /**
         * redefine the operator []
        */
        T &operator[](int i);

        /**
         * getter index_min
         * @return index_min
        */
        int get_min() const;

        /**
         * getter index_max
         * @return index_max
        */
        int get_max() const;

        /**
         * print the vector
        */
        void print();
};

#include "back/VecZ.tpp"

#endif