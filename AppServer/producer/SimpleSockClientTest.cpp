/**
 * To run the test, do:
 * ./SgSimpleSockClientTest
 */

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "SimpleSockClient.h"
#include "../common/XStr.cpp"

using namespace std;
using namespace xercesc;

char const* sHost = "127.0.0.1";
int nPort         = kServerPort;
int MAX_SIZE      = 1000; // 1000 bytes?

int total_passed = 0;
int total_tests = 0;
std::string intToString(int);
void log_without_connect();
void log_some_msgs();
void send_new_register(std::string, std::string, std::string);

// File related Messages
void send_new_file(std::string, std::string, char*);
void send_file_content(std::string, char*);
// File message related helpers
void createAndAppendNewFileMetaDoc(DOMDocument* doc, string userid,
        string hostid, string fileid, char* filepath);
void createAndAppendFileContentDoc(DOMDocument* doc, string fileid,
        char* filepath);

void dup_register();
void valid_login();
void invalid_login();
void init_sync();
void event_sync();
void createRegisterDoc(DOMDocument* doc, string id, string pw, string email);
void log_some_msgs(string msg, int len);
void writeOutDOM(DOMDocument* myDoc, DOMImplementation* impl);
void createLoginDoc(DOMDocument* doc, string id, string pw, string hostid);
void requestLogin(string, string, string);
DOMDocument* createHBMessage();

int main(int argc, char** argv) {
  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    // Do your failure processing here
    char* message = XMLString::transcode(toCatch.getMessage());
    cout << "Error during xerces-c initialization! :\n"
      << message << "\n";
    XMLString::release(&message);
    return 1;
  }
  printf("SgClient Unit Test:\n");

  log_without_connect();
  //log_some_msgs();
  send_new_register("jfu", "good_password_123", "fuj@cs.rpi.edu");
  requestLogin("jfu", "im_a_wrong_password", "1234567890");
  send_new_file("fmaj7", "k234324io2u3", "test");
  dup_register();
  valid_login();
  invalid_login();
  init_sync();
  event_sync();

  std::cout <<std::endl << "---------------------------" << std::endl
    << "  " << total_passed << "/" << total_tests
    << " tests passed." << std::endl
    << "---------------------------" << std::endl;

  return OK;
}

void log_without_connect() {
  total_tests ++;
  std::cout << std::endl << "====>" << std::endl;
  //get a string to fire on wire
  int sendStringLen = kMsgLen;
  uint8_t* sendString = (uint8_t*) malloc(sizeof(uint8_t) * sendStringLen);
  int i;
  for( i = 0 ; i < sendStringLen; i++) {
    sendString[i] = 'a';
  }

  //add a client/connection
  client_t clients;
  memset(&clients, '\0', sizeof(client_t));
  client_t* client = &clients;

  int err = hb_log(client, sendString, sendStringLen);

  assert(err == NOT_READY);
  std::cout << "log_without_connect() test passed" << std::endl;

  total_passed ++;
}

void log_some_msgs() {
  total_tests ++;
  std::cout << std::endl << "====>" << std::endl;
  //get a string to fire on wire
  int sendStringLen = kMsgLen;
  uint8_t* sendString = (uint8_t*) malloc(sizeof(uint8_t) * sendStringLen);
  int i;
  for( i = 0 ; i < sendStringLen; i++) {
    sendString[i] = 'a';
  }

  //add a client/connection
  client_t clients;
  memset(&clients, '\0', sizeof(client_t));
  client_t* client = &clients;

  //try to connect
  if(hb_connect(sHost, nPort, client) != 0) {
    perror("hb_connect() failed\n");
    return;
    //exit(1);
  }

  //send kMsgNum messages synchronously
  int counter = 0;
  while(counter < 1) {
    int err = hb_log(client, sendString, sendStringLen);
    assert(err == OK);
    counter++;
    //printf("Got a correct reply from server, counter = %d\n", counter);
    //sleep(1);
  }

  //disconnect
  hb_disconnect(client);

  printf("All messages acknowledged, SgSimpleSockClientTest exit normally\n");
  std::cout << "log_some_msgs() test passed" << std::endl;
  total_passed ++;
}

