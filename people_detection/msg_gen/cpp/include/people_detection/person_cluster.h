/* Auto-generated by genmsg_cpp for file /home/doodoros/rosbuild_ws/sandbox/people_detection/msg/person_cluster.msg */
#ifndef PEOPLE_DETECTION_MESSAGE_PERSON_CLUSTER_H
#define PEOPLE_DETECTION_MESSAGE_PERSON_CLUSTER_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace people_detection
{
template <class ContainerAllocator>
struct person_cluster_ {
  typedef person_cluster_<ContainerAllocator> Type;

  person_cluster_()
  : depth(0.0)
  , x(0.0)
  , indicator(0)
  {
  }

  person_cluster_(const ContainerAllocator& _alloc)
  : depth(0.0)
  , x(0.0)
  , indicator(0)
  {
  }

  typedef double _depth_type;
  double depth;

  typedef double _x_type;
  double x;

  typedef uint8_t _indicator_type;
  uint8_t indicator;


  typedef boost::shared_ptr< ::people_detection::person_cluster_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::people_detection::person_cluster_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct person_cluster
typedef  ::people_detection::person_cluster_<std::allocator<void> > person_cluster;

typedef boost::shared_ptr< ::people_detection::person_cluster> person_clusterPtr;
typedef boost::shared_ptr< ::people_detection::person_cluster const> person_clusterConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::people_detection::person_cluster_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::people_detection::person_cluster_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace people_detection

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::people_detection::person_cluster_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::people_detection::person_cluster_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::people_detection::person_cluster_<ContainerAllocator> > {
  static const char* value() 
  {
    return "7ebfa6761596b01a46ac5d45e08fa708";
  }

  static const char* value(const  ::people_detection::person_cluster_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x7ebfa6761596b01aULL;
  static const uint64_t static_value2 = 0x46ac5d45e08fa708ULL;
};

template<class ContainerAllocator>
struct DataType< ::people_detection::person_cluster_<ContainerAllocator> > {
  static const char* value() 
  {
    return "people_detection/person_cluster";
  }

  static const char* value(const  ::people_detection::person_cluster_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::people_detection::person_cluster_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float64 depth\n\
float64 x\n\
uint8 indicator\n\
\n\
";
  }

  static const char* value(const  ::people_detection::person_cluster_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::people_detection::person_cluster_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::people_detection::person_cluster_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.depth);
    stream.next(m.x);
    stream.next(m.indicator);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct person_cluster_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::people_detection::person_cluster_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::people_detection::person_cluster_<ContainerAllocator> & v) 
  {
    s << indent << "depth: ";
    Printer<double>::stream(s, indent + "  ", v.depth);
    s << indent << "x: ";
    Printer<double>::stream(s, indent + "  ", v.x);
    s << indent << "indicator: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.indicator);
  }
};


} // namespace message_operations
} // namespace ros

#endif // PEOPLE_DETECTION_MESSAGE_PERSON_CLUSTER_H

