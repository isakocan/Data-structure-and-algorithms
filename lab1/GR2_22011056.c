#include <stdio.h>


int main(){
	
	int n,m, i, j, k;
	printf("Matris boyutlarini giriniz. satir: ");
	scanf("%d", &n);
	printf("sutun: ");
	scanf("%d", &m);
	int matrix[n][m];
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("Matris [%d],[%d]: ", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}
	int elemanSayisi[n];
	int elemanlar[n*m];
	for(i=0;i<(n*m);i++){
		elemanlar[i] = 0;
	}
	i=0,j=0, k=0;
	while(i<n && matrix[i][j] != 0){
		elemanSayisi[i] = 0;
		while(j<m && matrix[i][j] != 0){
			elemanlar[k] = matrix[i][j];
			elemanSayisi[i]++; 
			j++;
			k++;
		}
		j = 0;
		i++;
	}
	printf("\n Satirlarin eleman sayisi: ");
	i=0;
	while(elemanSayisi[i] > 0){
		printf("%d ", elemanSayisi[i]);
		i++;
	}
	
	printf("\n Matrix'in elemanlari: ");
	i=0;
	while(elemanlar[i] > 0){
		printf("%d ", elemanlar[i]);
		i++;
	}
	
	
	return 0;
}
