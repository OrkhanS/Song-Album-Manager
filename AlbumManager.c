#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct song{
    char* SongName;
    char* Genre;
    int Duration;
    struct song* next;
    struct song* prev;
};

struct SongAlbum{
    char* albumName;
    char* artistName;
    int prodYear;
    char* prodCompany;
    struct song* first_single;
	struct SongAlbum* next;
	struct SongAlbum* prev;    
};

struct PlayList{
    struct song* SongofThisInstance;
    struct PlayList* next;
    struct PlayList* prev;
};

struct PlayList_DLL {
	struct PlayList * head;
	struct PlayList_DLL * next;
	struct PlayList_DLL * prev;
};

struct song * searchsong(struct SongAlbum*,char *name);
void displayalbums(struct SongAlbum *Album);
struct SongAlbum* CreateAlbum(struct SongAlbum *Album);
void CreateSong(struct SongAlbum *Album);
struct PlayList_DLL * CreatePlaylist(struct PlayList_DLL * list, struct SongAlbum * album);
void DisplayAlbum(struct SongAlbum* Album);
struct SongAlbum * SearchAlbum(struct SongAlbum *Album, char *);
void ModifyAlbum(struct SongAlbum *Album);
void RemoveAlbum(struct SongAlbum *Album, char *);
void display_ps(struct PlayList_DLL* head );
void RemoveSong(struct SongAlbum* Album);
void ExportAlbum(struct SongAlbum *Album);

int main()
{
	struct SongAlbum* album=NULL;
	struct PlayList_DLL * head_playlist=NULL;
	char choice;
	char *name;
	do
	{
		fflush(stdin);
		printf("\n\n--------Welcome to Album Manager, Press\n\n--------(c)reate an album\n--------(s)earch an album\n--------(d)isplay an album\n--------(r)emove an album\n--------(m)odify an album\n--------(i)mport an album\n--------(u)export an album\n");
		printf("--------(p) to create a playlist\n--------(j) to display a playlist\n--------(w) to remove songs\n--------(e)xit\n");
		fflush(stdin);
		scanf(" %c",&choice);
		fflush(stdin);
		switch(choice)
		{
				
			case 'c':
				printf("\nLet's create an album\n");
				fflush(stdin);
				album = CreateAlbum(album);
				fflush(stdin);
				break;
				
			case 's':
				fflush(stdin);
				printf("\nEnter name of album to be searched: \n");
				scanf(" %s",name);
				SearchAlbum(album, name);
				fflush(stdin);
				break;
				
			case 'd':
				displayalbums(album);
				break;	
					
			case 'p':
				head_playlist= CreatePlaylist(head_playlist,album);
				break;
					
			case 'r':
				printf("\nLet's delete an album\n");
				fflush(stdin);
				printf("Enter the name of the album\n");
				scanf(" %s",name);
				RemoveAlbum(album, name);
				printf("\nSuccessfully deleted\n");
				fflush(stdin);
				break;
				
			case 'j':
				display_ps(head_playlist);
				break;
				
			case 'm':
				fflush(stdin);
				ModifyAlbum(album);		
				break;
				
			case 'w':
				RemoveSong(album);
				break;
				
			case 'u':
				ExportAlbum(album);
				break;
			
			case 'e':
				fflush(stdin);
				printf("\nYou exitted from program\n");
				fflush(stdin);
				break;
			default :
				fflush(stdin);
				printf("\nInvalid choice!\n");
				fflush(stdin);
				break;
		}
		fflush(stdin);
	}while(choice != 'e');	
}



struct PlayList_DLL* CreatePlaylist(struct PlayList_DLL *head,struct SongAlbum * head_a)   
{
	struct PlayList_DLL *tmp = (struct PlayList_DLL *) malloc(sizeof(struct PlayList_DLL));
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->head = (struct PlayList *)malloc(sizeof(struct PlayList));
	
		struct PlayList * this_playlist = tmp->head;
		printf("Enter the album in which the song is located\n");
		char album_name[50];
		scanf(" %s",album_name);
		struct SongAlbum * album_found;
		album_found = SearchAlbum(head_a, album_name);
	
	if(album_found == NULL)return NULL;
		printf("Enter the song to be added from the album %s\n",album_name);
		char song_name[50];
		scanf(" %s",song_name);
		struct song * song_found;
		song_found  = searchsong(album_found, song_name);
	
	if(song_found == NULL)return NULL;
		this_playlist->SongofThisInstance = song_found;
		this_playlist->prev = NULL;
		struct PlayList * temp = this_playlist;
		temp->next = NULL;
		
		printf("Would you like to add other songs to this playlist (Y) (N)\n");
		char choice;
		scanf(" %c", &choice);
	
	while(choice != 'N'){
			printf("Enter the album in which the song is located\n");
			scanf(" %s",album_name);
			album_found = SearchAlbum(head_a, album_name);
			
			if(album_found == NULL)return NULL;
				printf("Enter the song to be added from the album %s\n",album_name);
				scanf(" %s",song_name);
				song_found  = searchsong(album_found, song_name);
		
			if(song_found == NULL)return NULL;
				struct PlayList * temp2 = (struct PlayList* )malloc(sizeof(struct PlayList*));
				temp2->SongofThisInstance = song_found;
				temp2->prev = temp;
				temp2->next = NULL;
				temp->next = temp2;
				temp = temp2;
			
				printf("Would you like to add other songs to this playlist (Y) (N)\n");
				scanf(" %c",&choice);
	}

