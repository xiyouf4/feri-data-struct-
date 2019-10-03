#include "box.h"

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "client.h"
#include "proto.h"
#include "log.h"

void process_resp_status(proto_head_t *resp)
{
    pthread_mutex_t mmm = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mmm);
    response_status_t *response = (response_status_t *)resp;
    printf("%s\n", response->message);
    pthread_mutex_unlock(&mmm);
}

void process_resp_fri_list(proto_head_t *resp)
{
    pthread_mutex_t mmm = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mmm);
    response_friens_list_t *response = (response_friens_list_t *)resp;
    size_t i;                                                                                            
    for (i = 0; i < 100; i++) {
        if (response->userlist[i] == '*') {
            printf("\n");
        } else {
          printf("%c", response->userlist[i]);
        }
    }
    pthread_mutex_unlock(&mmm);
}

void process_resp_group_list(proto_head_t *resp)
{
    pthread_mutex_t mmm = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mmm);                       
    response_group_list_t *response = (response_group_list_t *)resp;
    size_t i;                               
    for (i = 0; i < 100; i++) {                                                                            
        if (response->userlist[i] == '*') {     
            printf("\n");                   
        } else {                            
            printf("%c", response->userlist[i]);
        }                                   
    }

    pthread_mutex_unlock(&mmm);
}

void process_resp_pravmess(proto_head_t *resp)
{
    pthread_mutex_t mmm = PTHREAD_MUTEX_INITIALIZER;                
    pthread_mutex_lock(&mmm);                                       
    response_pravmessage_t *response = (response_pravmessage_t *)resp;
    printf("\t%s:%s\n", response->username, response->message);
    pthread_mutex_unlock(&mmm);
}

void process_resp_groupmessage(proto_head_t *resp)
{
    pthread_mutex_t mmm = PTHREAD_MUTEX_INITIALIZER;                
    pthread_mutex_lock(&mmm);                                       
    response_groupmessage_t *response = (response_groupmessage_t *)resp;
    printf("%s:\t", response->username);                                                                   
    printf("%s\n", response->message);                                                                     
    pthread_mutex_unlock(&mmm);
}

void process_user_response(proto_head_t *resp)
{
    switch (resp->type) {
    case 2001:
        process_resp_status(resp);
        break;
    case 2002:
        process_resp_fri_list(resp);
        break;
    case 2003:                      
        process_resp_pravmess(resp);
        break;                      
    case 2004:                      
        process_resp_groupmessage(resp);
        break;                      
    case 2009:
        process_resp_group_list(resp);
        break;
    }
}

void *box_pthread_start(void *value)
{
    char buffer[1024];
    client_t *client = (client_t *)value;
    int nrecv;
    while (1) {
    nrecv = recv(client->conn_fd, buffer, sizeof(proto_head_t), 0);              
    if (nrecv < 0) {                                                             
        printf("recv has some problems\n");                                      
        close(client->conn_fd);                                                  
        return NULL;                                                             
    }                                                                            
    proto_head_t *resp = (proto_head_t *)buffer;                                 
    if (resp->magic != FERI_PROTO_HEAD) {                                        
        log_warn("wrong proto head, close it\n");                                
        close(client->conn_fd);                                                  
        return NULL;                                                             
    }                                                                            
    int want_read_len = resp->length - sizeof(proto_head_t);                     
    nrecv = recv(client->conn_fd, buffer+sizeof(proto_head_t), want_read_len, 0);
    if (nrecv < 0) {                                                             
        log_warn("recv has some problems, close it\n");                          
        close(client->conn_fd);                                                  
        return NULL;                                                             
    }                                                                            
    process_user_response(resp);                                         
    }
    return NULL;
}

void create_box_pthread(client_t *client)
{
    pthread_t thid;
    pthread_create(&thid, NULL, box_pthread_start, (void *)client);
}

