#pragma once

#include <Arduino.h>
#include <micro_ros_platformio.h>
#include <WiFi.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <sensor_msgs/msg/laser_scan.h>
#include <Stepper.h>
#include <micro_ros_utilities/string_utilities.h>
#include <std_msgs/msg/int32.h>
#include <ESP32Servo.h>
#include <Adafruit_GFX.h>     // 加载Adafruit_GFX库
#include <Adafruit_SSD1306.h> // 加载Adafruit_SSD1306库
#include <Wire.h>
#include <std_msgs/msg/string.h>

#include "datatype.hpp"

#define ARRAY_LEN 200

#define PCOUNT 10
#define Trig 27 // 设定SR04连接的Arduino引脚
#define Echo 21

Adafruit_SSD1306 display; // 声明对象

rclc_executor_t executor_sub;
rclc_support_t support_sub;
rcl_allocator_t allocator_sub;
rcl_node_t node_sub;

// sub from qt in pc
rcl_subscription_t subscriber_int;
rcl_subscription_t subscriber_string;

// sub messages from qt in pc
std_msgs__msg__Int32 sub_msg_int;
std_msgs__msg__String sub_msg_string;

// pub to qt in pc
rclc_executor_t executor_pub;
rclc_support_t support_pub;
rcl_allocator_t allocator_pub;
rcl_node_t node_pub;

rcl_publisher_t publisher;
sensor_msgs__msg__LaserScan pub_msg; // pub message to qt

Servo servo1;
bool connected_agent = false;

void callback_subscription_int(const void *msgin);
void init_oled();
void callback_subscription_string(const void *msgin);
void setup();
void loop();

void stepper_run(void *param);

void laser_task();

float get_distance(int angle);

void sub_node_init();
void pub_node_init();

bool laser_start = false;
bool montor_start = false;

Stepper myStepper(100, 32, 22, 33, 23);