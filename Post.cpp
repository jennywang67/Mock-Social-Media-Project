#include "Post.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
Post::Post
(Person * arg_author, Message * arg_msg)
{
  this->author = arg_author;
  this->msg = arg_msg;
  this->receivers = NULL;
  this->actions = NULL;
  this->comments = NULL;
  this->reactions = NULL;
  this->links = NULL;
  this->keys = NULL;
  this->created = NULL;
  this->updated = NULL;
}

Json::Value * Post::dumpJ
(void)
{
  int i;

  Json::Value * result_ptr = new Json::Value();
  Json::Value * dumpjv_ptr;

  // "actions"

  if (this->actions != NULL)
    {
        Json::Value json_actions;
        Json::Value json_actions_array;
        for (i = 0; i < (this->actions)->size(); i++)
            {
              //std::cout << "be" << std::endl;
              dumpjv_ptr = ((*(this->actions))[i])->dumpJ();
              //std::cout << "af" << std::endl;
              json_actions[i] = (*dumpjv_ptr);
              delete dumpjv_ptr;
            }
        json_actions_array["data"] = json_actions;
        json_actions_array["count"] = ((int) (*(this->actions)).size());
        // std::cout << json_actions_array.toStyledString() << std::endl;
        (*result_ptr)["actions"] = json_actions_array;
    }
//std::cout << "comment1" << std::endl;
  // comments
  if (this->comments != NULL)
    {
        Json::Value json_comments;
        Json::Value json_comments_array;
        for (i = 0; i < (this->comments)->size(); i++)
        {
          //std::cout << "Post.cpp" << i << std::endl;
          dumpjv_ptr = ((*(this->comments))[i])->dumpJ();
          json_comments[i] = (*dumpjv_ptr);
          delete dumpjv_ptr;
        }

        //std::cout << this->tags << std::endl;
        //for (int k = 0; k < ((this->comments)->tags)->size; k++)
        json_comments_array["data"] = json_comments;
        json_comments_array["count"] = ((int) (*(this->comments)).size());
        //std::cout << json_comments_array.toStyledString() << std::endl;
        (*result_ptr)["comments"] = json_comments_array;
    }
//std::cout << "comment2" << std::endl;


  // "keys"
    if (this->keys != NULL)
    {
        Json::Value json_keys;
        Json::Value json_keys_array;
        Json::Value json_keys_line;
        int len = 0;
        std::string key_name;
        //std::cout << "--------" << ((*(this->keys)[0]) << std::endl;
        for (i = 0; i < (this->keys)->size(); i++)
        {
          //std::cout << "---------------" << i << std::endl;
          dumpjv_ptr = ((*(this->keys))[i])->dumpJ();
          json_keys[i] = (*dumpjv_ptr);
          len = ((json_keys[i]).toStyledString()).length();
          //std::cout << len << std::endl;
          //std::cout << ((json_keys[i]).toStyledString()).substr(15,len-1-18) << std::endl;
          json_keys_line[i] = ((json_keys[i]).toStyledString()).substr(15,len-1-18);
          delete dumpjv_ptr;
        }
        json_keys_array["data"] = json_keys_line;
        json_keys_array["count"] = ((int) (*(this->keys)).size());
        //std::cout << json_keys_array.toStyledString() << std::endl;
        (*result_ptr)["keys"] = json_keys_array;
    }
    //std::cout << "KEYS" << std::endl;


  // "links"
  if (this->links != NULL)
    {
        Json::Value json_links;
        Json::Value json_links_array;
        for (int i = 0; i < (this->links)->size(); i++)
        {
            dumpjv_ptr = ((*(this->links))[i])->dumpJ();
            json_links[i] = (*dumpjv_ptr);
            delete dumpjv_ptr;
        }
        json_links_array["data"] = json_links;
        json_links_array["count"] = ((int) (*(this->links)).size());
        // std::cout << json_links_array.toStyledString() << std::endl;
        (*result_ptr)["links"] = json_links_array;
    }


  // "message"
  if (this->msg != NULL)
    {
      //(*result_ptr)["message"] = (this->msg);
      (*result_ptr)["message"] = (this->msg)->content;
      
    }

  // "reactions"
  if (this->reactions != NULL)
    {
        Json::Value json_reactions;
        Json::Value json_reactions_array;
        //std::cout << "--------" << ((*(this->reactions))[0]) << std::endl;
        for (i = 0; i < (this->reactions)->size(); i++)
        {
          //std::cout << "---------------" << i << std::endl;
          dumpjv_ptr = ((*(this->reactions))[i])->dumpJ();
          json_reactions[i] = (*dumpjv_ptr);
          delete dumpjv_ptr;
        }
        json_reactions_array["data"] = json_reactions;
        json_reactions_array["count"] = ((int) (*(this->reactions)).size());
        // std::cout << json_reactions_array.toStyledString() << std::endl;
        (*result_ptr)["reactions"] = json_reactions_array;
    }

  // "id"
  (*result_ptr)["id"] = (this->profile_id + "_" + this->post_id);

  // "from"
  if (this->author != NULL)
    {
      dumpjv_ptr = (this->author)->dumpJ();
      (*result_ptr)["from"] = (*dumpjv_ptr);
      delete dumpjv_ptr;
    }

  // "to"
  if (this->receivers != NULL)
    {
        Json::Value json_to;
        Json::Value json_to_array;
        for (int i = 0; i< (this->receivers)->size(); i++)
        {
            dumpjv_ptr = ((*this->receivers))[i]->dumpJ();
            json_to[i] = (*dumpjv_ptr);
            delete dumpjv_ptr;
        }
        json_to_array["data"] = json_to;
        json_to_array["count"] = ( (int) 
                            (*(this->receivers)).size() );
        (*result_ptr)["to"] = json_to_array;
    }

  // "created_time"
  if (this->created != NULL)
    {
      (*result_ptr)["created_time"] = *((this->created)->getTimeString());
    }

  // "updated_time"
  if (this->updated != NULL)
    {
      (*result_ptr)["updated_time"] = *((this->updated)->getTimeString());
    }

  // "is_published"
  (*result_ptr)["is_published"] = this->is_published;

#ifdef _ECS36B_DEBUG_
  std::cout << result_ptr->toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
  return result_ptr;
}