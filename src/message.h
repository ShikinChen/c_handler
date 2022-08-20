//
// Created by Shiki on 2022/8/20.
//

#ifndef C_HANDLER_SRC_MESSAGE_H_
#define C_HANDLER_SRC_MESSAGE_H_

typedef void (*Runnable)();

typedef struct message {
  int what_;
  int arg1_;
  int arg2_;
  char *msg_;
  int size_;
  void *obj_;
} Message;

typedef void(*HandlerMessage)(Message *message);

typedef struct message_proxy {
  Message *msg_;
  Runnable run_;
  HandlerMessage target_;
  long time_;
} MessageProxy;

Message *CreateMessage(int what);

Message *CreateMessage(int what, int arg1);

Message *CreateMessage(int what, int arg1, int arg2);

Message *CreateMessage(int what, int arg1, int arg2, int arg3);

Message *CreateMessage(int what, int arg1, int arg2, int arg3, int arg4);

Message *CreateMessage(int what, char *msg, int size);

Message *CreateMessage(int what, int arg1, char *msg, int size);

Message *CreateMessage(int what, int arg1, int arg2, char *msg, int size);

Message *CreateMessage(int what, int arg1, int arg2, int arg3, char *msg, int size);

Message *CreateMessage(int what, int arg1, int arg2, int arg3, int arg4, char *msg, int size);

Message *CreateMessage(int what, void *obj);

Message *CreateMessage(int what, int arg1, void *obj);

Message *CreateMessage(int what, int arg1, int arg2, void *obj);

Message *CreateMessage(int what, int arg1, int arg2, int arg3, void *obj);

Message *CreateMessage(int what, int arg1, int arg2, int arg3, int arg4, void *obj);

Message *CreateMessage(int what, void *obj, char *msg, int size);

Message *CreateMessage(int what, int arg1, void *obj, char *msg, int size);

Message *CreateMessage(int what, int arg1, int arg2, void *obj, char *msg, int size);

Message *CreateMessage(int what, int arg1, int arg2, int arg3, void *obj, char *msg, int size);

Message *CreateMessage(int what, int arg1, int arg2, int arg3, int arg4, void *obj, char *msg, int size);

MessageProxy *CreateProxy(Runnable run);

MessageProxy *CreateProxy(Message *msg, HandlerMessage target);

void FreeMessage(Message *msg);

void FreeProxy(MessageProxy *proxy);

#endif //C_HANDLER_SRC_MESSAGE_H_
