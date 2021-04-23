#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>





sp_tuples * load_tuples(char* input_file)
{
    FILE *f_ptr;
    f_ptr=fopen(*input_file,"r");
    if(f_ptr==NULL)return NULL;
    int row, col, store;
    fscanf(f_ptr, "%d %d", &row, &col);
    sp_tuples *tuples_ptr=(sp_tuples*)malloc(sizeof(sp_tuples)); 

    tuples_ptr->m=row;
    tuples_ptr->n=col;
    tuples_ptr->nz=0;
    tuples_ptr->tuples_head=NULL;
    
    int r,c;
    double v;
    fgetc(f_ptr);
    while(fscanf(f_ptr,"%d %d %lf",&r,&c,&v )!=EOF){
        set_tuples(tuples_ptr, r, c, v);
    }
   /* int i, j;

    tuples_ptr->tuples_head=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    sp_tuples_node *head= tuples_ptr->tuples_head;
    sp_tuples_node *temp=head;
    for(i=0;i<row;i++){
        fgetc(f_ptr); // removes newline character 
        for(j=0;j<col;j++){
           // store=fgetc(f_ptr);
           // if(store==0) continue;
            temp->col=j;
            temp->row=i;
            temp->value=fgetc(f_ptr);
            if(j==col-1 && i==row-1) {
                temp->next=NULL;
                continue;
            }
            temp->next=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
            temp=head->next;
        }
    }
    */
    fclose(f_ptr);
    return tuples_ptr;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node *node;
    node=mat_t->tuples_head;

    while(node!=NULL){
        if(node->col==col && node->row==row){
             return node->value;
        }
        else if(node->col!=col || node->row!=row){
             return 0;
        }
    }
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{

	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

	return NULL;// retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return NULL; //retmat;

}


	
void destroy_tuples(sp_tuples * mat_t){
	
    return;
}  






