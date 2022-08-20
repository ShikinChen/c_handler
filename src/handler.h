//
// Created by Shiki on 2022/8/20.
//

#ifndef C_HANDLER_SRC_HANDLER_H_
#define C_HANDLER_SRC_HANDLER_H_
#include "looper.h"
#include "message.h"

typedef struct handler {

  Looper *looper_;

  HandlerMessage target_;

} Handler;

Handler *CreateHandler(Looper *looper, HandlerMessage handler);

void SendMessage(Handler *handler, Message *msg);

void SendMessage(Handler *handler, Message *msg, long delay);

void PostCallback(Handler *handler, Runnable callback);

void PostCallback(Handler *handler, Runnable callback, long delay);

void FreeHandler(Handler *handler);
#endif //C_HANDLER_SRC_HANDLER_H_
