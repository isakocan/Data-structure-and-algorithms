#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Disaridan verilen 2 adet N basamakli sayi ayri ayri linkli listelerde saklanmaktadir.  
// Sayilari birbirinden cikarip sonucu tek bir degiskende saklayip ekrana yazdiran programin C kodu asagida eksik verilmistir.

// Doldurulmasi gereken fonksiyonlar:
// -push: Verilen degeri linkli listenin basina ekler.
// -subtractLinkedLists: Iki linkli listedeki sayilari kucuk basamaktan baslayarak birbirinden cikarir.
// Eger bir basamakta eksilen cikan sayiya yetmezse bir sonraki basamaktan 10'luk borc alinir (borrow).
// Sonuc, basamak basamak hesaplanip bir tam sayi (int) olarak dondurulur.

// Sayilar dizilerde (digits1, digits2) duz sirayla verilmistir (buyuk basamaktan kucuk basamaga).

//Girdi:  N:5
//Liste 1:   8->7->1->0->9->NULL (90178'i temsil eder, kucuk basamak basta)
//Liste 2:   6->5->1->2->6->NULL (62156'i temsil eder)

//Cikti:
//Sonuc: 28022

/////////////////////////////////////////////////////////////////////////////

//.c uzantili lab dosyanizi grupno_ogrenciNo_isim_soyisim.c seklinde isimlendiriniz.

//Ornek: GR1_25011000_Isim_Soyisim.c

//Lab sonunda hocalar izin verdiginde interneti acip asagidaki form linkine .c uzantili kodunuzu yukleyiniz.

//https://l24.im/fThRV

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	return node;
}

void push(Node** headRef, int data) {
    //Linked list push
    Node* node = createNode(data);
    node->next = *headRef;
    *headRef = node;    
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int subtractLinkedLists(Node* l1, Node* l2) {
    
    //linked list cikarma
    int result = 0, digit = 1;
    while(l1 != NULL){
    	if(l1->data < l2->data){
    		l1->next->data -= 1;
    		result += (l1->data + 10 - l2->data)*digit;
    		digit *= 10;
		}
		else{
			result += (l1->data - l2->data)*digit;
			digit *= 10;
		}
		l1 = l1->next;
		l2 = l2->next;
	}
	return result; //return'u nasýl unuttum amk
}

// Test
int main() {
    int N = 5;
    
    //digits1 > digits2
    int digits1[] = {9,0,1,7,8};
    int digits2[] = {6,2,1,5,6};
    int i;
    
    Node* number1 = NULL;
    Node* number2 = NULL;
    
    for (i = 0; i < N; i++) {
        push(&number1, digits1[i]);
        push(&number2, digits2[i]);
    }
    
    int fark = subtractLinkedLists(number1, number2);
    printf("Sonuc: %d\n", fark);
    
    freeList(number1);
    freeList(number2);

    return 0;
}
