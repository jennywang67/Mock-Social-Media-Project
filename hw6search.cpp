#include <iostream>
#include <string.h>
#include <string>
// JSON RPC part
#include <stdlib.h>
#include "hw6search.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

#include "Post.h"
#include <json/json.h>
#include <fstream>
#include <arpa/inet.h>
#include "Post.h"
#include <string.h>
#include <string>
#include <iostream>
#include <stdio.h>
using namespace jsonrpc;
using namespace std;

int
main(int argc, char *argv[])
{
  if (argc != 2) return -1;

  FILE *jf1 = fopen(argv[1], "r");
  if (jf1 == NULL) return -1;

  Json::CharReaderBuilder builder;
  Json::CharReader* reader;
  std::string errors;
  bool parsingSuccessful;

  // *** process JSON File ***
  long lSize1;
  size_t lresult1;

  // obtain file size:
  fseek(jf1, 0 , SEEK_END);
  lSize1 = ftell(jf1);
  rewind(jf1);

  // allocate memory to contain the whole file:
  char *jf1_ptr = (char *) malloc(sizeof(char)*lSize1);
  // copy the file into the buffer:
  lresult1 = fread(jf1_ptr, 1, lSize1, jf1);    
  if (lresult1 != lSize1)
    {
      fputs("Reading error", stderr);
      exit (-3);
    }

  Json::Value myv_message;
  reader = builder.newCharReader();
  parsingSuccessful = reader->parse(jf1_ptr, jf1_ptr + lSize1, &myv_message, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the content of the first JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }
  fclose(jf1);
    HttpClient httpclient("http://169.237.6.102:55407");
  hw6Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value result_json;
  
  // below: just simple examples
  try {
    result_json = myClient.search(myv_message.toStyledString());
    std::cout << (((result_json).toStyledString())) << endl; // important
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  char fname_buf[1024];
  FILE * post_f_ptr;
  long lSize;
  size_t lresult;
  char post_json_buf[8192];
  // write it back -- Persistent Object
  if ( ((result_json["count"].isNull()) !=  true ))
    {
      for(int i = 0; i < result_json["count"].asInt(); i++)
      {
        Json::Value r_jv = result_json["data"][i];
        bzero(fname_buf, 1024);
        sprintf(fname_buf, "post_%s.json", ((r_jv["id"]).asString()).c_str());
        post_f_ptr = fopen(fname_buf, "w");
        if(post_f_ptr != NULL)
        {
            char post_json_buf[8192];
            bzero(post_json_buf, 8192);
            sprintf(post_json_buf, "%s", ((r_jv).toStyledString()).c_str());
            lSize = strlen(post_json_buf);
            std::cout << fname_buf << " " << lSize <<  std::endl;
            lresult = fwrite(post_json_buf, 1, lSize, post_f_ptr);    
            if (lresult != lSize)
            {
              fputs("Reading error", stderr);
              exit (-3);
            }
            fclose(post_f_ptr);
        }

      }    
    }
  return 0;
}