void requestLogin(std::string id, std::string passwd, std::string hostid) {

  total_tests ++;
  std::cout << std::endl << "====>" << std::endl;

  DOMDocument*   myDoc;
  DOMImplementation* impl =  DOMImplementationRegistry::getDOMImplementation(X("Core"));
  assert(impl != NULL);
  myDoc = createHBMessage();

  createLoginDoc(myDoc, id, passwd, hostid);
  writeOutDOM(myDoc, impl);

  std::cout << "loginRequest(): id="<<id <<", passwd="<<passwd << std::endl;
  total_passed++;
}

void send_new_register(std::string id, std::string passwd, std::string email) {
  total_tests ++;
  std::cout << std::endl << "====>" << std::endl;

  DOMDocument*   myDoc;
  DOMImplementation* impl =  DOMImplementationRegistry::getDOMImplementation(X("Core"));
  assert(impl != NULL);
  myDoc = createHBMessage();

  createRegisterDoc(myDoc, id, passwd, email);
  writeOutDOM(myDoc, impl);

  std::cout << "new_register(): id="<<id <<", passwd="<<passwd << std::endl;
  total_passed++;
}

void writeOutDOM(DOMDocument* myDoc, DOMImplementation* impl){
  const XMLSize_t elementCount = myDoc->getElementsByTagName(X("*"))->getLength();
  //impl          = DOMImplementationRegistry::getDOMImplementation(X("LS"));
  DOMLSSerializer   *theSerializer = ((DOMImplementationLS*)impl)->createLSSerializer();
  DOMConfiguration *theConfig = theSerializer->getDomConfig();
  theConfig->setParameter(X("format-pretty-print"), true);
  //if ( theSerializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true) )
  //      theSerializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);
  DOMLSOutput       *theOutputDesc = ((DOMImplementationLS*)impl)->createLSOutput();
  //XMLFormatTarget *myFormTarget = new StdOutFormatTarget();
  MemBufFormatTarget *myFormTarget = new MemBufFormatTarget();
  theOutputDesc->setByteStream(myFormTarget);
  theSerializer->write(myDoc, theOutputDesc);
  cout << "MemBuf len: "<< myFormTarget->getLen() << ", content: \n"<< myFormTarget->getRawBuffer() << endl;

  int msg_len = myFormTarget->getLen();
  string output((char*)myFormTarget->getRawBuffer());
  log_some_msgs(output, msg_len);
}

void send_new_file(std::string userid, std::string hostid, char* filepath) {
    total_tests ++;
    std::cout << std::endl << "====>" << std::endl;

    DOMImplementation* impl =  DOMImplementationRegistry::getDOMImplementation(X("Core"));
    //TODO:: generate unique file id
    string fileid = "A1B2C3D4E5";

    DOMDocument* myDoc = createHBMessage();
    createAndAppendNewFileMetaDoc(myDoc, userid, hostid, fileid, filepath);
    writeOutDOM(myDoc, impl);

    send_file_content(fileid, filepath);

    std::cout << "send_new_file(): userid="<<userid <<", hostid="<<hostid <<", filepath="<<filepath << std::endl;
    total_passed++;
}

void send_file_content(std::string fileid, char* filepath) {
    total_tests ++;
    std::cout << std::endl << "====>" << std::endl;

    DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(X("Core"));
    DOMDocument* myDoc = createHBMessage();
    createAndAppendFileContentDoc(myDoc, fileid, filepath);
    writeOutDOM(myDoc, impl);

    std::cout << "send_file_content(): userid="<<fileid <<", filepath="<<filepath << std::endl;
    total_passed++;
}

void dup_register() {
}

void valid_login() {
}

void invalid_login() {
}

void init_sync() {
}

void event_sync() {
}

