#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    char name[50]; 
    int age;
    int salary;
    struct Node* child;
    struct Node* sibling;
}Node;




Node* createNode(char* name, int age, int salary);
Node* findNode(Node* currentNode, char* name); 
void addChild(Node* parent, Node* newChild);
Node* createTree(char* filename, int* n, int* totalAge, int* totalSalary); 
void freeTree(Node* node);
void printTree(Node* node, int level);
int calculateLevel(Node* node);
void findLevelCounts(Node* node, int currentLevel, int* levelCounts);
void printLevelCounts(Node* root, int level);
void findMaxChildrenNode(Node* node, int targetLevel, int currentLevel, Node** maxNode, int* maxCount);

int main(){
	
	int totalAge, totalSalary, level, fileChoice, targetLevel, maxChildrenCount,n = 0;
	char* filename;
	
	printf("Girdi dosyasi secmek icin ilgili numaraya basiniz:\n");
	printf("1. personel.txt\n2. personel2.txt\n3. personel3.txt\nSeciminiz: ");
	scanf("%d", &fileChoice);
	if(fileChoice == 2) filename = "personel2.txt";
	else if(fileChoice == 2) filename = "personel3.txt";
	else filename = "personel.txt";
	
    Node* root = createTree(filename, &n, &totalAge, &totalSalary);
    Node* maxChildrenNode = NULL;
    maxChildrenCount = -1;
    
    printf("\nThe Tree:\n\n");
    printTree(root, 0);
	level = calculateLevel(root)+1;
	
    printf("\n--- Hesaplamalar ---\n\n");
    printf("- Ilgili sirketin personel agaci %d seviyeden olusmaktadir.\n", level);
    
    printLevelCounts(root, level);
    
    printf("Alt calisan sayisi en fazla olan kisiyi ogrenmek icin bir seviye giriniz: ");
    scanf("%d", &targetLevel);
    findMaxChildrenNode(root, targetLevel, 1, &maxChildrenNode, &maxChildrenCount);
	printf("- %d. seviyede en fazla alt calisana sahip olan kisi %d kisi ile %s'dir.\n", targetLevel, maxChildrenCount, maxChildrenNode->name);

    printf("- Tum calisanlarin yas ortalamasi: %.2f\n", (float)totalAge / n);
    
    printf("- Sirketin odedigi aylik personel maasi: %d\n", totalSalary);


    freeTree(root);
    root = NULL;
    printf("\n[i]-> Bellek temizlendi.\n");	
	
	
	
	
	
	return 0;
}



Node* createNode(char* name, int age, int salary) {

    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->age = age;
    newNode->salary = salary;
    newNode->child = NULL;
    newNode->sibling = NULL;

    return newNode;
}


Node* findNode(Node* currentNode, char* name) {
    if (currentNode == NULL) return NULL;
    if (strcmp(currentNode->name, name) == 0) return currentNode;

    Node* found = findNode(currentNode->child, name);
    if (found != NULL) return found;

    return findNode(currentNode->sibling, name);
}

void addChild(Node* parent, Node* newChild) {

    if (parent->child == NULL) parent->child = newChild;
    else {
        Node* currentSibling = parent->child;
        while (currentSibling->sibling != NULL) currentSibling = currentSibling->sibling;
        currentSibling->sibling = newChild;
    }
}


Node* createTree(char* filename, int* n, int* totalAge, int* totalSalary) {
    FILE* file = fopen(filename, "r");
    fscanf(file, "%d\n", n);
    
    Node* root = NULL;
    char name[50], parentName[50];
    int age, salary;
    int i = 1;
    
    fscanf(file, "%s %d %d %s\n", name, &age, &salary, parentName);
    *totalAge = age;
	*totalSalary = salary;
	root = createNode(name, age, salary);
	
	 
    while (i < *n){
		fscanf(file, "%s %d %d %s\n", name, &age, &salary, parentName);
		*totalAge += age;
		*totalSalary += salary;
		Node* newNode = createNode(name, age, salary);
	    Node* parentNode = findNode(root, parentName);
		addChild(parentNode, newNode);		
        i++;
    }
	
    fclose(file);

    return root;
}


void freeTree(Node* node) {
    if (node != NULL) {
		freeTree(node->child);
    	freeTree(node->sibling);
    	free(node);
	}
}


void printTree(Node* node, int level) {
    if (node != NULL) {
        int i;
        for (i = 0; i < level; i++) printf("\t");
        printf("[ %s | Age: %d | Salary: %d ]\n", node->name, node->age, node->salary);
    	printTree(node->child, level + 1);
        printTree(node->sibling, level);
        
    }
}




int calculateLevel(Node* node){
	
	if(node == NULL) return -1;
	
	Node* currentChild = node->child;
	int maxLevel = -1;
	int currentLevel;
	
	while(currentChild != NULL){
		currentLevel = calculateLevel(currentChild);
		if(currentLevel > maxLevel) maxLevel = currentLevel;
		currentChild = currentChild->sibling;	
	}
	
	return maxLevel + 1;
}


void findLevelCounts(Node* node, int currentLevel, int* levelCounts){
	if(node != NULL){
		levelCounts[currentLevel - 1]++;
		findLevelCounts(node->child, currentLevel+1, levelCounts);
		findLevelCounts(node->sibling, currentLevel, levelCounts);
	}
}


void printLevelCounts(Node* root, int level){

    int* levelCounts = (int*)calloc(level, sizeof(int));
	int i;
    findLevelCounts(root, 1, levelCounts);

    printf("- Her seviyedeki personel sayisi:\n");
    for(i=0; i<level ;i++) printf("   - Seviye %d: %d\n", i+1, levelCounts[i]);

    free(levelCounts);
}


void findMaxChildrenNode(Node* node, int targetLevel, int currentLevel, Node** maxNode, int* maxCount){
	if(node != NULL){
		if (currentLevel == targetLevel){
        	int currentCount = 0;
        	Node* currentNode = node->child;
        	while(currentNode != NULL){
        		currentCount++;
        		currentNode = currentNode->sibling;
			}
        
        	if (currentCount > *maxCount) {
        	    *maxCount = currentCount;
        	    *maxNode = node;
        	}
    	}
        findMaxChildrenNode(node->child, targetLevel, currentLevel+1, maxNode, maxCount);
    	findMaxChildrenNode(node->sibling, targetLevel, currentLevel, maxNode, maxCount);   
    }
}



