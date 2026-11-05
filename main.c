#include <stdio.h>
#include <string.h>
// int main(){
//     // char *list[2] = {
//     //     "fsefsever",
//     //     "frsevsevre"
//     // };
//     // for (int i = 0; i < 2; i++){
//     //     printf("%s\n", list[i]);
//     // };
//     char *op = "esvrgf";
//     char op2[15] = "cesov,rek";
//     char iu[10] = "abc";
//     char *iu_2 = "abcngmyu";
//     char ol[10] = {'a', 'e', 'c'};
//     printf("%d\n", strlen(op));
//     // 字符串长度
//     strcat(iu, ol);
//     printf("%s\n", iu);
//     strcpy(iu, ol);
//     // 字符串替换
//     // printf("%s\n", iu);
//     int len = strcmp(iu, iu_2);
//     // 同样的返回0，不同样的返回！=0
//     printf("%d\n", len);
//     char str[20] = "ISDMFEILF";
//     strlwr(str);
//     // 转小写
//     printf("%s\n", str);
//     // 转大写
//     strupr(str);
//     printf("%s", str);
//     return 0;

// }
int main(){
    char str[100];
    scanf("%s", str);
    int len = 0, len_2 = 0;
    for (int i = 0; i < strlen(str); i++){
        char str_1 = str[i];
        if (str_1 >= 'a' && str_1 <= 'z' || str_1 >= 'A' && str_1 <= 'Z')
            len += 1;
        else if (str_1 >= '1' || str_1 <= '9')
            len_2 += 1;
    }
    printf("%d \n %d \n", len, len_2);
    return 0;
}