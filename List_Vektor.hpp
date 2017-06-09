

#ifndef List_Vektor_hpp
#define List_Vektor_hpp

#include <stdio.h>

#include <iostream>
using namespace std;
template< class T >
class List_Vektor {
    
public:
    typedef T value_type;
    
    typedef  int position;
    
    
    List_Vektor();
    List_Vektor(int);
    List_Vektor(const List_Vektor<T>& );
    ~List_Vektor();
    
    // operations
    void create();
    bool empty() const;
    value_type read(position) const;
    void write(const value_type &, position);
    position begin() const;
    bool end(position) const;
    position next(position) const;
    position previous(position) const;
    void insert(const value_type &, position);
    void erase(position);
    void print();
    
    // operator overriding
    List_Vektor<T>& operator=(const List_Vektor<T>&);
    bool operator==(const List_Vektor<T> &) const;
    
    List_Vektor<T> bashko(List_Vektor v1);
    void operator=(List_Vektor<T> &&);
    
    
    //To fill the list with random numbers
    void gen_rand(int);
    int ordered();
    
    
    void printA();
private:
    void change_dimension_(T*& , int , int );
    value_type* elements_;
    int length_; 
    int array_dimension_;
};


#endif /* List_Vektor_hpp */





















