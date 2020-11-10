#include "OKey.h"


Json::Value * OKey::dumpJ
(void)
{
    Json::Value *result_ptr = new Json::Value();
    (*result_ptr)["keys"] = this->okey;
    //std::cout << result_ptr->toStyledString() << std::endl;
    return result_ptr;
}
