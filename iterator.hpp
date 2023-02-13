#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include <iterator>

namespace ft
{
    template<class Iter> 
        struct iterator_traits
        {
            typedef typename Iter::difference_type  difference_type ;
            typedef typename Iter::value_type       value_type ;
            typedef typename Iter::reference       reference ;
            typedef typename Iter::pointer       pointer ;
            typedef typename Iter::iterator_category       iterator_category ;
        };
    template<class T>
        struct iterator_traits<T*>
        {
            typedef typename std::ptrdiff_t difference_type ;
            typedef T value_type ;
            typedef T* pointer ;
            typedef T& reference ;
            typedef typename std::random_access_iterator_tag iterator_category ;
        };

    template<class T>
        struct iterator_traits<const T*>
        {
            typedef typename std::ptrdiff_t difference_type ;
            typedef T value_type ;
            typedef T* pointer ;
            typedef T& reference ;
            typedef typename std::random_access_iterator_tag iterator_category ;
        };
    template<class T, class Cont>
        class iterator
        {
            public:
                typedef typename iterator_traits<T>::difference_type difference_type ;
                typedef typename iterator_traits<T>::value_type value_type ;
                typedef typename iterator_traits<T>::pointer pointer ;
                typedef typename iterator_traits<T>::reference reference ;
                typedef typename std::random_access_iterator_tag iterator_category ;

            protected:
                pointer _pVal;

            public:
                iterator() {}
                ~iterator() {}
                iterator(const pointer pVal) : _pVal(pVal) {} 
                iterator(const iterator& from) : _pVal(from._pVal) {}
                template<typename Iter>
                iterator(const iterator<Iter, Cont>& from) : _pVal(&*from) {}

                iterator& operator=(const iterator& n)
                {
                    this->_pVal = n._pVal;
                    return (*this);
                }

                iterator operator+(difference_type n) const
                {
                    return (iterator(_pVal + n));
                }

                iterator& operator+=(difference_type n)
                {
                    _pVal += n;
                    return *this;
                }

                iterator operator-(difference_type n) const
                {
                    return (iterator(_pVal - n));
                }

                iterator& operator-=(difference_type n)
                {
                    _pVal -= n;
                    return *this;
                }

                iterator& operator++()
                {
                    _pVal++;
                    return (*this);
                }

                iterator operator++(int) 
                {
                    iterator tmp = *this;
                    ++(*this);
                    return (tmp);
                }

                iterator& operator--()
                {
                    _pVal--;
                    return (*this);
                }

                iterator operator--(int)
                {
                    iterator tmp = *this;
                    --(*this);
                    return (tmp);
                }

                reference operator*() const
                {
                    return *_pVal;
                }

                pointer operator&() const
                {
                    return _pVal;
                }

                reference operator[](const size_t n) const
                {
                    return (static_cast<reference>(_pVal[n]));
                } 

                template<class T2>
                friend bool operator==(const iterator<T,Cont>& lfs, const iterator<T2,Cont>& rhs) 
                {
                    return (lfs._pVal == rhs._pVal);
                }

                template<class T2>
                friend bool operator!=(const iterator<T,Cont>& lfs, const iterator<T2,Cont>& rhs) 
                {
                    return (lfs._pVal != rhs._pVal);
                }

                template<class T2>
                friend bool operator<=(const iterator<T,Cont>& lfs, const iterator<T2,Cont>& rhs) 
                {
                    return (lfs._pVal <= rhs._pVal);
                }

                template<class T2>
                friend bool operator>=(const iterator<T,Cont>& lfs, const iterator<T2,Cont>& rhs) 
                {
                    return (lfs._pVal >= rhs._pVal);
                }

                template<class T2>
                friend bool operator<(const iterator<T,Cont>& lfs, const iterator<T2,Cont>& rhs) 
                {
                    return (lfs._pVal < rhs._pVal);
                }

                template<class T2>
                friend bool operator>(const iterator<T,Cont>& lfs, const iterator<T2,Cont>& rhs) 
                {
                    return (lfs._pVal > rhs._pVal);
                }
                };
}

#endif // !ITERATOR_HPP
