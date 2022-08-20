//
// Created by Shiki on 2022/8/20.
//

#ifndef C_HANDLER_SRC_LOOPER_H_
#define C_HANDLER_SRC_LOOPER_H_

#include <pthread.h>
#include "message.h"

typedef struct message_queue {

  MessageProxy *msg_;

  message_queue *next_;

} MessageQueue;

typedef struct looper {

  char *name_;

  pthread_mutex_t *lock_;

  pthread_condattr_t *waitattr_;

  pthread_cond_t *wait_;

  MessageQueue *queue_;

  int quit_;

} Looper;

void FreeMessageQueue(MessageQueue *queue);

void StartLooper(Looper *looper);

void AddMessage(Looper *looper, MessageProxy *msg);

MessageQueue *NextMessage(Looper *looper);

void QuitLooper(Looper *looper);

void FreeLooper(Looper *looper);

#endif //C_HANDLER_SRC_LOOPER_H_
