#include "Message.h"
#include <string>
#include <iostream>
#include <stdio.h>

/*
Json::Value * Message::dumpJ
(void)
{
    Json::Value *result_ptr = new Json::Value();
    (*result_ptr)["message"] = this->content;
    #ifdef _ECS36B_DEBUG_
    std::cout << result_ptr->toStyledString() << std::endl;
    #endif /* _ECS36B_DEBUG_ */
    /*
    return result_ptr;
}
*/