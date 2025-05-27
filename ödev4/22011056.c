#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int** readGraph(char* filename, int* size);
void printGraph(int** graph, int size);
void freeGraph(int** graph, int size);
int isNeighbor(int* node, int X);
int findBestNode(int** graph, int size, int* candidates, int candidateCount);
void askXisNeighbor(int* bestNode, int size, int** candidates, int* candidateCount, int X);



int main() {
	// Variable declarations.
	int choice, X, size, candidateCount, bestNode, questionCount = 1, i;
	int* candidates;
	char filename[100];
	int** graph;
	
	// Get graph choice from user.
    printf("Lutfen test etmek istediginiz grafi secin (1, 2, veya 3): ");
    scanf("%d", &choice);
	if(choice == 2) strcpy(filename, "G2_KMat.txt");
	else if(choice == 3) strcpy(filename, "G3_KMat.txt");
	else strcpy(filename, "G1_KMat.txt");
	
	// Read graph from file and print.
    graph = readGraph(filename, &size);
    printGraph(graph, size);
    
    // Get target prize node from user, with input validation.
    printf("\nHangi dugum hedef olsun: ");
    scanf("%d", &X);
    while(X >= size || X < 0){
    	printf("\nLutfen %d - %d araliginda bir deger giriniz!\nHangi dugum hedef olsun: ", 0, size-1);
    	scanf("%d", &X);
	}
    
    // Initialize candidates array: initially all nodes are candidates.
    candidates = (int*)malloc(size*sizeof(int));
    //All of them a candidate at the beginning
    for(i=0;i<size;i++) candidates[i] = 1; 
    //So that candidateCount's value is about size
    candidateCount = size; 
    
    // Main loop to find the prize node.
    // Continues until only one candidate remains or max questions reached.
    while(candidateCount != 1 && questionCount <= size){
    	// Find the best node to ask about.
    	bestNode = findBestNode(graph, size, candidates, candidateCount);
    	printf("\n\nSoru %d: [%d] %d'ye komsu mu?", questionCount, bestNode, X);
    	// Ask the question. // Update candidates based on the answer.
		askXisNeighbor(graph[bestNode], size, &candidates, &candidateCount, X);
    	printf("\nAdaylar: ");
    	for(i=0;i<size;i++){
    		if(candidates[i] != 0) printf("%d ", i);
		} 
    	questionCount++;
	}
    
    // After the loop, check if the prize node was found.
    if(questionCount > size){
    	printf("\n\nHedef dugum bulunamadi! Potensiyel Adaylar: ");
    	for(i=0;i<size;i++){
    		if(candidates[i] != 0) printf("%d ", i);
		}
	}
	else{
    	i=0;
		while(candidates[i] != 1) i++; 
    	printf("\n\nHedef dugum bulundu: %d", i);
				
	}
    
    // Free allocated memory for the graph.
    freeGraph(graph, size);
    free(candidates);
    
    return 0;
}




/*
@brief Reads a graph from a file and represents it as an adjacency matrix.
@param filename The name of the file containing the graph data.
@param size Pointer to an integer to store the size (number of nodes) of the graph.
@return A 2D integer array representing the adjacency matrix, or NULL on failure.
*/
int** readGraph(char* filename, int* size){
    FILE* file = fopen(filename, "r");
    if (!file) { // Check if file opening failed.
        printf("Hata: '%s' dosyasi acilamadi.\n", filename);
        return NULL;
    }
    
	*size = 0; // Initialize graph size.
	int** graph;
    int i, j, value;
    
    //Determine the size (number of lines/nodes) of the graph.
    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), file) != NULL) (*size)++;
    
    // Allocate memory for the adjacency matrix.
    graph = (int**)malloc(*size*sizeof(int*));
	for(i=0;i<*size;i++) graph[i] = (int*)malloc(*size*sizeof(int));

    rewind(file); // Reset file pointer to the beginning.
	//Read the adjacency matrix values.   
    for(i=0;i<*size;i++){
    	for(j=0;j<*size;j++){
    		fscanf(file, "%d ", &value);
    		graph[i][j] = value;
		}
	}
    
    // Close the file and Return the populated adjacency matrix.
    fclose(file);
    return graph;
}


/*
@brief Prints the adjacency matrix of the graph.
@param graph The 2D integer array representing the adjacency matrix.
@param size The size (number of nodes) of the graph.
@return Void.
*/
void printGraph(int** graph, int size) {
    printf("\nGrafin Komsuluk Matrisi:\n");
    int i, j;
    // Iterate through rows.
    for (i = 0; i < size; i++) {
    	for(j=0;j<size;j++){ // Iterate through columns in the current row.
    		printf("%d ", graph[i][j]); // Print matrix element.
		}
		printf("\n"); // Newline after each row.
    }
}


