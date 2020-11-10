#include "Link.h"

// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

#include <iostream>
#include <stdio.h>

// ecs36b
#include <time.h>
using namespace std;

#include "Post.h"
#include "Link.h"

Link::Link
(std::string arg_url, std::string arg_class_id, 
    std::string arg_object_id)
{
  this->url = arg_url;
  this->class_id = arg_class_id;
  this->object_id = arg_object_id;
  //std::cout << url << std::endl;
    //std::cout << class_id << std::endl;
    //std::cout << object_id << std::endl;
}

Json::Value * Link::dumpJ
(void)
{
    Json::Value *result_ptr = new Json::Value();
    (*result_ptr)["class_id"] = this->class_id;
    (*result_ptr)["object_id"] = this->object_id;
    (*result_ptr)["url"] = this->url;
    #ifdef _ECS36B_DEBUG_
    std::cout << result_ptr->toStyledString() << std::endl;
    #endif /* _ECS36B_DEBUG_ */
    return result_ptr;
}