

#include "List_Vektor.hpp"

#include <iostream>

using namespace std;

template< class T >
List_Vektor< T >::List_Vektor() {
    this->array_dimension_ = 10;
    this->create();
}
// constructor
template< class T >
List_Vektor< T >::List_Vektor(int dim){
    this->array_dimension_ = dim;
    this->create();
}


template< class T >
List_Vektor< T >::List_Vektor(const List_Vektor<T>& Lista) {
    this->array_dimension_ = Lista.array_dimension_;
    this->length_ = Lista.length_;
    this->elements_ = new T[array_dimension_];
    for (int i=0; i<Lista.array_dimension_; i++)
        this->elements_[i] = Lista.elements_[i];
}

// destructor
template< class T >
List_Vektor< T >::~List_Vektor(){
    delete elements_;
}
// operations
template< class T >
void List_Vektor< T >::create(){
    this->elements_ = new T[array_dimension_];
    this->length_ = 0;
    srand(time(0));
}
template< class T >
bool List_Vektor< T >::empty() const {
    return(length_ == 0);
}

template< class T >
typename List_Vektor< T >::position List_Vektor< T >::begin() const {
    return 1;
}

template< class T >
typename List_Vektor< T >::position List_Vektor< T >::next(position p) const {
    if ( (0 < p) && (p < length_+1))
        return(p+1);
    else
        return(p);
}

template< class T >
typename List_Vektor< T >::position List_Vektor< T >::previous(position p) const {
    if ( (1 < p) && (p < length_+1)) return(p-1);
    else
        return(p);
}

template< class T >
bool List_Vektor< T >::end(position p) const {
    if ( (0 < p) && (p <= length_+1)) return( p == length_+1);
    else
        return(false);
}

template< class T >
typename List_Vektor< T >::value_type List_Vektor< T >::read(position p) const {
    if ( (0 < p) && (p < length_+1))
        return(elements_[p-1]);
    else
        return 0;
}

template< class T >
void List_Vektor< T >::write(const value_type &a, position p) {
    if ( (0 < p) && (p < length_+1))
        this->elements_[p-1] = a;
}

template< class T >
void List_Vektor< T >::insert(const value_type &a, position p){
    if (length_ == array_dimension_){
        change_dimension_(elements_, array_dimension_, array_dimension_ * 2);
        array_dimension_ = array_dimension_ * 2; }
    if ( (0 < p) && (p <= length_+1)) {
        for (int i=length_; i>=p; i--)
            elements_[i] = elements_[i-1];
        elements_[p-1]=a;
        length_=length_ + 1;
    }
}

template< class T >
void List_Vektor< T >::erase(position p){
    if ( (0 < p) && ( p < length_ + 1))
        if (!empty()) {
            for (int i=p-1;i<(length_-1);i++)
                elements_[i]=elements_[i+1];
            length_= length_ -1;
        }
}

template<class T>
void List_Vektor<T >::change_dimension_(T*& a, int dimensionVjeter, int dimensionRi){
    T* temp = new T[dimensionRi];
    int number;
    if (dimensionVjeter < dimensionRi)
        number = dimensionVjeter;
    else
        number = dimensionRi;
    for (int i=0; i<number; i++)
        temp[i]=a[i];
    delete [] a;
    a = temp;
}

/* assignment operator */
template<class T>
List_Vektor<T>& List_Vektor<T>::operator=(const List_Vektor<T>& l){
    if (this != &l){ // kujdes qe te eleminojme rastion l = l
        this->array_dimension_ = l.array_dimension_;
        this->length_ = l.length_;
        delete this->elements_;
        this->elements_ = new T[array_dimension_];
        for (int i=0; i<l.array_dimension_; i++)
            this->elements_[i] = l.elements_[i];
    }
    return *this;
}


template<class T>
bool List_Vektor<T>::operator==(const List_Vektor<T> &l) const{
    if (l.length_ != this->length_)
        return false;
    for (int i=0; i<this->array_dimension_; i++)
        if (this->elements_[i] != l.elements_[i])
            return false;
    return true;
}

template< class T >
void List_Vektor< T >::print(){
    int p;
    p = this->begin();
    cout << "[";
    while (!this->end(p)){
        if (p != this->begin())
            cout << ", " << this->read(p);
        else
            cout << this->read(p);
        p = this->next(p);
    }
    cout << "]" << endl;
}


template <typename T>
List_Vektor<T> List_Vektor<T>::bashko(List_Vektor<T> v1){
    List_Vektor<T> bashkimi(this->array_dimension_+v1.array_dimension_);
    bashkimi.length_ = this->length_ + v1.length_;
    
    position f1 = this->begin();
    position f2 = v1.begin();
    position f3 = bashkimi.begin();
    
    while(!this->end(f1) || !v1.end(f2)){
        if(this->read(f1)>v1.read(f2)){
            bashkimi.write(this->read(f1), f3);
            f1 = this->next(f1);
            f3 = bashkimi.next(f3);
        }else if(this->read(f1)<v1.read(f2)){
            bashkimi.write(v1.read(f2), f3);
            f2 = v1.next(f2);
            f3 = bashkimi.next(f3);
        }else{
            bashkimi.write(this->read(f1), f3);
            f3 = bashkimi.next(f3);
            bashkimi.write(v1.read(f2), f3);
            f3 = bashkimi.next(f3);
            f1 = this->next(f1);
            f2 = v1.next(f2);
        }
    }
    
    while(!this->end(f1)){
        bashkimi.write(this->read(f1), f3);
        f3 = bashkimi.next(f3);
        f1 = this->next(f1);
    }
    
    while(!v1.end(f2)){
        bashkimi.write(v1.read(f2), f3);
        f3 = bashkimi.next(f3);
        f2 = v1.next(f2);
    }
    
    
    
    return bashkimi;
}

template <typename T>
void List_Vektor<T>::operator=(List_Vektor<T> && l){
    this->array_dimension_ = l.array_dimension_;
    this->length_ = l.length_;
    this->elements_ = new T[array_dimension_];
    
    for(position i = this->begin(); !this->end(i); i = this->next(i)){
        this->write(l.read(i), i);
    }
    
    
}

template <typename T>
void List_Vektor<T>::printA(){
    for(int i = 0; i < this->array_dimension_; i++){
        std::cout << i << " : " << this->elements_[i] << std::endl;
    }
}

template <typename T>
int List_Vektor<T>::ordered(){
    int rrites=0, zb=0;
    
    for(int i = 1; i <= this->length_; i++){
        if(this->elements_[i-1] < this->elements_[i]){
            zb = -1;
        }
        
        if(this->elements_[i-1] > this->elements_[i]){
            rrites = -1;
        }
    }
    
    if(rrites == 0 && zb == 0){
        return 1; //constant
    }else if(rrites == 0)
        return 2; // ascending order
    else if(zb == 0)
        return 3; //descending order
    else
        return 0; //not ordered
}

#include <cstdlib>
#include <ctime>

template <typename T>
void List_Vektor<T>::gen_rand(int N){
    /*
    value_type n;
    
    srand(time(0));
    
    for(int i = 1; i<=N; i++){
        n = rand()%10;
        cout << n << " ";
        insert(n, i);
    }*/
    
    
    //this->elements_ = new T[array_dimension_];
    this->length_ = N;
    
    for(int i = 0; i < N; i++){
        int n = rand()%10;
        this->elements_[i] = n;
        cout << " " << n;
    }
    cout << ";";
}





template class List_Vektor<int>;
template class List_Vektor<float>;

























