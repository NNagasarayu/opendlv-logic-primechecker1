#include<chrono>
#include<iostream>

#include "cluon-complete.hpp"
#include "prime-checker.hpp"
#include "messages.hpp"

int32_t main(int32_t, char **) {
  PrimeChecker pc;
  std::cout << "Hello world = " << pc.isPrime(43) << std::endl;
  
  cluon::OD4Session od4(111, //this is a namespace which can communicate with various udp multicast
    [](cluon::data::Envelope &&envelope) noexcept { // the envolope contains who sent what timestamp and all information
      if  (envelope.dataType() == 2001) {// check if the datatype of the envelope is 2001
        MyTestMessage1 receivedMsg = 
         cluon::extractMessage<MyTestMessage1>(std::move(envelope));// this command output or extract the envelope and put it into received msg
        
         PrimeChecker pc;
         std::cout << receivedMsg.myValue() << " is "
            << (pc.isPrime(receivedMsg.myValue()) ? "" : "not") << " a prime." 
            << std::endl;
      }
    });
  
 
  uint16_t value;
  std::cout << "Enter a number to check: ";
  std::cin >> value;
  
  MyTestMessage1 msg;
  msg.myValue(value);
  
  od4.send(msg); //take the message put it in a envolope and stamp it and send it
  
  return 0;
}
//od4 session has two arguments first one is 111-which id number and the rest of the receiving message
