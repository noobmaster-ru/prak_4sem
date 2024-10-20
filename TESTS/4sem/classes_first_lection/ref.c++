#include <iostream>

void swap(int &x ,int &y){
    int t = x;
    x = y;
    y = t;
}
int main(){
    int i = 5;
    int & reference_to_i = i;   //ссылка обязательно должна 
				                // быть инициализирована
				                // reference_to_i – синоним имени i ;    
				                // &i  ≡ &referenc_to_i; 
    i = reference_to_i + 1;
    reference_to_i = i + 1;
    std::cout << reference_to_i << ' '<< i << '\n';


    int a = 5, b =6;
    swap(a,b);
    std::cout << a << ' '<< b << '\n';
    return 0;
}