	if(head == NULL)return tmp;
	else
	{
		struct PlayList_DLL * tempo = head;
		while(tempo->next != NULL){
			tempo = tempo->next;
		}
		tmp->prev = tempo;
		tempo->next = tmp;
		return head;	
	}
	
}


struct song * searchsong(struct SongAlbum * album,char *name)
{
	struct song * tmp = album->first_single;
	
	while(tmp != NULL)
	{
		if(!strcmp(name,tmp->SongName))
		{
			printf("song found\n");
			return tmp;
		}
		tmp = tmp->next;
	}
	
	printf("song not found\n");
	return NULL;
	
}

struct SongAlbum * CreateAlbum(struct SongAlbum *head)
{

	struct SongAlbum * Album;
	Album = (struct SongAlbum*)malloc(sizeof(struct SongAlbum));
	 
	      		//Name
	char name[100];   // here I wrote array to get name of the album then, I calculated the length of it and allocate space for its length in struct name 
	int n,i;
	fflush(stdin);
	printf("\nEnter the name of album:  ");
	fflush(stdin);
	scanf(" %s",name);
	fflush(stdin);	
		n = strlen(name);      
		Album->albumName = (char *)malloc((sizeof(char)*n) + 1);
		strcpy(Album->albumName, name); 
		
		
					// Singername
	printf("\nEnter the singer name of album:"); 
	fflush(stdin);   // I did all of creation parts exactly like the first part.
	scanf(" %s",name);
	fflush(stdin);
	
		n = strlen(name);
		Album->artistName = (char *)malloc((sizeof(char)*n) + 1);
		strcpy(Album->artistName, name);
	

	           // Production Year
	printf("\nEnter production year:");
	
	fflush(stdin);
	scanf(" %d",&(Album->prodYear));
	fflush(stdin);
	
			  // Production Company	
	printf("\nEnter the production company of album:");
	fflush(stdin);
	scanf(" %s",name);
	fflush(stdin);
	
		n = strlen(name);
		Album->prodCompany = (char *)malloc((sizeof(char)*n) + 1);
		strcpy(Album->prodCompany, name);
		fflush(stdin);
		
	Album->first_single=NULL;

	CreateSong(Album);
	
	printf("\nDo you want to add more song, Press Y if yes, N if no: ");
	char choice;
	scanf("%c",&choice);
	while(choice !='N'){
		CreateSong(Album);
		printf("\nDo you want to add more song, Press Y if yes, N if no: ");
		scanf("%c",&choice);
	}
	
	if(head==NULL){
		Album->next=NULL;
		Album->prev=NULL;
		return Album;
		
	}
	else {
		struct SongAlbum * tmp=head;
		while(tmp->next!=NULL){
			tmp=tmp->next;
		}
		tmp->next=Album;
		Album->next=NULL;
		Album->prev=tmp;
		return head;
	}
}

void CreateSong(struct SongAlbum *Album)
{
	if(Album->first_single==NULL){
	
	Album->first_single = (struct song*)malloc(sizeof(struct song));
				// Song name 
	char name[100]; 
	int n,i;
	fflush(stdin);						
	printf("\nEnter the song name:");
	fflush(stdin);
	scanf(" %s",name);
	fflush(stdin);
	
		n = strlen(name);
		Album->first_single->SongName = (char *)malloc((sizeof(char) +1)*n);
		strcpy(Album->first_single->SongName, name);
		fflush(stdin);
		
		
			//Song duration
	printf("\nEnter song duration:");
	
	fflush(stdin);
	scanf(" %d",&Album->first_single->Duration);
	fflush(stdin);
	
	
			//Song genre
	printf("\nEnter the song genre:");
	fflush(stdin);
	scanf(" %s",name);                         
	fflush(stdin);
	
		n = strlen(name);
		Album->first_single->Genre = (char *)malloc((sizeof(char) +1)*n);
		strcpy(Album->first_single->Genre, name);
		fflush(stdin);
	Album->first_single->next = NULL;		//since it is our first song		
	Album->first_single->prev = NULL;
	
	}
	
	else 
	{
		struct song * temp = Album->first_single;
		struct song *temp_prev = NULL;
		while(temp->next != NULL)
		{
			temp = temp->next;
			
		}
		
			temp_prev = temp;
			temp->next = (struct song *) malloc(sizeof(struct song));
			temp=temp->next;
				// Song name 
	char name[100]; 
	int n,i;
	fflush(stdin);						
	printf("\nEnter the song name:");
	fflush(stdin);
	scanf(" %s",name);
	fflush(stdin);
	
		n = strlen(name);
		temp->SongName = (char *)malloc(sizeof(char)*n +1);
		strcpy(temp->SongName, name);
		fflush(stdin);
		
		
			//Song duration
	printf("\nEnter song duration:");
	
	fflush(stdin);
	scanf(" %d",&(temp->Duration));
	fflush(stdin);
	
	
			//Song genre
	printf("\nEnter the song genre:");
	fflush(stdin);
	scanf(" %s",name);                         
	fflush(stdin);
	
		n = strlen(name);
		temp->Genre = (char *)malloc(sizeof(char)*n +1);
		strcpy(temp->Genre, name);
		fflush(stdin);
	temp->next = NULL;				
	temp->prev = temp_prev;
		
	}
}

