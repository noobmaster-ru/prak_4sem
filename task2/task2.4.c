#include <stdio.h>

double str2double(char str[100]){
    double answer, v,k;
    int i,s,kol;
    answer = 0;
    i = 0;
    while (str[i] - '0' >= 0 &&  str[i] - '0' <= 9) {
        answer *= 10;
        answer += str[i] - '0';
        i += 1;
    }

    if (str[i] == '.') {
        i += 1;
        s = 0;
        while (str[i] - '0' >= 0 &&  str[i] - '0' <= 9 && str[i] != '\0') {
            s += 1;
            k = 1;
            kol = s;
            while (kol != 0){
                k /= 10;
                kol -= 1;
            }
            v = (str[i] - '0')*k;
            answer += v;
            i += 1;
        }
        

        if (str[i] == 'e' || str[i] == 'E'){  // exponental form
            i += 1;
            if (str[i] == '+'){
                s = 0;
                i += 1;
                while (str[i] - '0' >= 0 &&  str[i] - '0' <= 9){
                    s *= 10;
                    s += str[i] - '0';   // s - stepen of 10
                    i += 1; 
                }
                kol = 1;
                while (s != 0){
                    kol *= 10;
                    s -= 1;
                }
                return answer*kol;
            }
            else if (str[i] == '-'){
                s = 0;
                i += 1;
                while (str[i] - '0' >= 0 && str[i] - '0' <= 9){
                    s *= 10;
                    s += str[i] - '0';  // s - stepen of 10
                    i += 1;
                }
                k = 1;
                while (s != 0){
                    k /= 10;
                    s -= 1;
                }
                return answer*k;
            }
            else {
                s = 0;
                s += str[i] - '0'; 
                i += 1;
                while (str[i] - '0' >= 0  && str[i] - '0' <= 9){
                    s *= 10;
                    s += str[i] - '0';
                    i += 1;
                }
                kol = 1;
                while (s != 0){
                    kol *= 10;
                    s -= 1;
                }
                return answer*kol;
            }    
        }
        return answer;
    }
    else if (str[i] == 'e' || str[i] == 'E') {
        i += 1;
        if (str[i] == '+'){
            s = 0;
            i += 1;
            while (str[i] - '0' >= 0 &&  str[i] - '0' <= 9){
                s *= 10;
                s += str[i] - '0';   // s - stepen of 10
                i += 1; 
            }
            kol = 1;
            while (s != 0){
                kol *= 10;
                s -= 1;
            }
            return answer*kol;
        }
        else if (str[i] == '-'){
            s = 0;
            i += 1;
            while (str[i] - '0' >= 0 && str[i] - '0' <= 9 && str[i] != '\0'){
                s *= 10;
                s += str[i] - '0';  // s - stepen of 10
                i += 1;
            }
            k = 1;
            while (s != 0){
                k /= 10;
                s -= 1;
            }
            return answer*k;
        }
        else {
            s = 0;
            s += str[i] - '0'; 
            i += 1;
            while (str[i] - '0' >= 0  && str[i] - '0' <= 9 && str[i] != '\0'){
                s *= 10;
                s += str[i] - '0';
                i += 1;
            }
            kol = 1;
            while (s != 0){
                kol *= 10;
                s -= 1;
            }
            return answer*kol;
        }    
    }
    return answer;
}

int main(){
    char str[100];
    double ans;
    printf(" Enter numbers: ");
    while (scanf("%s",str) != EOF) {
        ans = str2double(str);
        printf(" Number: %.10g\n",ans);
    }
}