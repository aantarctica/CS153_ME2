#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct rsa_struct rsa;
typedef struct cmd_struct cmd;
typedef struct cmdq_struct cmdq;


void parseInput(rsa* RSA);
void initRSA(rsa* RSA);
void printRSA(rsa* RSA);

cmdq* initQ();
void enqueue(cmdq* queue);
cmd* dequeue(cmdq* queue);

struct rsa_struct{
    int P;
    int Q;
    int E;
    int qsize;
    cmdq* queue;
};

struct cmd_struct{
    char   command[8];
    int     value;
    cmd*    next;
};  

struct cmdq_struct{
    cmd*    head;
    cmd*    tail;
};


int main(){
    rsa* RSA = (rsa*) malloc(sizeof(rsa));

    parseInput(RSA);
    printRSA(RSA);

    return 0;
}

void parseInput(rsa* RSA){
    scanf("%d %d", &RSA->P, &RSA->Q);
    scanf("%d", &RSA->E);
    scanf("%d", &RSA->qsize);

    for(int i = 0; i < RSA->qsize; i++){
        enqueue(RSA->queue);
    }
}

void initRSA(rsa* RSA){
    RSA->queue = initQ();
}

void printRSA(rsa* RSA){
    printf("P:\t%d\nQ:\t%d\nE:\t%d\nqueue size:\t%d\nqueue ptr:\t%p\n", 
    RSA->P, 
    RSA->Q, 
    RSA->E,
    RSA->qsize, 
    RSA->queue);
}

cmdq* initQ(){
    cmdq* temp = (cmdq*) malloc(sizeof(cmdq));
    temp->head = NULL;
    temp->tail = NULL;
    return temp;
}

void enqueue(cmdq* queue){
    // create new command pointer
    // ncmd and copy values of cmd to it
    cmd* NCMD = (cmd*) malloc(sizeof(cmd));

    scanf("%s %d", NCMD->command, &NCMD->value);
    NCMD->next = NULL;
    
    // if queue is empty, assign
    // ncmd to head and tail
    // else assign ncmd to 
    // tail->next then tail
    if(queue->head == NULL){
        queue->head = NCMD;
    } else{
        queue->tail->next = NCMD;
    }
    queue->tail = NCMD;
    
}

cmd* dequeue(cmdq* queue){
    cmd *CMD = (cmd*) malloc(sizeof(cmd));
    if(queue->head != NULL){
        // copy values
        strcpy(queue->head->command, CMD->command);
        CMD->value = queue->head->value;
        CMD->next = queue->head->next;
    
        queue->head = queue->head->next;
    }
    
    return CMD;
}