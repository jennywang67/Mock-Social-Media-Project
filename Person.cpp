#include "Person.h"
#include <arpa/inet.h>
GPS_DD::GPS_DD()
{
}

GPS_DD::GPS_DD(double arg_latitude, double arg_longtitude)
{
  this->latitude = arg_latitude;
  this->longtitude = arg_longtitude;
}

Json::Value * GPS_DD::dumpJ
(void)
{
  Json::Value *result_ptr = new Json::Value();
  (*result_ptr)["location"]["latitude"] = this->latitude;
  (*result_ptr)["location"]["longtitude"] = this->longtitude;
#ifdef _ECS36B_DEBUG_
  std::cout << result_ptr->toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
  return result_ptr;
}


double 
GPS_DD::getLatitude()
{
  return this->latitude;
}
 
double
GPS_DD::getLongtitude
()
{
  return this->longtitude;
}

// DD distance calculation

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::                                                                         :*/
/*::  This routine calculates the distance between two points (given the     :*/
/*::  latitude/longitude of those points). It is being used to calculate     :*/
/*::  the distance between two locations using GeoDataSource(TM) products.   :*/
/*::                                                                         :*/
/*::  Definitions:                                                           :*/
/*::    South latitudes are negative, east longitudes are positive           :*/
/*::                                                                         :*/
/*::  Passed to function:                                                    :*/
/*::    lat1, lon1 = Latitude and Longitude of point 1 (in decimal degrees)  :*/
/*::    lat2, lon2 = Latitude and Longitude of point 2 (in decimal degrees)  :*/
/*::    unit = the unit you desire for results                               :*/
/*::           where: 'M' is statute miles (default)                         :*/
/*::                  'K' is kilometers                                      :*/
/*::                  'N' is nautical miles                                  :*/
/*::  Worldwide cities and other features databases with latitude longitude  :*/
/*::  are available at https://www.geodatasource.com                         :*/
/*::                                                                         :*/
/*::  For enquiries, please contact sales@geodatasource.com                  :*/
/*::                                                                         :*/
/*::  Official Web site: https://www.geodatasource.com                       :*/
/*::                                                                         :*/
/*::           GeoDataSource.com (C) All Rights Reserved 2018                :*/
/*::                                                                         :*/
/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

#include <math.h>
#define pi 3.14159265358979323846

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  Function prototypes                                           :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double);
double rad2deg(double);

double GeoDataSource_distance(double lat1, double lon1, double lat2, double lon2, char unit) 
{
  double theta, dist;
  if ((lat1 == lat2) && (lon1 == lon2))
    {
      return 0;
    }
  else
    {
      theta = lon1 - lon2;
      dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
      dist = acos(dist);
      dist = rad2deg(dist);
      dist = dist * 60 * 1.1515;
      switch(unit)
	{
	case 'M':
	  break;
	case 'K':
	  dist = dist * 1.609344;
	  break;
	case 'N':
	  dist = dist * 0.8684;
	  break;
	}
      return (dist);
    }
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts decimal degrees to radians             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double deg)
{
  return (deg * pi / 180);
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts radians to decimal degrees             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double rad2deg(double rad)
{
  return (rad * 180 / pi);
}

double
GPS_DD::distance
(GPS_DD& another)
{
  return GeoDataSource_distance(this->latitude, this->longtitude, another.getLatitude(), another.getLongtitude(), 'M');
}

IP_Address::IP_Address()
{
}

IP_Address::IP_Address
(std::string arg_ip)
{
}

Json::Value * IP_Address::dumpJ
(void)
{
  // 50:15
  Json::Value *result_ptr = new Json::Value();
  (*result_ptr)["network"] = this->addr;
  // (*result_ptr)["network"] = this->addr;
  //std::cout << this->addr <<std::endl;
#ifdef _ECS36B_DEBUG_
  std::cout << result_ptr->toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
  return result_ptr;
}
/*
// implementation from professor wu
Json::Value * 
IP_Address::dumpJ
()
{
  Json::Value * result_ptr = new Json::Value();
  struct in_addr my_in;
  my_in.s_addr = addr;
  char *ip_ch = inet_ntoa(my_in);
  std::string ip_str {ip_ch};
  (*result_ptr)["IPv4"] = ip_str;
  //std::cout << "hello" << std::endl;
  return result_ptr;
}
*/


std::string SDefault {"Default"};

std::string&
IP_Address::getIPaddressString()
{  
  return SDefault;
}

std::string
IP_Address::getIPaddressValue()
{
  return addr;
}

unsigned int Person::person_count { };

Person::Person(std::string core_arg_host_url, std::string core_arg_owner_vsID,
	       std::string core_arg_class_id, std::string core_arg_object_id)
  : Core { core_arg_host_url, core_arg_owner_vsID, core_arg_class_id, core_arg_object_id }
{
  person_count++;
  std::cout << "Core Constructor" << std::endl;
}

Person::Person()
{
}

Person::Person(std::string core_arg_host_url, std::string core_arg_owner_vsID,
	       std::string core_arg_class_id, std::string core_arg_object_id,
	       std::string arg_avatar_name, std::string arg_vsID)
  : Core { core_arg_host_url, core_arg_owner_vsID, core_arg_class_id, core_arg_object_id }
{
  this->avatar_name = arg_avatar_name;
  this->vsID = arg_vsID;
}

Person::Person
(std::string arg_avatar_name, std::string arg_vsID)
{
  this->avatar_name = arg_avatar_name;
  this->vsID = arg_vsID;
  //std::cout << avatar_name << std::endl;
  //std::cout << vsID << std::endl;
}

void
Person::setHome
(std::string arg_home)
{
}

void
Person::setHome
(GPS_DD arg_home)
{
}

GPS_DD
Person::getHome
(void)
{
  return home;
}

std::string
Person::getVsID()
{
  return this->vsID;
}

std::string
Person::getAvatarName()
{
  return this->avatar_name;
}

bool
Person::operator==
(Person& aPerson)
{
  return ((this->vsID == aPerson.getVsID()) && 
	  (this->avatar_name == aPerson.getAvatarName()));
}

bool
Person::message
(Json::Value myv)
{
  std::cout << "message called\n";
  std::cout << myv["subject"] << std::endl;
  std::cout << myv["body"] << std::endl;
  return true;
}

Json::Value * Person::dumpJ
(void)
{
  Json::Value *result_ptr = new Json::Value();
  (*result_ptr)["avatar_name"] = this->avatar_name;
  (*result_ptr)["vsID"] = this->vsID;
#ifdef _ECS36B_DEBUG_
  std::cout << result_ptr->toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
  return result_ptr;
}

