#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct SongNode{
	char name[50];
	int duration;
	int songIndex;
	struct SongNode* prev;
	struct SongNode* next;
	
}SongNode;

typedef struct TopList{
	char name[50];
	int songIndex;
	int listenDuration;
	int listenTimes;
	struct TopList* next;
}TopList;


SongNode* createNode(char* name, int songIndex ,int duration);
void addNode(SongNode** head, SongNode* newNode);
int createPlaylists(SongNode** user, int n, int maxSongCount, int minSongCount, char songNames[][50], int songDurations[]);
void printPlaylist(SongNode* head);
void printToplist(TopList* head);
void addTopList(TopList** head, int songIndex, int duration, char name[]);
void simulateUser(int m, TopList** head, SongNode* userPlaylist);
void freePlaylist(SongNode** head);
void freeToplist(TopList** head);

int main(){
	srand(time(NULL));
	char songNames[100][50] = {
        "Bohemian Rhapsody", "Stairway to Heaven", "Hotel California", "Like a Rolling Stone", "Smells Like Teen Spirit", "Imagine", "One", "Billie Jean",
		"Hey Jude", "Sweet Child o' Mine", "Shape of You", "Blinding Lights", "Someone You Loved", "Uptown Funk", "Thinking Out Loud", "Rolling in the Deep", 
		"Havana", "Despacito", "Shallow", "Bad Guy", "November Rain", "Comfortably Numb", "Wish You Were Here", "Hallelujah", "Yesterday", "Enter Sandman", 
		"With or Without You", "Under the Bridge", "Lose Yourself", "Wonderwall", "Don't Stop Me Now", "Africa", "Take On Me", "Livin' on a Prayer", 
		"Every Breath You Take", "Don't Stop Believin'", "Mr. Brightside", "Seven Nation Army", "Creep", "Zombie", "Paint It Black", "Another Brick in the Wall", 
		"Born to Run", "Purple Haze", "Whole Lotta Love", "Sultans of Swing", "Back in Black", "Kashmir", "More Than a Feeling", "Come As You Are", "No Woman, No Cry", 
		"Let It Be", "Iron Man", "All Along the Watchtower", "Gimme Shelter", "Sympathy for the Devil", "Good Vibrations", "A Day in the Life", "My Generation", 
		"London Calling", "Highway to Hell", "Baba O'Riley", "You Shook Me All Night Long", "Message in a Bottle", "Roxanne", "Fortunate Son", "Satisfaction", 
		"Layla", "Superstition", "I Will Survive", "Dancing Queen", "Stayin' Alive", "Billie Eilish - lovely", "Watermelon Sugar", "Levitating", 
		"Juice WRLD - Lucid Dreams", "Post Malone - Sunflower", "Drake - God's Plan", "The Weeknd - Starboy", "Ed Sheeran - Perfect", 
		"Queen - Another One Bites the Dust", "Michael Jackson - Thriller", "AC/DC - Thunderstruck", "Nirvana - Heart-Shaped Box", "Guns N' Roses - Paradise City", 
        "Red Hot Chili Peppers - Californication", "Coldplay - Yellow", "Oasis - Champagne Supernova", "Radiohead - Karma Police", "Linkin Park - Numb", 
        "Eminem - Without Me", "Beyonce - Crazy in Love", "Rihanna - Umbrella", "Adele - Hello", "Taylor Swift - Blank Space",
        "Katy Perry - Firework", "Justin Bieber - Sorry", "Maroon 5 - Moves Like Jagger", "Pharrell Williams - Happy", "Journey - Any Way You Want It"
    };
    int songDurations[100] = {
        357, 482, 390, 369, 303, 216, 456, 259, 251, 355, 203, 202, 227, 238, 266, 248, 219, 289, 216, 198, 558, 405, 302, 359, 122, 263, 331, 273, 327, 296, 204, 293, 
        226, 244, 253, 241, 213, 233, 309, 301, 187, 261, 279, 177, 417, 368, 251, 495, 246, 268, 242, 236, 302, 374, 300, 358, 226, 328, 228, 276, 208, 301, 257, 196, 
        142, 235, 429, 242, 188, 242, 241, 200, 173, 206, 241, 224, 206, 240, 258, 212, 357, 231, 279, 411, 262, 248, 373, 265, 245, 284, 219, 222, 267, 232, 227, 214, 
        201, 233, 199, 250                               
    };
    
	int k, n, maxSongCount, minSongCount, songCount, randomSong, i, j;
    SongNode** users;
    TopList* topList = NULL;
    int* usersSongCount;

    printf("Please enter the number of users (K): ");
    scanf("%d", &k);
    printf("Please enter the total number of songs (N): ");
    scanf("%d", &n);
	
	users = (SongNode**) malloc(k*sizeof(SongNode*));
	usersSongCount = (int*)malloc(k*sizeof(int));
	maxSongCount = (n / k) + (k / 2);
	minSongCount = (n / (2*k)) + 1;

	for(i=0;i<k;i++){
		usersSongCount[i] = createPlaylists(&users[i], n, maxSongCount, minSongCount, songNames, songDurations);
		printf("User %d's Playlist\n", i+1);
		printPlaylist(users[i]);
		printf("\n");
	}
	
	for(i=0;i<k;i++){
		printf("\n\n--- Simulating User %d ---\n", i+1);
		simulateUser(usersSongCount[i], &topList, users[i]);
		printToplist(topList);
	}
	
	for(i=0;i<k;i++){
		freePlaylist(&users[i]);
	}
	free(users);
	freeToplist(&topList);
	free(usersSongCount);
	
	return 0;
}


