#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//WRITTEN BY FAKHRI JAFAROV

typedef struct song {
    char* name;
    float duration;
} song;


typedef struct dynamic_array {
    
    int capacity;
    int size;
    void** elements;
    } dynamic_array;


void init_array(dynamic_array* array) {

    array->size=0;
    array->capacity = 2;

    array->elements =  malloc(2* sizeof(void*));;
    array->elements[0] = NULL;  //MAKING FIRST AND SECOND ELEMENTS EQUAL TO NULL
    array->elements[1] = NULL;

}

void put_element(dynamic_array* array, void* element) {

    //RESIZING HERE -> CREATING NEW DOUBLED CAPACITY ARRAY AND POINTING OLD ONE TO THE NEW ONE
    if(array->size==array->capacity){

        dynamic_array* arr;
        
        arr->size=array->size;

        arr->capacity=array->capacity*2;

        arr->elements = malloc(2 * array->capacity * sizeof(void*));

        for(int i=0;i<array->capacity;i++){

            arr->elements[i] = array->elements[i];
        }
        
        int dif = arr->capacity-array->capacity;

        for(int i=dif;i<arr->capacity;i++){
            arr->elements[i] = NULL;
        }
        free(array->elements);
        *array = *arr;

    }
    array->size+=1;

    //ADDING NEW ELEMENT TO VOID* ARRAY
    for(int i=0;i<(array->capacity);i++){

        if(array->elements[i] == NULL){

            (array->elements)[i] = element;

            break;
        }   
    }
}

void remove_element(dynamic_array* array, int position) {

    int p = position;

    if(array->size==array->capacity/2){  //CHECKING ARRAY SIZE AND RESIZING, ALLOCATING NEW MEMORY
        
        dynamic_array* arr;
        
        arr->size=array->size;

        arr->capacity=array->capacity/2;

        arr->elements = malloc((array->capacity/2) * sizeof(void*));

        for(int i=0;i<arr->capacity;i++){

            arr->elements[i] = array->elements[i];
        }
        free(array->elements);

        *array = *arr;
        
    }
    array->size-=1;

    array->elements[position]=NULL;

    for(int i=0;i<array->size-p;i++){
        if(array->elements[position+1]!=NULL){
            array->elements[position] = array->elements[position+1];
            array->elements[position+1] = NULL;
            position+=1;
        }
    }
}


void* get_element(dynamic_array* array, int position) {
    return array->elements[position];
}


int main() {

    struct dynamic_array arr;
    init_array(&arr);

    int input_val;

    while(1){

        printf("\nPlease Select one of them : \n");
        printf("\n1. Add a song: ");
        printf("\n2. Delete a song: ");
        printf("\n3. List all the songs: ");
        printf("\n4. Exit: \n");
        
        scanf("%d",&input_val);
        fgetc(stdin);

        if(input_val==1){
            
            //ALLOCATING MEMORY FOR CHAR AND SONG 
            char* name = (char*) malloc(64*sizeof(char*));
            float duration;
            struct song* song1 = (song*) malloc(sizeof(struct song));
            
            printf("\nEnter Name of the song: ");

            fgets(name, 64, stdin);         //TAKING INPUT WITH FGETS()
            name[strlen(name)-1] = 0;

            printf("Enter duration of the song : ");

            scanf("%f", &duration);

            song1->duration = duration;
            song1->name = name;

            put_element(&arr,song1);

        }

        else if(input_val==2){  

            char* name = (char*) malloc(64*sizeof(char*));
            printf("\nEnter Name of the song you want to delete: "); //I TAKE INPUT WITH FGETS(), IT CRASH THE PROGRAM WHEN IT'S TAKEN WITH SCANF()

            fgets(name, 64, stdin);
            name[strlen(name)-1] = 0;

            for(int i=0;i<(arr.size);i++){

                //CHECKING IF INPUTTED STRING EXISTS IN OUR ARRAY
                int num = strcmp((*(struct song*)arr.elements[i]).name,name);

                if(num==0){
                    song* pr = (song*)get_element(&arr,i); //GETTING VOID* ELEMENT, CASTING IT INTO SONG* AND FREEING MEMEORY
                    free(pr);
                    pr = NULL;
                    remove_element(&arr, i); //REMOVING ELEMENT FROM VOID**
                    break;
                }
            }
        }
        else if(input_val==3){  

            printf("\nHere are the all the songs that you have added\n");
            for(int i=0;i<arr.size;i++){

                void* song = get_element(&arr,i);
                printf("\nName : %s",(*(struct song*)song).name);  //PRINTING NAME AND DURATION OF THE SONGS IN FOR LOOP
                printf("\nDuration : %f\n",(*(struct song*)song).duration);
            }
        }
        else{
            if(arr.size!=0){
                for(int i=0;i<(arr.size);i++){
                    song* pr = (song*)get_element(&arr,i); //GETTING VOID* ELEMENT, CASTING IT INTO SONG* AND FREEING MEMORY
                    free(pr);
                    pr = NULL;
                }
            }
        exit(0);
        }
    }
}