void createRegisterDoc(DOMDocument* doc, string id, string pw, string email) {
  int errorCode = 0;

  try
  {
    DOMElement* rootElem = doc->getDocumentElement();

    DOMElement*  typeElem = doc->createElement(X("registerRequest"));
    rootElem->appendChild(typeElem);

    /*
    prodElem->setAttribute(X("name"), X("registerRequestMessageType"));

    DOMElement* nextElem = doc->createElement(X("ActionType"));
    prodElem->appendChild(nextElem);
    nextElem->setAttribute(X("Name"), X("Request"));

    DOMElement* userElem = doc->createElement(X("User"));
    nextElem->appendChild(userElem);
    */

    DOMElement*  catElem = doc->createElement(X("userid"));
    typeElem->appendChild(catElem);

    //catElem->setAttribute(X("idea"), X("great"));

    DOMText*    catDataVal = doc->createTextNode(X(id.c_str()));
    catElem->appendChild(catDataVal);

    DOMElement*  devByElem = doc->createElement(X("password"));
    typeElem->appendChild(devByElem);

    DOMText*  devByDataVal = doc->createTextNode(X(pw.c_str()));
    devByElem->appendChild(devByDataVal);

    // new schema got rid of email info
    /*
    DOMElement*  evaByElem = doc->createElement(X("email"));
    typeElem->appendChild(evaByElem);

    DOMText*  evaByDataVal = doc->createTextNode(X(email.c_str()));
    evaByElem->appendChild(evaByDataVal);
    */

    //
    // Now count the number of elements in the above DOM tree.
    //

    const XMLSize_t elementCount = doc->getElementsByTagName(X("*"))->getLength();
    cout << "The tree just created contains: " << elementCount << " elements." << endl;

    //doc->release();
  }
  catch (const OutOfMemoryException&)
  {
    cerr << "OutOfMemoryException" << endl;
    errorCode = 5;
  }
  catch (const DOMException& e)
  {
    cerr << "DOMException code is:  " << e.code << endl;
    errorCode = 2;
  }
  catch (...)
  {
    cerr << "An error occurred creating the document" << endl;
    errorCode = 3;
  }
}

DOMDocument* createHBMessage() {
    DOMImplementation* impl =  DOMImplementationRegistry::getDOMImplementation(X("Core"));
    assert(impl != NULL);
    return impl->createDocument(
            0,                    // root element namespace URI.
            X("HBMessages"),         // root element name (it doesn't like space in between)
            0);

}

DOMElement* createTextNode(DOMDocument* doc, string name, string val) {
    DOMElement* textNodeElem = doc->createElement(X(name.c_str()));
    DOMText* textNodeVal = doc->createTextNode(X(val.c_str()));
    textNodeElem->appendChild(textNodeVal);
    return textNodeElem;
}

void createAndAppendNewFileMetaDoc(DOMDocument* doc, string userid, string hostid,
        string fileid, char* filepath) {

    int errorCode = 0;
    try
    {
        DOMElement* rootElem = doc->getDocumentElement();

        DOMElement* requestElem = doc->createElement(X("newfileRequest"));
        rootElem->appendChild(requestElem);

        DOMElement* uidElem = createTextNode(doc, "userid", userid);
        requestElem->appendChild(uidElem);

        DOMElement* hostidElem = createTextNode(doc, "hostid", hostid);
        requestElem->appendChild(hostidElem);

        DOMElement* fileidElem = createTextNode(doc, "fileid", fileid);
        requestElem->appendChild(fileidElem);

        DOMElement* filepathElem = createTextNode(doc, "filepath", filepath);
        requestElem->appendChild(filepathElem);

        // Now count the number of elements in the above DOM tree.
        const XMLSize_t elementCount = doc->getElementsByTagName(X("*"))->getLength();
        cout << "The tree just created contains: " << elementCount << " elements." << endl;
    }
    catch (const OutOfMemoryException&)
    {
        cerr << "OutOfMemoryException" << endl;
        errorCode = 5;
    }
    catch (const DOMException& e)
    {
        cerr << "DOMException code is:  " << e.code << endl;
        errorCode = 2;
    }
    catch (...)
    {
        cerr << "An error occurred creating the document" << endl;
        errorCode = 3;
    }
}

