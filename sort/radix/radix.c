#include "radix.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_LEN 1000

node_t *create_bucket()
{
    node_t *dummy = (node_t *)malloc(sizeof(node_t));
    node_t *tmp = dummy;
    int loop = 10, i = 0;
    while (loop--) {
        node_t *node = (node_t *)malloc(sizeof(node_t));
        node->value = (value_t *)malloc(sizeof(value_t));
        tmp->next = node;
        tmp = node;
        node->value->numi = 0;
        node->value->bucket_num = i;
        i++;
        for (int j = 0; j < NUM_LEN; j++) {
            node->value->num[j] = 0;
        }
    }
    tmp->next = NULL;
    return dummy;
}

void read_clear_bucket(int a[], node_t *h)
{
    int j = 0;                                      
    node_t *tmp = h->next;                                  
    while (tmp != NULL) {                           
        for (int i = 0; i < tmp->value->numi; i++) {
            a[j++] = tmp->value->num[i];            
            tmp->value->num[i] = 0;
        }                                           
        tmp->value->numi = 0;                       
        tmp = tmp->next;                            
    }                                               
}

int *radix_sort(int a[], int len)
{
    node_t *h = create_bucket(); 
    int li = 0;
    node_t *tmp = h->next;
    /*int loop = 3;
    while (loop--) {
        for (int i = 0; i < len; i++) {                     
            tmp = h->next;                           
            if (a[i] >= 0 && a[i] < 10) {            
                if (loop == 3) {
                    li = a[i];                           
                } else if (loop == 2) {
                    li = 0;
                } else if (loop == 1) {
                    li = 0;
                }
            } else if (a[i] >= 10 && a[i] < 100) {   
                if (loop == 3) {
                    li = a[i]%10;                        
                } else if (loop == 2) {
                    li = a[i]/10;
                } else if (loop == 1) {
                    li = 0;
                }
            } else if (a[i] >= 100 && a[i] < 1000) { 
                if (loop == 3) {
                    li = a[i]%10;                        
                } else if (loop == 2) {

                } else if (loop == 1) {
                    li = a[i]/100;
                }
            }                                        
            while (li != tmp->value->bucket_num) {   
                tmp = tmp->next;                     
            }                                        
            tmp->value->num[tmp->value->numi] = a[i];
            tmp->value->numi++;                      
        }                                            
        read_clear_bucket(a, h);                     
    }*/
    for (int i = 0; i < len; i++) {
        tmp = h->next;
        if (a[i] >= 0 && a[i] < 10) {
            li = a[i];
        } else if (a[i] >= 10 && a[i] < 100) {
            li = a[i]%10;
        } else if (a[i] >= 100 && a[i] < 1000) {
            li = a[i]%10;
        }
        while (li != tmp->value->bucket_num) {
            tmp = tmp->next;
        }
        tmp->value->num[tmp->value->numi] = a[i];
        tmp->value->numi++;
    }
    read_clear_bucket(a, h);
//---------------------------------------------------------------------------------------
    for (int i = 0; i < len; i++) {              
        tmp = h->next;                           
        if (a[i] >= 0 && a[i] < 10) {            
            li = 0;                           
        } else if (a[i] >= 10 && a[i] < 100) {   
            li = a[i]/10;                        
        } else if (a[i] >= 100 && a[i] < 1000) { 
            li = a[i]%100/10;                        
        }                                        
        while (li != tmp->value->bucket_num) {   
            tmp = tmp->next;                     
        }                                        
        tmp->value->num[tmp->value->numi] = a[i];
        tmp->value->numi++;                      
    }                                            
    read_clear_bucket(a, h);                     
//--------------------------------------------------------------------------------------
    for (int i = 0; i < len; i++) {              
        tmp = h->next;                           
        if (a[i] >= 0 && a[i] < 10) {            
            li = 0;                              
        } else if (a[i] >= 10 && a[i] < 100) {   
            li = 0;                        
        } else if (a[i] >= 100 && a[i] < 1000) { 
            li = a[i]/100;                    
        }                                        
        while (li != tmp->value->bucket_num) {   
            tmp = tmp->next;                     
        }                                        
        tmp->value->num[tmp->value->numi] = a[i];
        tmp->value->numi++;                      
    }                                            
    read_clear_bucket(a, h);                    
    return a;
}                                               
