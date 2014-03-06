/*
    KAI AUSTIN
    BACON.C - Mimiking the oracle of bacon to match give actors
    via their movies
*/

#include <stdio.h>
#include <stdlib.h>
#include "mongo.h"

//Linked list of actors
struct ActorListActor {
  struct Actor* value; //Pointer to current actor comprising this node
  struct ActorListActor* next;  //Pointer to the next actor in the list
};

struct ActorList {
  struct ActorListActor* head;  //Points to the head of the Linked list of actors
};

struct MovieListMovie {
  struct Movie* value;  //Pointer to current movie comprising this node
  struct MovieListMovie* next;  //Point to next movie in the list
};

struct MovieList {
  struct MovieListMovie* head;  //Pointer to the head node of the movie list
};

//Actors and their list of movies played in
struct Actor {
  char name;   //Pointer to the name of the actor
  struct MovieList* movies; //Pointer to the Movie list head (also a pointer)
};

//Movies and the list of actors who played in them
struct Movie {
  char name;   //Pointer to movie's name
  struct ActorList* actors;   //Pointer to the Actor list head (also a pointer)
};


/*
 *     FUNCTIONS FOR BUILDING LINKED LISTS AND STUFF
 */

//Make a new actor
struct Actor* newActor(char name){
  struct Actor* actor = malloc(sizeof(struct Actor));
  actor->name = name;
  actor->movies = NULL;

  return actor;
}

//Make a new movie
struct Movie* newMovie(char name){
  struct Movie* movie = malloc(sizeof(struct Movie));
  movie->name = name;
  movie->actors = NULL;

  return movie;
}

//Make a new actor in a list
struct ActorListActor* newALA(struct Actor* actor){
  struct ActorListActor* actorNode = malloc(sizeof(struct ActorListActor));
  actorNode->value = actor;
  actorNode->next = NULL;

  return actorNode;
}

//Make a new movie in a list
struct MovieListMovie* newMLM(struct Movie* movie){
  struct MovieListMovie* movieNode = malloc(sizeof(struct MovieListMovie));
  movieNode->value = movie;
  movieNode->next = NULL;

  return movieNode;
}

//For adding movies to the actor's list of movies
void addMovieToMovieList(struct MovieList* mList, struct Movie* movie){
  //Adds to the FRONT of the linked list (because I say so)
  struct MovieListMovie* movieNode = newMLM(movie);
  movieNode->next = mList->head;
  mList->head = movieNode;
}

//For adding an actor to the movie's list of actors
void addActorToActorList(struct ActorList* aList, struct Actor* actor){
  //Adds to the FRONT of the linked list (still)
  struct ActorListActor* actorNode = newALA(actor);
  actorNode->next = aList->head;
  aList->head = actorNode;
}

/*
 *  MAIN FUNCTIONS FOR PATH FINDING PROGRAM
 *  Basic logic:
 *  Start with an actor
 *  Get all the movies they play in
 *  Get all the actors in those movies
 *    One by one, check if each actor matches the desired pair
 *    If they do, search is done, free all space, return path
 *    If NOT, then continue search and adding actors
 *  If no match found in above, then move to next level
 *  Repeat the process for each actor in the movie connections
 *
 */

//Nodes for the path (string stored only)
 struct PathNode {
    char movieName; //Name of the movie in the path
    char actorName; //Name of the actor in the path
 };
 //Path from the actor to the specified actor
 struct Path {
   int size;  //How long the path is
   struct PathNode* array;  //Array of path nodes
 };

//Print out the path of the actor connections
 void printPath(char *aName, struct Path* path){
    int plen;
    //Start by printing the main actor
    printf("%s \n", aName);
    //Print out the main path to the desired actor
    for (plen=0; plen < path->size; plen++){
      printf("--> %d (in %d) \n", path->array[plen].actorName, path->array[plen].movieName);
    }
 }

int main(){
  char actor1[80];
  char actor2[80];
  struct Path* path = malloc(sizeof(struct Path));
  struct Actor* lead = malloc(sizeof(struct Actor));

  //Get two actors typed in
  printf("Enter Actor 1: ");
  fgets(actor1, 80, stdin);
  printf("Enter Actor 2: ");
  fgets(actor2, 80, stdin);

  //Get stuff from database here
  mongo conn[1];
  int status = mongo_client( conn, "127.0.0.1", 27017 );

  //Check connection
  if( status != MONGO_OK ) {
      switch ( conn->err ) {
        case MONGO_CONN_NO_SOCKET:  printf( "no socket\n" ); return 1;
        case MONGO_CONN_FAIL:       printf( "connection failed\n" ); return 1;
        case MONGO_CONN_NOT_MASTER: printf( "not master\n" ); return 1;
      }
  }



  //Print out the path
  printPath(actor1, path);

  //Free things
  free(path);
  free(lead);

  mongo_destroy( conn );

  return 0;
}

