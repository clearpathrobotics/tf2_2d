/***************************************************************************
 * Copyright (C) 2017 Locus Robotics. All rights reserved.
 * Unauthorized copying of this file, via any medium, is strictly prohibited
 * Proprietary and confidential
 ***************************************************************************/
#ifndef TF2_2D_TF2_2D_H
#define TF2_2D_TF2_2D_H

#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Transform.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <tf2/convert.h>
#include <tf2/transform_datatypes.h>
#include <tf2/utils.h>
#include <tf2_2d/rotation.h>
#include <tf2_2d/transform.h>
#include <tf2_2d/vector2.h>

#include <cmath>

/**
 * This file contains conversion functions from standard ROS message types to/from the 2D geometry objects. These are
 * designed to work with the tf2 data conversion system: http://wiki.ros.org/tf2/Tutorials/Migration/DataConversions
 */

namespace tf2
{

inline geometry_msgs::Vector3 toMsg(const tf2_2d::Vector2& in)
{
  geometry_msgs::Vector3 msg;
  msg.x = in.x();
  msg.y = in.y();
  msg.z = 0;
  return msg;
}

inline void fromMsg(const geometry_msgs::Vector3& msg, tf2_2d::Vector2& out)
{
  out.setX(msg.x);
  out.setY(msg.y);
}

inline void fromMsg(const geometry_msgs::Point& msg, tf2_2d::Vector2& out)
{
  out.setX(msg.x);
  out.setY(msg.y);
}

inline void fromMsg(const geometry_msgs::Point32& msg, tf2_2d::Vector2& out)
{
  out.setX(msg.x);
  out.setY(msg.y);
}

inline geometry_msgs::Vector3Stamped toMsg(const tf2::Stamped<tf2_2d::Vector2>& in)
{
  geometry_msgs::Vector3Stamped msg;
  msg.header.stamp = in.stamp_;
  msg.header.frame_id = in.frame_id_;
  msg.vector = toMsg(static_cast<const tf2_2d::Vector2&>(in));
  return msg;
}

inline void fromMsg(const geometry_msgs::Vector3Stamped& msg, tf2::Stamped<tf2_2d::Vector2>& out)
{
  out.stamp_ = msg.header.stamp;
  out.frame_id_ = msg.header.frame_id;
  fromMsg(msg.vector, static_cast<tf2_2d::Vector2&>(out));
}

inline void fromMsg(const geometry_msgs::PointStamped& msg, tf2::Stamped<tf2_2d::Vector2>& out)
{
  out.stamp_ = msg.header.stamp;
  out.frame_id_ = msg.header.frame_id;
  fromMsg(msg.point, static_cast<tf2_2d::Vector2&>(out));
}

inline geometry_msgs::Quaternion toMsg(const tf2_2d::Rotation& in)
{
  geometry_msgs::Quaternion msg;
  msg.x = 0;
  msg.y = 0;
  msg.z = std::sin(0.5 * in.angle());
  msg.w = std::cos(0.5 * in.angle());
  return msg;
}

inline void fromMsg(const geometry_msgs::Quaternion& msg, tf2_2d::Rotation& out)
{
  out.setAngle(tf2::getYaw(msg));
}

inline geometry_msgs::QuaternionStamped toMsg(const tf2::Stamped<tf2_2d::Rotation>& in)
{
  geometry_msgs::QuaternionStamped msg;
  msg.header.stamp = in.stamp_;
  msg.header.frame_id = in.frame_id_;
  msg.quaternion = toMsg(static_cast<const tf2_2d::Rotation&>(in));
  return msg;
}

inline void fromMsg(const geometry_msgs::QuaternionStamped& msg, tf2::Stamped<tf2_2d::Rotation>& out)
{
  out.stamp_ = msg.header.stamp;
  out.frame_id_ = msg.header.frame_id;
  fromMsg(msg.quaternion, static_cast<tf2_2d::Rotation&>(out));
}

inline geometry_msgs::Transform toMsg(const tf2_2d::Transform& in)
{
  geometry_msgs::Transform msg;
  msg.translation = toMsg(in.translation());
  msg.rotation = toMsg(in.rotation());
  return msg;
}

inline void fromMsg(const geometry_msgs::Transform& msg, tf2_2d::Transform& out)
{
  tf2_2d::Rotation rotation;
  fromMsg(msg.rotation, rotation);
  out.setRotation(rotation);
  tf2_2d::Vector2 translation;
  fromMsg(msg.translation, translation);
  out.setTranslation(translation);
}

inline void fromMsg(const geometry_msgs::Pose& msg, tf2_2d::Transform& out)
{
  tf2_2d::Rotation rotation;
  fromMsg(msg.orientation, rotation);
  out.setRotation(rotation);
  tf2_2d::Vector2 translation;
  fromMsg(msg.position, translation);
  out.setTranslation(translation);
}

inline void fromMsg(const geometry_msgs::Pose2D& msg, tf2_2d::Transform& out)
{
  out.setAngle(msg.theta);
  out.setX(msg.x);
  out.setY(msg.y);
}

inline geometry_msgs::TransformStamped toMsg(const tf2::Stamped<tf2_2d::Transform>& in)
{
  geometry_msgs::TransformStamped msg;
  msg.header.stamp = in.stamp_;
  msg.header.frame_id = in.frame_id_;
  msg.transform = toMsg(static_cast<const tf2_2d::Transform&>(in));
  return msg;
}

inline void fromMsg(const geometry_msgs::TransformStamped& msg, tf2::Stamped<tf2_2d::Transform>& out)
{
  out.stamp_ = msg.header.stamp;
  out.frame_id_ = msg.header.frame_id;
  fromMsg(msg.transform, static_cast<tf2_2d::Transform&>(out));
}

inline void fromMsg(const geometry_msgs::PoseStamped& msg, tf2::Stamped<tf2_2d::Transform>& out)
{
  out.stamp_ = msg.header.stamp;
  out.frame_id_ = msg.header.frame_id;
  fromMsg(msg.pose, static_cast<tf2_2d::Transform&>(out));
}

}  // namespace tf2

#endif  // TF2_2D_TF2_2D_H
