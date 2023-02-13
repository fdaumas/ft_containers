#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>
#include "iterator.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector {
        public:
            typedef Alloc allocator_type;
            typedef typename Alloc::size_type size_type;
            typedef typename Alloc::value_type value_type;
            typedef typename Alloc::reference reference;
            typedef typename Alloc::const_reference const_reference;
            typedef typename ft::iterator<T*,vector> iterator;

        private:
            Alloc   _alloc;
            T*      _array;
            size_t  _capacity;
            size_t  _last;

            void    newAlloc(size_t size) 
            {
                T* tmp = _alloc.allocate(size);
                size_t index = 0;

                for(; index != _last; index++)
                    _alloc.construct(&tmp[index], _array[index]);
                for(; index != 0 ; index--)
                    _alloc.destroy(&_array[index]);
                _alloc.deallocate(_array, _capacity);
                _capacity = size;
                _array = tmp;
            }

            void    needCapacity()
            {
                if (_capacity == 0)
                    _capacity = 2;
            }

        public:
            explicit vector (const allocator_type& alloc = allocator_type()) :
                _alloc(alloc),
                _array(_alloc.allocate(0)),
                _capacity(0),
                _last(0)
            {}
            explicit vector (size_t n, const T& val = T(), const allocator_type& alloc = allocator_type()) :
                _alloc(alloc),
                _array(_alloc.allocate(n)),
                _capacity(n),
                _last(n)
            {
                for(size_t index ; index != n ; index++)
                    _alloc.construct(&_array[index], val);
            }
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

            vector (const vector& from) :
                _alloc(from._alloc),
                _array(from._array),
                _capacity(from._capacity),
                _last(from._last)
            {
                for(size_t index; index != _last; index++)
                    _alloc.construct(&_array[index], from._array[index]);
            }

            ~vector() 
            {
                for(size_t index = 0; index != _last ; ++index)
                    _alloc.destroy(&_array[index]);
                _alloc.deallocate(_array, _capacity);
            }

            iterator    begin()
            {
                return (iterator(_array));
            }

            iterator    end()
            {
                return (iterator(_array + _last));
            }

            void    push_back(const T& val)
            {
                if (_last == _capacity)
                {
                    needCapacity();
                    newAlloc(_capacity * 2);
                }
                _alloc.construct(&_array[_last], val);
                _last++;
            }

            void    pop_back()
            {
                _alloc.destroy(&_array[_last]);
                _last--;
            }

            size_t  size() const 
            {
                return _last;
            }

            size_t  capacity()
            {
                return _capacity;
            }

            size_t max_size() 
            {
                return _alloc.max_size();
            }

            void resize (size_t n, value_type val = value_type())
            {
                if (n < _last)
                {
                    for(size_t index = n; index != _last; ++index)
                        _alloc.destroy(&_array[index]);
                    _last = n;
                }
                else if (n > _last)
                {
                    needCapacity();
                    while(n > _capacity)
                        newAlloc(_capacity * 2);
                    for(size_t index = _last; index != n; ++index)
                        _alloc.construct(&_array[index], val);
                    _last = n;
                }
            }

            bool empty() const
            {
                return (_last == 0);
            }

            void    reserve(size_t n)
            {
                needCapacity();
                while(n > _capacity)
                    newAlloc(_capacity * 2);
            }

            void clear()
            {
                for(size_t index = 0; index != _last ; ++index)
                    _alloc.destroy(&_array[index]);
                _last = 0;
            }

            iterator insert(iterator position, const value_type& val)
            {
                needCapacity();
                if (_last == _capacity)
                    newAlloc(_capacity * 2);
                if (position == end())
                { 
                    push_back(val);
                    return (end() - 1);
                }
                else
                {
                    iterator    it = begin();
                    iterator    rightIt;
                    size_t      index = 0;
                    T           *tmp = _alloc.allocate(_capacity);
                    for(;it != position; it++, index++)
                        _alloc.construct(&tmp[index], _array[index]);
                    _alloc.construct(&tmp[index], val);
                    rightIt = iterator(&tmp[index]);
                    index++;
                    for(;it != end(); it++, index++)
                        _alloc.construct(&tmp[index], _array[index - 1]);
                    it = begin();
                    index = 0;
                    for(; it != end(); it++, index++)
                        _alloc.destroy(&_array[index]);
                    _alloc.deallocate(_array, _capacity);
                    _array = tmp;
                    _last++;
                    return rightIt;
                }
            }

            reference at(size_t npos)
            {
                if (npos >= _last)
                    throw (std::out_of_range("not in vector")); 
                return (_array[npos]);
            }

            const_reference at(size_t npos) const
            {
                if (npos >= _last)
                    throw (std::out_of_range("not in vector")); 
                return (_array[npos]);
            }

            T& operator[](unsigned int npos)
            {
                return (_array[npos]);
            }

            const T& operator[](unsigned int npos) const
            {
                return (_array[npos]);
            }
    };
}

#endif // !VECTOR_HPP