/*
@brief Frees the dynamically allocated memory for the graph's adjacency matrix.
@param graph The 2D integer array representing the adjacency matrix.
@param size The size (number of nodes) of the graph.
@return Void.
*/
void freeGraph(int** graph, int size) {
	int i;
    for (i=0;i<size;i++) {
		free(graph[i]); // Free memory for the i-th row.
    }
    free(graph); // Free the array of row pointers.
    printf("\n\n[i]-> Bellek temizlendi!");
}


/*
@brief Checks if a target node X is a neighbor of a given node's adjacency list/row.
@param node An integer array representing the adjacency list/row of a node.
@param X The index of the target node to check for neighborhood.
@return 1 if X is a neighbor, 0 otherwise.
*/
int isNeighbor(int* node, int X) {
    if(node[X] == 1) return 1; // X is a neighbor.
    else return 0; // X is not a neighbor.
}


/*
@brief Finds the best node to ask about next to minimize the worst-case number of remaining candidates.
@param graph The adjacency matrix of the graph.
@param size The size of the graph.
@param candidates An array indicating current potential prize candidates (1 if candidate, 0 if not).
@param candidateCount The current number of candidates.
@return The index of the best node to ask about.
*/
int findBestNode(int** graph, int size, int* candidates, int candidateCount) {

	int potentialCount, yesCount, noCount, bestCount = size, bestNode = 0;
	int i, j;
	
	// Iterate through all nodes in the graph to evaluate them as potential questions.
    for(i=0;i<size;i++){
    	// Calculate candidates if 'i' IS a neighbor of the prize (answer "Yes")
   		yesCount = 0;
		for(j=0;j<size;j++){
			// finds the number of candidates for 
			//the intersection of node i's neighbors and the candidates set. 
			if(graph[i][j] == 1 & candidates[j] == 1) yesCount++;
		}
    	
		// Calculate candidates if 'i' IS NOT a neighbor of the prize (answer "No")	
   		//Finds the number of candidates after 
		//removing node i's neighbors from the candidates set.
		noCount = candidateCount - yesCount;

		// The worst-case scenario: Takes larger candidateCount
		if(yesCount < noCount) potentialCount = noCount;
		else potentialCount = yesCount;
	
		// If node 'i' results in a smaller candidate count, update bestNode
		if(potentialCount < bestCount){
			bestCount = potentialCount;
			bestNode = i;
		}
	}
   	
	// Return the index of the node that minimizes the remaining candidates.	
    return bestNode; 
}



/*
@brief Simulates asking if a chosen node is a neighbor of the prize node and updates the list of candidates accordingly.
@param bestNode The adjacency list/row of the node chosen for the question.
@param size The size of the graph.
@param candidates Pointer to the array of candidates (will be modified).
@param candidateCount Pointer to the current number of candidates (will be modified).
@param X The index of the actual prize node.
@return Void.
*/
void askXisNeighbor(int* bestNode, int size, int** candidates, int* candidateCount, int X){
	// Determine the actual answer to "Is bestNode a neighbor of X?"
	int answer = isNeighbor(bestNode, X);
	int* tmpCandidates = *candidates;
	int tmpCandidateCount = *candidateCount;
	int i;
	
	if(answer == 1){ //(Answer: "Yes")    
		printf("\nCevap: Evet");	
    	tmpCandidateCount = 0;
    	// Only neighbors of bestNode can be the prize. Eliminate non-neighbors.
		// candidates = candidates (intersection with) Neighborhoods(bestNode) 
		for(i=0;i<size;i++){
			if(bestNode[i] == 1 & tmpCandidates[i] == 1) tmpCandidateCount++;
			else tmpCandidates[i] = 0;
		}	
	}
	else{ //(Answer: "No")    
		printf("\nCevap: Hayir");
		// Neighbors of bestNode CANNOT be the prize. Eliminate them.
		// candidates = candidates - Neighborhoods(bestNode) 
		for(i=0;i<size;i++){
			if(bestNode[i] == 1 & tmpCandidates[i] == 1){
				tmpCandidates[i] = 0;
				tmpCandidateCount--;
			}
		}	
	}	
	
	// Update the caller's candidateCount and candidates array.
	*candidates = tmpCandidates;
	*candidateCount = tmpCandidateCount;
}


