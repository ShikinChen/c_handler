#include <iostream>
#include <handler_thread.h>
#include <handler.h>

void test_handler_message(Message *msg) {
  printf("test handler_message what_::%d\n", msg->what_);
}

void test_runnable() {
  printf("test runnable callback...\n");
}

int main(int argc, const char* argv[]) {
  HandlerThread *thread = CreateThread("test-handler");
  StartThread(thread);
  HandlerMessage hand = &test_handler_message;
  Handler *handler = CreateHandler(thread->looper_, hand);
  Message *msg = CreateMessage(20);
  SendMessage(handler, msg, 1000);
  Runnable run = &test_runnable;
  PostCallback(handler, run);
  ThreadJoin(thread);
  return 0;
}
