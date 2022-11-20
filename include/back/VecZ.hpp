#ifndef VECZ_HPP
#define VECZ_HPP

#include <iostream>
#include <vector>

template <class T>
class VecZ
{
    public:
        std::vector<T> vec_pos;
        std::vector<T> vec_neg;

        int min;
        int max;
        int index_min;
        int index_max;

        VecZ() : vec_pos{1}, vec_neg{1}, min{0}, max{0}, index_min{0}, index_max{0}
        {
        }

        ~VecZ() {}

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

        void print()
        {
            std::cout << min << " -> " << max << " | " << index_min << " -> " << index_max << std::endl;
            for(int i = index_min; i < 0; i++)
            {
                std::cout << vec_neg[-i] << " ";
            }
            std::cout << "| ";
            for(int i = 0; i <= index_max; i++)
            {
                std::cout << vec_pos[i] << " ";
            }
            std::cout << std::endl;
        }

};

#endif