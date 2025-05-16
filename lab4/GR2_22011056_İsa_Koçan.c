#include<stdio.h>
#include<stdlib.h>

//Lab4-Question1

//Disaridan iki farkli yigin'a girdi olarak basamak basamak okunan iki adet sayinin toplamini hesaplamak 
//icin ucuncu bir yigin kullanilmasi istenmektedir. Bahsi gecen islemleri yapan ve 
//3. YIGIN'da basamak basamak yer alan TOPLAM degerin ekrana sira ile basamak basamak 
//yazdirilmasini saglayan programin kodunu C dilinde yaziniz.

// Her Yýðýn ve Queue iþleminde kullandýðýnýz veri yapýsýnýn son halini kullanýcýya yazdýrýn.

//Not: Her iki sayinin disaridan en yuksek anlamli basamaktan en dusuk anlamli basamaga dogru okunmasi onerilmektedir. STACK fonksiyonlari hazir verilmektedir. Yeniden yazmayiniz.
//Girdi:  Sayi 1:  5 4 7 8 9
//        Sayi 2:  1 2 3

//Cikti:  5 4 9 1 2

// Form Linki: https://l24.im/eidgr9u
////////////////
//Write the code of the program that performs the operations mentioned above and prints the TOTAL value in the 3rd STACK to the screen in order, in C language.
//A third stack is required to calculate the sum of two numbers that are read as inputs to two different stacks.

// Print the final version of the data structure you used in each Stack and Queue operation to the user.

//Note: It is recommended that both numbers be read from the most significant digit to the least significant digit. STACK functions are provided as is. Do not rewrite.
//Input: Number 1: 5 4 7 8 9
// Number 2: 1 2 3

//Output: 5 4 9 1 2

// Form Link: https://l24.im/eidgr9u

typedef struct STACK{
	int *arr;
	int size;
	int currP;
}stack;


stack* createStack(int size){
	stack* newStack=(stack*)malloc(sizeof(stack));
	newStack->arr=(int*)malloc(size*sizeof(int));
	newStack->size=size;
	newStack->currP=0;
	return newStack;
}

void reSize(stack *Stack){
	printf("Resizing Stack from %d to %d\n",Stack->size,Stack->size*2);
	Stack->size*=2;
	Stack->arr=realloc(Stack->arr,Stack->size*sizeof(int));	
}


void push(stack* Stack,int newItem){
	Stack->arr[Stack->currP++]=newItem;
	if(Stack->currP==Stack->size)
		reSize(Stack);
}

int pop(stack* Stack){
	if(Stack->currP<=0)
		return NULL;
	return Stack->arr[--Stack->currP];
}


void printStack(stack* Stack){
	int i;
	printf("Current Stack: ");
	for(i=0;i<Stack->currP;i++)
		printf("%d ",Stack->arr[i]);
		
	printf("\n");
	
}

void freeStack(stack* Stack){
	free(Stack->arr);
	free(Stack);
}



int main(){
	
	int ilkSayi, ikinciSayi;
	printf("ilk sayi: ");
	scanf("%d", &ilkSayi);
	printf("ikinci sayi: ");
	scanf("%d", &ikinciSayi);
	
	stack *stack1, *stack2, *stack3;	
	int size1=0, size2=0, tmp, basamak1, basamak2, size3;
	
	tmp = ilkSayi;
	while(tmp != 0){
		size1++;
		tmp = tmp/10;
	}
	
	tmp = ikinciSayi;
	while(tmp != 0){
		size2++;
		tmp = tmp/10;
	}
	
	stack1 = createStack(size1);
	stack2 = createStack(size2);
	size3 = size1+size2;
	stack3 = createStack(size3);
	
	basamak1 = 1;
	while(size1 > 1){
		basamak1*=10;
		size1--;
	} 
	basamak2 = 1;
	while(basamak1 != 0){
		if(basamak1 != 1) tmp = ilkSayi/basamak1;
		if(basamak2 != 1) tmp = tmp%basamak2;
		basamak1 = basamak1/10;
		basamak2 = basamak2*10;
		push(stack1, tmp);
		printStack(stack1);
	}
	
	basamak1 = 1;
	while(size2 > 1){
		basamak1*=10;
		size2--;
	} 
	basamak2 = 1;
	while(basamak1 != 0){
		if(basamak1 != 1) tmp = ikinciSayi/basamak1;
		if(basamak2 != 1) tmp = tmp%basamak2;
		basamak1 = basamak1/10;
		basamak2 = basamak2*10;
		push(stack2, tmp);
		printStack(stack2);
	}
	
	
	
	while(stack2->currP>0 || stack2->currP>0){
		ilkSayi = pop(stack1);
		ikinciSayi = pop(stack2);
		tmp = ilkSayi + ikinciSayi;
		push(stack3, tmp);
		printStack(stack1);
		printStack(stack2);
		printStack(stack3);
	}
	if(stack1->currP>0){
		while(stack1->currP>0){
			tmp = pop(stack1);
			push(stack3, tmp);
			printStack(stack1);
			printStack(stack3);
		}
	}
	else{
		while(stack2->currP>0){
			tmp = pop(stack2);
			push(stack3, tmp);
			printStack(stack2);
			printStack(stack3);
		}
	}
	
	

	return 0;
}
