#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#define isSymbol(str) (str == '^' || str == '*' || str == '-' || str == '=')
#define isAlphabet(str) ((str >= 'A' && str <= 'Z') || (str >= 'a' && str <= 'z'))
#define isSpecSymbol(str1,str2) (str1 == '-' && str2 == '>')
#define isEqualSymbol(str1,str2,str3) (str1 == '<' && str2 == '-' && str3 == '>')

static _inline int mythReplace(char* str, int len,int left, int right){
	str[left] = 'p';
	memcpy(str + left + 1, str + right + 1, len - right + 1);
	return len - right + left + 1;
}

static _inline int isAtom(char* str, int left, int right){
	switch (right - left - 1){
	case 5:
		return isAlphabet(str[left + 1]) && isEqualSymbol(str[left + 2], str[left + 3], str[left + 4]) && isAlphabet(str[right - 1]);	//p<->q 
	case 4:
		return isAlphabet(str[left + 1]) && isSpecSymbol(str[left + 2],str[left + 3]) && isAlphabet(str[right - 1]);//p->q
	case 3:
		return isAlphabet(str[left + 1]) && isSymbol(str[left + 2]) && isAlphabet(str[right - 1]);//p^q
	case 2:
		return str[left + 1] == '!' && isAlphabet(str[right - 1]);//!p
	default:
		return 0;
	}
}

int isLogic(char* str,int len){
	int  i = 0, tmpright = -1, tmpleft = -1;
	char* p = str;
	if (*(p+1) == 0 && isAlphabet(*p))
		return 1;
	do{
		if(*p == '('){
			tmpleft = i;
		}else if(*p == ')'){
			tmpright = i;
			break;
		}
		i++;
	}while(*p++ != 0);
	if(tmpleft == -1 || tmpright == -1 || tmpright < tmpleft){
		puts("Illegal Count:No more '(' or ')'");
		return 0;
	}
	if (!isAtom(str, tmpleft, tmpright)){
		printf("Error in:%s,where left:%d and right:%d\n",str,tmpleft,tmpright);
		return 0;
	}
	else{
		i = mythReplace(str, len,tmpleft, tmpright);
		return isLogic(str,i);
	}
}

int main(int argc, char**argv){
	char str[256];
	for (;;){
		memset(str, 0, 256);
		printf(">"); gets(str);
		if (strcmp(str,"quit") == 0)
			break;
		if (isLogic(str,strlen(str)))
			printf("True,Is a Logic Expression\n");
		else
			printf("False,Not a Logic Expression\n");
	}
	return 0;
}