struct SongAlbum * SearchAlbum(struct SongAlbum *Album, char *name)
{
	struct SongAlbum * temp;
	temp = Album;
	while(temp != NULL)
	{
		if(!strcmp(name,temp->albumName))
		{
			printf("\nAlbum founded\n");
				return temp;
		}
	
		temp = temp->next;
	}
	printf("not found\n");
	return NULL;

}

void ModifyAlbum(struct SongAlbum *head)
{
	printf("Enter the name of album to be modified:\n");
	char name_album[50];
	scanf(" %s",name_album);
	struct SongAlbum *Album = SearchAlbum(head,name_album);
	if(Album!=NULL){
		
		char name[100]; 
			int n,i;
			fflush(stdin);
			printf("\nEnter the name of album:  ");
			fflush(stdin);
			scanf(" %s",name);
			fflush(stdin);	
				n = strlen(name);      
				Album->albumName = (char *)malloc((sizeof(char) +1)*n);
				strcpy(Album->albumName, name); 
				
				
							// Singername
			printf("\nEnter the singer name of album:"); 
			fflush(stdin);   // I did all of creation parts exactly like the first part.
			scanf(" %s",name);
			fflush(stdin);
			
				n = strlen(name);
				Album->artistName = (char *)malloc((sizeof(char) +1)*n);
				strcpy(Album->artistName, name);
			
		
			           // Production Year
			printf("\nEnter production year:");
			
			fflush(stdin);
			scanf(" %d",&Album->prodYear);
			fflush(stdin);
			
					  // Production Company	
			printf("\nEnter the production company of album:");
			fflush(stdin);
			scanf(" %s",name);
			fflush(stdin);
			
				n = strlen(name);
				Album->prodCompany = (char *)malloc((sizeof(char) +1)*n);
				strcpy(Album->prodCompany, name);
				fflush(stdin);	
		}

}


void RemoveAlbum(struct SongAlbum *Album, char *name)
{
	struct SongAlbum * temp = SearchAlbum(Album,name);
	struct SongAlbum * temp_p;
	struct SongAlbum * temp_n;
	if(temp != NULL) 
	{
		temp_p = temp->prev;
		temp_n = temp->next;
		
		if(temp_p != NULL)
		{
			temp_p->next = temp_n;
			
		}
		
		if(temp_n != NULL)
		{
			temp_n->prev = temp_p;
		}
			
		free(temp);
		printf("successfuly delete\n");
	}
}

void RemoveSong(struct SongAlbum *head)
{
	char *name;
	printf("\Enter name of Album:");
	scanf("%s",name);
	struct SongAlbum * temp = SearchAlbum(head,name);
	char *songname;
	scanf("%s",songname);
	struct song * temp2 = 	searchsong(temp, songname); 
	temp2->next->prev = temp2->prev;
	temp2->prev->next = temp2->next;
	free(temp2);
}

void ExportAlbum(struct SongAlbum *Album)
{
	struct song * temp;
	FILE* fp;
	fp = fopen("text.txt", "a+");
	   			//Exporting Album first
		fprintf(fp, "And this Album contains: ");

	fprintf(fp,"%s %s %d %s\n", Album->albumName, Album->artistName, Album->prodYear, Album->prodCompany);
	
	fprintf(fp, "And this Album contains: ");
	
				//Exporting Songs of this Album
	while(temp->next != NULL)
	{
		fprintf(fp, "%s %d %s\n", temp->SongName, temp->Duration, temp->Genre);
		temp = temp->next;		
	}
	
	
}


void DisplayAlbum(struct SongAlbum *Album)
{	
	printf("\nThe name is: ");
	printf("\n%s", Album->albumName);
	printf("\n%s", Album->artistName);
	printf("\n%s", Album->prodCompany);
	printf("\n%d", Album->prodYear);
	struct song * tmp = Album->first_single;
	
	while(tmp != NULL)
	{
			printf("\n%s", tmp->SongName);
			printf("\n%d", tmp->Duration);  
			printf("\n%s", tmp->Genre);    
			tmp = tmp->next;  
	} 
	printf("\n");
	return;
}

void displayalbums (struct SongAlbum * Album){
	
	if(Album == NULL)return;
	DisplayAlbum(Album);
	printf("\n\n");
	displayalbums(Album->next);
}


void display_ps(struct PlayList_DLL* p ){
	if(p == NULL)return;
	struct PlayList * tmp = p->head;
	while(tmp != NULL)
	{
		printf("%s\t", tmp->SongofThisInstance->SongName);
		tmp = tmp->next;
	}
	printf("\n\n\n");
	display_ps(p->next);	
};
