
// JSON_Post_redacted.cpp
// #define _ECS36B_DEBUG_

#include <arpa/inet.h>
#include "Post.h"

std::map<std::string, OKey *> All_Keys;

std::vector<Post *> *
getPostbyKey
(std::string key)
{
  if (All_Keys.find(key) == All_Keys.end())
    return NULL;

  OKey *okey_ptr = All_Keys[key];
  return okey_ptr->posts;
}

OKey *
getOKey
(std::string key)
{
  if (All_Keys.find(key) != All_Keys.end())
    return All_Keys[key];

  OKey *new_okey_ptr = new OKey(key);
  new_okey_ptr->posts = new std::vector<Post *>();
  All_Keys[key] = new_okey_ptr;
  return new_okey_ptr;
}

std::string
Json_2_PostID
(Json::Value myv)
{
  return ((myv["id"]).asString());
}

// here it is

Post *
Json_2_Post
(Json::Value myv)
{
  if (myv.isArray() == true)
    {
      // wrong one
      // {...}
      // [...] NULL
      return NULL;
    }

  Post * my_post_ptr = new Post((Person *) NULL, (Message *) NULL);

  // "id"
  if ((myv["id"]).isNull() != true)
    {
      char idstr[1024];
      bzero(idstr, 1024);
      sprintf(idstr, "%s", ((myv["id"]).asString()).c_str());
      if (idstr[0] != '\0')
	{
	  char c_prof_buf[256];
	  char c_post_buf[256];
	  bzero(c_prof_buf, 256);
	  bzero(c_post_buf, 256);

	  sscanf(idstr, "%[^_]_%s", c_prof_buf, c_post_buf);

	  std::string profile_id = { c_prof_buf };
	  std::string post_id = { c_post_buf };

	  // put id attributes to the Post object
	  my_post_ptr->profile_id = profile_id;
	  my_post_ptr->post_id = post_id;
	}
      else
	{
	  std::cerr << "No Post ID presented" << std::endl;
	  exit(-1);
	}
    }
  else
    {
      std::cerr << "No Post ID presented" << std::endl;
      exit(-2);
    }

  int rc = Json_Post_Common(myv, my_post_ptr);
  if (rc != 0)
    {
      std::cerr << "Error Json_Post_Common " << rc << std::endl;
      exit(-3);
    }

  return my_post_ptr;
}

int
Json_Post_Merging
(Json::Value myv, Post * my_post_ptr)
{
  char idstr[1024];
  bzero(idstr, 1024);

  if ((myv).isArray() == true) return -3;
  if ((myv["id"]).isNull() == true) return -1;

  // compare ID first
  // "id" (Let us check first if they share the same ID)
  sprintf(idstr, "%s", ((myv["id"]).asString()).c_str());

  if (idstr[0] != '\0')
    {
      char c_prof_buf[256];
      char c_post_buf[256];
      bzero(c_prof_buf, 256);
      bzero(c_post_buf, 256);

      sscanf(idstr, "%[^_]_%s", c_prof_buf, c_post_buf);

      std::string profile_id = { c_prof_buf };
      std::string post_id = { c_post_buf };

      if ((my_post_ptr->profile_id != profile_id) ||
	  (my_post_ptr->post_id    != post_id))
	{	  
	  std::cerr << "Post IDs mismatched!!" << std::endl;
	  return -1;
	}
    }
  else
    {
      std::cerr << "No Post ID presented for the second JSON" << std::endl;
      return -2;
    }

  // now, they matched, let us proceed with the merge action
  return Json_Post_Common(myv, my_post_ptr);
}

int
Json_Post_Common
(Json::Value myv, Post * my_post_ptr)
{
  int i, j;

  // under Json_Post_Common, we assume that the ID already matched
  // for both Post and myv

  // "actions"
...

  // "comments"
...

  // "keys"
...

  // "links"
...

  // "message"
...

  // "reactions" 
    if (((myv["reactions"]).isNull() != true) &&
	((myv["reactions"]["count"]).asInt() > 0))
    {
      if (my_post_ptr->reactions == NULL)
	my_post_ptr->reactions = new vector<Reaction *>();

      for (i = 0; i < (myv["reactions"]["count"]).asInt(); i++)
	{
	  Json::Value l_jv = myv["reactions"]["data"][i];

	  if (((l_jv["avatar_name"]).isNull() != true) &&
	      ((l_jv["vsID"]).isNull() != true) &&
	      ((l_jv["created_time"]).isNull() != true) &&
	      ((l_jv["type"]).isNull() != true))
	    {

	      Person *react_p_ptr = new Person((l_jv["avatar_name"]).asString(),
					       (l_jv["vsID"]).asString()); 
	      JvTime *react_cr_time_ptr =
		new JvTime(((l_jv["created_time"]).asString()).c_str());
	      Reaction * react_ptr = new Reaction(l_jv["type"].asString(),
						  react_p_ptr, react_cr_time_ptr);

	      (*(my_post_ptr->reactions)).push_back(react_ptr);

	    }
	}
    }

  // "history"
...

  // "id"
  // already done

  // "from"
  // this could be a from replacement
...

  // "to"
    if (((myv["to"]).isNull() != true) &&
	((myv["to"]["count"]).asInt() > 0))
    {
      if (my_post_ptr->receivers == NULL)
	my_post_ptr->receivers = new vector<Person *>();

      for (i = 0; i < (myv["to"]["count"]).asInt(); i++)
	{
	  Json::Value l_jv = myv["to"]["data"][i];

	  if (((l_jv["avatar_name"]).isNull() != true) &&
	      ((l_jv["vsID"]).isNull() != true))
	    {
	      Person * to_ptr = new Person((l_jv["avatar_name"]).asString(),
					   (l_jv["vsID"]).asString());

	      (*(my_post_ptr->receivers)).push_back(to_ptr);
	    }
	}
    }

  // "created_time"
  if ((myv["created_time"]).isNull() != true)
    {
      my_post_ptr->created = new JvTime(((myv["created_time"]).asString()).c_str());
    }

  // "updated_time"
...

  // "is_published"
  my_post_ptr->is_published = (myv["is_published"]).asBool();

  return 0;
}