//
// Created by Shiki on 2022/8/20.
//
#include "message.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Message* CreateMessage(int what) {
  return CreateMessage(what, 0);
}

Message* CreateMessage(int what, int arg1) {
  return CreateMessage(what, arg1, 0);
}

Message* CreateMessage(int what, int arg1, int arg2) {
  int msg_len = sizeof(Message);
  Message* message = (Message*)malloc(msg_len);
  memset(message, 0x0, msg_len);
  message->what_ = what;
  message->arg1_ = arg1;
  message->arg2_ = arg2;
  return message;
}

Message* CreateMessage(int what, char *msg, int size) {
  return CreateMessage(what, 0, msg, size);
}

Message* CreateMessage(int what, int arg1, char *msg, int size) {
  return CreateMessage(what, arg1, 0, msg, size);
}

Message* CreateMessage(int what, int arg1, int arg2, char *msg, int size) {
  int msg_len = sizeof(Message);
  Message* message = (Message*)malloc(msg_len);
  memset(message, 0x0, msg_len);
  message->what_ = what;
  message->arg1_ = arg1;
  message->arg2_ = arg2;
  message->msg_ = (char*)malloc(size + 1);
  memset(message->msg_, 0x0, size + 1);
  snprintf(message->msg_, size, "%s", msg);
  message->size_ = size;
  return message;
}

Message* CreateMessage(int what, void *obj) {
  return CreateMessage(what, 0, obj);
}

Message* CreateMessage(int what, int arg1, void *obj) {
  return CreateMessage(what, arg1, 0, obj);
}

Message* CreateMessage(int what, int arg1, int arg2, void *obj) {
  int msg_len = sizeof(Message);
  Message* msg = (Message*)malloc(msg_len);
  memset(msg, 0x0, msg_len);
  msg->what_ = what;
  msg->arg1_ = arg1;
  msg->arg2_ = arg2;
  msg->obj_ = obj;
  return msg;
}

Message* CreateMessage(int what, void *obj, char *msg, int size) {
  return CreateMessage(what, 0, obj, msg, size);
}

Message* CreateMessage(int what, int arg1, void *obj, char *msg, int size) {
  return CreateMessage(what, arg1, 0, obj, msg, size);
}

Message* CreateMessage(int what, int arg1, int arg2, void *obj, char *msg, int size) {
  int msg_len = sizeof(Message);
  Message* message = (Message*)malloc(msg_len);
  memset(message, 0x0, msg_len);
  message->what_ = what;
  message->arg1_ = arg1;
  message->arg2_ = arg2;
  message->msg_ = (char*)malloc(size + 1);
  memset(message->msg_, 0x0, size + 1);
  snprintf(message->msg_, size, "%s", msg);
  message->size_ = size;
  message->obj_ = obj;
  return message;
}

MessageProxy* CreateProxy(Runnable run) {
  int msg_len = sizeof(MessageProxy);
  MessageProxy* message = (MessageProxy*)malloc(msg_len);
  memset(message, 0x0, msg_len);
  message->run_ = run;
  return message;
}

MessageProxy* CreateProxy(Message *msg, HandlerMessage target) {
  int msg_len = sizeof(MessageProxy);
  MessageProxy* message = (MessageProxy*)malloc(msg_len);
  memset(message, 0x0, msg_len);
  message->msg_ = msg;
  message->target_ = target;
  return message;
}

void FreeMessage(Message *msg) {
  free(msg->msg_);
  free(msg);
}

void FreeProxy(MessageProxy *proxy) {
  if (proxy->msg_ != NULL) {
	FreeMessage(proxy->msg_);
  }
  free(proxy);
}