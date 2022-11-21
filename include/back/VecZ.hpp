#ifndef VECZ_HPP
#define VECZ_HPP

#include <iostream>
#include <vector>

//Class that represents a vector with interger index (positive and negative)

template <class T>
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
        VecZ() : vec_pos{1}, vec_neg{1}, min{0}, max{0}, index_min{0}, index_max{0}
        {
        }

        //Destructor
        ~VecZ() {}

        /**
         * @param i integer, index to insert your element
         * @param elt element to add
        */
        void insert(int i, T elt)
        {
            if(i >= 0)
            {
                //RESIZE
                if(i > index_max) index_max = i;
                while(i >= max)
                {
                    vec_pos.resize(2 * max + 1);
                    max = 2 * max + 1;
                }

                vec_pos[i] = elt;
            } else {
                if(i < index_min) index_min = i;
                
                while(i <= min)
                {
                    min = 2 * min - 1;
                    //std::cout << -min << std::endl;
                    vec_neg.resize(size_t(-min));
                }
                vec_neg[-i] = elt;
                //std::cout << i << " " << vec_neg[-i] << std::endl;
            }
        }

        /**
         * redefine the operator []
        */
        T &operator[](int i)
        {
            if(i >= 0)
            {
                if(i > index_max) index_max = i;
                while(i >= max)
                {
                    vec_pos.resize(2 * max + 1);
                    max = 2 * max + 1;
                }
                return vec_pos[i];
            } else 
            {
                if(i < index_min) index_min = i;
                
                while(i <= min)
                {
                    min = 2 * min - 1;
                    vec_neg.resize(size_t(-min));
                }

                return vec_neg[-i];
            }
        }

        /**
         * getter index_min
         * @return index_min
        */
        int get_min() const
        {
            return index_min;
        }

        /**
         * getter index_max
         * @return index_max
        */
        int get_max() const
        {
            return index_max;
        }

        /**
         * print the vector
        */
        void print()
        {
            //std::cout << min << " -> " << max << " | " << index_min << " -> " << index_max << std::endl;
            for(int i = index_min; i < 0; i++)
            {
                std::cout << vec_neg[-i] << " ";
            }
            for(int i = 0; i <= index_max; i++)
            {
                std::cout << vec_pos[i] << " ";
            }
            std::cout << std::endl;
        }

};

#endif