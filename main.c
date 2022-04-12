#include <stdio.h>
#include <stdlib.h>
/* Define structures and global variables*/
int n; // max. number of processes
struct node1 {
    int process_id;
    struct node1* link;
};

typedef struct node1 list_type;

struct node2 {
    int parent;
    list_type *children;
}*pcb_array = NULL;

typedef struct node2 pcb_type;


/***************************************************************/
void printHierarchy() {
    /* declare local vars */
    list_type* current_child;
    
    /* for each PCB index i from 0 up to (but not including) maximum 
    number*/
    printf("\nProcess hierarchy: \n");
    for (int i = 0; i < n; i++){
        /* check if PCB[i] has a parent and children */
        if ( (pcb_array[i].parent != -1) && (pcb_array[i].children != NULL) ) { 
            
            /* intilize variable to head of list of children */
            current_child = pcb_array[i].children;
            /* while the end of the linked list of children is not reached */ 
            while (current_child != NULL) {
                /* print message about current child process index */
                printf("Process %i is the parent of Process %d\n" , i, current_child->process_id);
                /* move to next node in linked list */
                current_child = current_child->link;
            } /* while */
        }/* if */
    } /* for */
} /* end of procedure */
/***************************************************************/
void option1() {
/* declare local vars */
    
/* prompt for maximum number of processes */
    printf("Enter maximum number of processes: ");
    scanf("%d" , &n);
/* allocate memory for dynamic array of PCBs */
    pcb_array = (pcb_type*)malloc(n * sizeof(pcb_type));
/* Define PCB[0] */
    pcb_array[0].parent = 0;
    pcb_array[0].children = NULL;
/* for-loop to intitialize all other indices' parent to -1 */
    for (int i=1; i<n; i++ ){
        pcb_array[i].parent = -1;
        pcb_array[i].children = NULL;
    }
    printf("Process 0 was created as the top-level process \n");
return;
} /* end of procedure */
/***************************************************************/
void option2() {
    /* define local vars */
    int q = 1;
    int p;
    list_type* child_process;
    list_type* current_node;
    
    /* prompt for parent process index p */
    printf("Enter the parent process id: ");
    scanf("%d" , &p);
    
    /* search for first available index q without a parent in a while 
    loop */
    while ( (q < n) && (pcb_array[q].parent != -1) ){
        q++;
    }
    
    if (q==n){
        printf("Out of processes!\n");
        return;
    }
    
    /* allocate memory for new child process, initilize fields */
    child_process = (list_type*)malloc(sizeof(list_type));
    child_process -> process_id = q;
    child_process -> link = NULL;
    /* record the parent's index p in PCB[q] */
    pcb_array[q].parent = p;
    
    /* initialize the list of children of PCB[q] as empty */ //already done
    
    /* create a new link containing the child's index q and append the 
    link to the end of the linked list of PCB[p] */
    if (pcb_array[p].children == NULL){
        pcb_array[p].children = child_process;
    }
    else {  
        current_node = pcb_array[p].children;
        while(current_node->link != NULL) {
            current_node = current_node->link;
        }
        current_node->link = child_process;
    }
    
    printf("Process %i was created as a child of Process %d\n" , child_process->process_id, p);
    
    /* call procedure to print current hierachy of processes */
    printHierarchy();
    
    return;
} /* end of procedure */

/***************************************************************/

void deleteChildren(list_type* node) {
    /* declare local vars */
    int q;

    /* check if end of linked list--if so return */ //check returning case
    if (node == NULL){
        return;
    }
    
    else {
        /* else call self on next node in linked list */
        deleteChildren(node -> link);
        
        
        /* set variable q to current node's process index field */
        q = node ->process_id;
        
        /* call self on children of PCB[q] */ 
        deleteChildren(pcb_array[q].children);
        
        /* free memory of paramter */
        printf("Process %d was destroyed\n" , q);
        free(node);
        
        /* reset parent of PCB[q] to -1 */
        pcb_array[q].parent = -1;
        
        /* set paramter to NULL */
        node = NULL;
        
    } /* end of else */
        
    return;
} /* end of procedure */
/***************************************************************/
void option3() {
    /* declare local vars */
    int p;
    
    /* prompt for process index p */
    printf("Enter the parent process id: ");
    scanf("%d" , &p);
    
    /* call recursive procedure to destroy children of PCB[p] */
    deleteChildren(pcb_array[p].children); //recusirve call
    
    /* reset children of PCB[p] to NULL */
    pcb_array[p].children = NULL;

    /* call procedure to print current hierarchy of processes */
    printHierarchy();
    
    return;
} /* end of procedure */

/***************************************************************/

void option4() {
    /* check if PCB is non null)*/
    if (pcb_array == NULL){
        
    }
    else {
        /* call recursive procedure to destroy 
        children of PCB[0] */
        deleteChildren(pcb_array[0].children);
            
        free(pcb_array);
    } // else 
    return;
} /* end of procedure */

/***************************************************************/

int main() {
    /* declare local vars */
    int choice = 0;
    /* while user has not chosen to quit */
    while (choice != 4) {
        /* print menu of options */
        printf("\nProcess creation and destruction \n--------------------------------\n1) Enter parameters \n2) Create a new child process \n3) Destroy all descendants of a process \n4) Quit program and free memory  \n");
        /* prompt for menu selection */
        printf("\nEnter selection: ");
        scanf("%d" , &choice);
        
        /* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */
        if (choice == 1){
            option1();
        }
        else if (choice == 2){
            option2();
        }
        else if (choice == 3){
            option3();
        }
        else if (choice == 4 ){
            option4();
        }
        else {
            printf("Invalid Option\n");
        }
        
        
} /* while loop */
 return 1; /* indicates success */
} /* end of procedure */







