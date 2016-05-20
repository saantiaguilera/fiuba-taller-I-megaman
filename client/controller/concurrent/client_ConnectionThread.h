/*
Masomenos:


#Lo va a construir el MainScreenController cuando apretas enter sobre la IP.
#Lo joinea el MainScreenController en su destructor (si el trhread es !=NULL)
#que esto va a ocurrir cuando se salga del loop infinito del app->run(w);
constructor(Lista de suscriptores a eventos, ip, port) {
- me guardo la lista
- me connecto con ip port
- dispatcheo evento de que tal me fue (el evento no va a ser mas que un
data model con algun switch para diferenciarlos en el suscriptor)
}

--El socket lo clavo a recibir para siempre?? --
void onReceive() {
- intento parsear alguna respuesta coherente
- dispatcheo un evento de eso
}
*/

#ifndef CLIENT_EVENTS_CLIENT_CONNECTIONTHREAD_H_
#define CLIENT_EVENTS_CLIENT_CONNECTIONTHREAD_H_

#include "../../../common/common_ThreadsafeList.h"
#include "../../../common/common_Thread.h"
#include <unistd.h>

class ConnectionStatus {
public:
  virtual ~ConnectionStatus() {};
  virtual void onConnection() = 0;
  virtual void onDisconnection() = 0;
  virtual void onConnectionError() = 0;
};

class ConnectionThread : public Thread {
private:
  ConcurrentList<ConnectionStatus*> *listeners;
protected:
  virtual void run() {
    //Do something
    usleep(1000 * 1000 * 3); //1000 micro * 1000 millis * 3 secs.

    ConcurrentList<ConnectionStatus*>::ConcurrentIterator concurrentIterator(listeners);
    for (std::list<ConnectionStatus*>::iterator iterator = concurrentIterator.begin() ;
          iterator != concurrentIterator.end() ; ++iterator)
          (*iterator)->onConnection();
  }

public:
  ConnectionThread(ConcurrentList<ConnectionStatus*> *listeners) : listeners(listeners) {}

  ~ConnectionThread() {
    {
      std::list<ConnectionStatus*> unlockedList = listeners->unblock();
      for (std::list<ConnectionStatus*>::iterator it = unlockedList.begin();
    			it != unlockedList.end(); ++it) {
    		delete (*it);
    	}
    }

  	listeners->clear();

  	delete listeners;
    //TODO WATCHOUT HERE.
  };
};

#endif
