template<typename T> 
VecZ<T>::VecZ() : vec_pos{1}, vec_neg{1}, min{0}, max{0}, index_min{0}, index_max{0}
{
}

template<typename T>
VecZ<T>::~VecZ()
{

}

template<typename T>
void VecZ<T>::insert(int i, T elt)
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
    } 
    else 
    {
        if(i < index_min) index_min = i;
        
        while(i <= min)
        {
            min = 2 * min - 1;
            vec_neg.resize(size_t(-min));
        }
        vec_neg[-i] = elt;
    }
}

template<typename T>
T & VecZ<T>::operator[](int i)
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

template<typename T>
int VecZ<T>::get_min() const
{
    return index_min;
}

template<typename T>
int VecZ<T>::get_max() const
{
    return index_max;
}

template<typename T>
void VecZ<T>::print()
{
    for(int i = index_min; i < 0; i++)
        std::cout << vec_neg[-i] << " ";

    for(int i = 0; i <= index_max; i++)
        std::cout << vec_pos[i] << " ";
        
    std::cout << std::endl;
}
