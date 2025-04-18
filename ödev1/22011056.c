#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int* array, int left, int right, int pivotIndex){
	int i;
	for(i=left;i<=right;i++){
		if(pivotIndex >= 0 && i == pivotIndex) printf("[%d]", array[i]);
		else printf(" %d ", array[i]);
	}
}

void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int* keys, int* locks, int left, int right) {
    
    int keyIndex = (rand() % (right - left + 1)) + left;
    int i, j, lockIndex;
    lockIndex=left;
    while(locks[i] != keys[keyIndex]) i++;
    printf("\nAnahtarlar:");
	printArray(keys, left, right, keyIndex);
	printf("\nKilitler:  ");
	printArray(locks, left, right, i);
    printf("\n\nAnahtar %d'e gore kilitler duzenleniyor..\n", keys[keyIndex]);
	
	//lock dizisini seçilen key'e göre düzenleme
	i = left, j = right;
    while (i < j) {
    	while (i <= right && locks[i] < keys[keyIndex]) i++;
    	while (j >= left && locks[j] > keys[keyIndex]) j--;
        swap(&locks[i], &locks[j]);
    }
    swap(&locks[i], &locks[j]);
    i=left;
	while(locks[i] != keys[keyIndex]) i++;
	swap(&locks[i], &locks[j]);
	lockIndex = j;
	
	printf("\nAnahtarlar:");
	printArray(keys, left, right, keyIndex);
	printf("\nKilitler:  ");
	printArray(locks, left, right, lockIndex);
    printf("\n\nkilit %d'e gore anahtarlar duzenleniyor..\n", locks[lockIndex]);
	
	//keys dizisini pivot lock'a göre düzenleme
	i = left, j = right;
    while (i < j) {
        while (i <= right && keys[i] < locks[lockIndex]) i++;
        while (j >= left && keys[j] > locks[lockIndex]) j--;
        swap(&keys[i], &keys[j]);
    }
    swap(&keys[i], &keys[j]);
    i=left;
	while(keys[i] != locks[lockIndex]) i++;
	swap(&keys[i], &keys[j]);
    
    printf("\nAnahtarlar:");
	printArray(keys, left, right, j);
	printf("\nKilitler:  ");
	printArray(locks, left, right, j);
    return j;
}

void findKeyAndLock(int* keys, int* locks, int left, int right, int iter){
	if(left < right){
		printf("\n\n%d. adim\n--------------------\n", ++iter);
		int pivotIndex = partition(keys, locks, left, right);
		findKeyAndLock(keys, locks, left, pivotIndex-1, iter);
		findKeyAndLock(keys, locks, pivotIndex+1, right, iter);
	}
}


int main(){
	
	// Dosyadan veri çekme
	int size, i, j;
	char fileName[20];
	printf("Txt dosyasinin ismini giriniz: ");
	scanf("%s", fileName);
	FILE *file = fopen(fileName, "r");
	if(file == NULL){
		printf("Dosya acma hatasi!");
		return 1;
	}
	
	fscanf(file, "%d", &size);
	int *keys = (int*)malloc(size*sizeof(int));
	int *locks = (int*)malloc(size*sizeof(int));
	
	printf("\nAnahtarlar:");
	for(i=0;i<size;i++){
		fscanf(file, " %d", &keys[i]);
		printf(" %d ", keys[i]);
	}
	printf("\n");
	
	printf("\nKilitler:  ");
	for(i=0;i<size;i++){
		fscanf(file, " %d", &locks[i]);
		printf(" %d ", locks[i]);
	}
	fclose(file);
	srand(time(NULL));
	findKeyAndLock(keys, locks, 0, size-1, 0);
	printf("\n\n[i]-> Butun anahtarlar ve kilitler eslestirildi!\n\nAnahtarlar:");
	printArray(keys, 0, size-1, -1);
	printf("\n\nKilitler:  ");
	printArray(locks, 0, size-1, -1);
	free(keys);
	free(locks);

	return 0;
}