void createAndAppendFileContentDoc(DOMDocument* doc, string fileid,
      char* filepath) {

    int errorCode = 0;
    try
    {
        DOMElement* rootElem = doc->getDocumentElement();


        char buffer[MAX_SIZE];
        ifstream myFile (filepath, ios::in|ios::binary);
        if (!myFile) {
          // An error occurred!
          // myFile.gcount() returns the number of bytes read.
          // calling myFile.clear() will reset the stream state
          // so it is usable again.
          cout << "ERROR: Cannot open file.";
        }
        int sequence = 0;
        while (myFile.read (buffer, MAX_SIZE)) {
          DOMElement* requestElem = doc->createElement(X("filecontentRequest"));
          rootElem->appendChild(requestElem);
          DOMElement* fileElem = createTextNode(doc, "file", fileid);
          requestElem->appendChild(fileElem);
          string filecontent (buffer, buffer+MAX_SIZE);
          DOMElement* filecontentElem = createTextNode(doc, "content", filecontent);
          requestElem->appendChild(filecontentElem);
          cout << "filecontent:" << filecontent;
          DOMElement* sequenceElem = createTextNode(doc, "sequence", intToString(sequence));
          requestElem->appendChild(sequenceElem);
          ++sequence;
        }

        // Now count the number of elements in the above DOM tree.
        const XMLSize_t elementCount = doc->getElementsByTagName(X("*"))->getLength();
        cout << "The tree just created contains: " << elementCount << " elements." << endl;
    }
    catch (const OutOfMemoryException&)
    {
        cerr << "OutOfMemoryException" << endl;
        errorCode = 5;
    }
    catch (const DOMException& e)
    {
        cerr << "DOMException code is:  " << e.code << endl;
        errorCode = 2;
    }
    catch (...)
    {
        cerr << "An error occurred creating the document" << endl;
        errorCode = 3;
    }
}


void createLoginDoc(DOMDocument* doc, string id, string pw, string email) {
  int errorCode = 0;

  try
  {
    DOMElement* rootElem = doc->getDocumentElement();

    DOMElement*  typeElem = doc->createElement(X("loginRequest"));
    rootElem->appendChild(typeElem);

    DOMElement*  catElem = doc->createElement(X("userid"));
    typeElem->appendChild(catElem);

    //catElem->setAttribute(X("idea"), X("great"));

    DOMText*    catDataVal = doc->createTextNode(X(id.c_str()));
    catElem->appendChild(catDataVal);

    DOMElement*  devByElem = doc->createElement(X("password"));
    typeElem->appendChild(devByElem);

    DOMText*  devByDataVal = doc->createTextNode(X(pw.c_str()));
    devByElem->appendChild(devByDataVal);

    // new schema got rid of email info
    /*
    DOMElement*  evaByElem = doc->createElement(X("email"));
    typeElem->appendChild(evaByElem);

    DOMText*  evaByDataVal = doc->createTextNode(X(email.c_str()));
    evaByElem->appendChild(evaByDataVal);
    */

    //
    // Now count the number of elements in the above DOM tree.
    //

    const XMLSize_t elementCount = doc->getElementsByTagName(X("*"))->getLength();
    cout << "The tree just created contains: " << elementCount << " elements." << endl;

    //doc->release();
  }
  catch (const OutOfMemoryException&)
  {
    cerr << "OutOfMemoryException" << endl;
    errorCode = 5;
  }
  catch (const DOMException& e)
  {
    cerr << "DOMException code is:  " << e.code << endl;
    errorCode = 2;
  }
  catch (...)
  {
    cerr << "An error occurred creating the document" << endl;
    errorCode = 3;
  }
}
void log_some_msgs(string msg, int len) {
  //get a string to fire on wire
  assert(len > 0);
  int sendStringLen = len;
  string sendString(msg);

  //add a client/connection
  client_t clients;
  memset(&clients, '\0', sizeof(client_t));
  client_t* client = &clients;

  //try to connect
  if(hb_connect(sHost, nPort, client) != 0) {
    perror("hb_connect() failed\n");
    return;
    //exit(1);
  }

  //send kMsgNum messages synchronously
  int counter = 0;
  while(counter < 1) {
    int err = hb_log(client, (uint8_t*)sendString.c_str(), sendStringLen);
    assert(err == OK);
    counter++;
    //printf("Got a correct reply from server, counter = %d\n", counter);
    //sleep(1);
  }

  //disconnect
  hb_disconnect(client);

  printf("All messages acknowledged.\n");
}

std::string intToString(int i)
{
  std::stringstream ss;
  std::string s;
  ss << i;
  s = ss.str();

  return s;
}