SongNode* createNode(char* name, int songIndex ,int duration) {
    SongNode* newNode = (SongNode*)malloc(sizeof(SongNode));
    strcpy(newNode->name, name);
    newNode->duration = duration;
    newNode->songIndex = songIndex;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}


void addNode(SongNode** head, SongNode* newNode) {
    if (*head == NULL) {
        *head = newNode; 
        newNode->next = newNode; 
        newNode->prev = newNode; 
    } 
	else {
        SongNode* tail = (*head)->prev;
        tail->next = newNode; 
        newNode->prev = tail;   
        newNode->next = *head; 
        (*head)->prev = newNode; 
    }
}


int createPlaylists(SongNode** user, int n, int maxSongCount, int minSongCount, char songNames[][50], int songDurations[]) {
    int songCount;
    int randomSong;
    int i;
    SongNode* newNode;
	*user = NULL; 
    songCount = (rand() % (maxSongCount - minSongCount + 1)) + minSongCount;

    for(i=0;i<songCount;i++){
    	randomSong = rand() % n; 
		newNode = createNode(songNames[randomSong], randomSong ,songDurations[randomSong]);
		addNode(user, newNode);
    }
	return songCount;
}


void printPlaylist(SongNode* head) {
    SongNode* current = head;
    int counter = 1;
	int duration, minutes, seconds;
    do {
        duration = current->duration;
        minutes = duration / 60;
        seconds = duration % 60;
        printf("%d. %s | %d min %02d sec\n", counter, current->name, minutes, seconds);
        current = current->next;
        counter++;
    } while (current != head);
}


void printToplist(TopList* head){
	printf("\n\n-_ Top10 List _-\n==================\n\n");
	TopList* current = head;
    int counter = 1;
	int duration, minutes, seconds;
	while (current != NULL && counter <= 10){
		duration = current->listenDuration;
        minutes = duration / 60;
        seconds = duration % 60;
        printf("%d. %s | Duration: %d dk %02d sn | Listens: %d\n", counter, current->name, minutes, seconds, current->listenTimes);
        current = current->next;
        counter++;
	}
}


void addTopList(TopList** head, int songIndex, int duration, char name[]) {
    TopList* current = *head;
    TopList* prev = NULL;
    TopList* foundNode = NULL;

    while (current != NULL && foundNode == NULL) {
        if (current->songIndex == songIndex) {
            foundNode = current;
        }
        else{
        	prev = current;
        	current = current->next;
		}
        
    }

    if (foundNode != NULL) { 
        foundNode->listenDuration += duration;
        if (prev == NULL) *head = foundNode->next;
		else prev->next = foundNode->next;
		foundNode->next = NULL;
		foundNode->listenTimes++;
    }
	else { 
        foundNode = (TopList*) malloc(sizeof(TopList));
        foundNode->songIndex = songIndex;
        foundNode->listenDuration = duration;
        strcpy(foundNode->name, name);
        foundNode->next = NULL;
        foundNode->listenTimes = 1;
    }

    if (*head == NULL || (*head)->listenDuration <= foundNode->listenDuration) {
        foundNode->next = *head;
        *head = foundNode;
    } 
	else {
        current = *head;
        while (current->next != NULL && foundNode->listenDuration < current->next->listenDuration) {
            current = current->next;
        }
        foundNode->next = current->next;
        current->next = foundNode;
    }
}


void simulateUser(int m, TopList** head, SongNode* userPlaylist){
	int i, j;
	int songCount = (rand() % m) + 1;
	int jumpedSong;
	SongNode* current= userPlaylist;
	
	for(i=0;i<songCount;i++){
		jumpedSong = (rand() % (m + 1)) - (m/2);
		if(jumpedSong < 0) for(j=0;j<(-jumpedSong);j++) current = current->prev;
		else for(j=0;j<jumpedSong;j++) current = current->next;
		printf("\n[%d] User listens to: %s ", jumpedSong, current->name);
		addTopList(head, current->songIndex, current->duration, current->name);
	}	
}  


void freePlaylist(SongNode** head) {
    SongNode* current = *head;
    SongNode* next_node;
    
    if ((*head)->prev != NULL) (*head)->prev->next = NULL;
	else (*head)->next = NULL;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    *head = NULL;
}


void freeToplist(TopList** head){
	TopList* current = *head;
    TopList* next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    *head = NULL;
}
