#include "main.hpp"
#include <rcl/error_handling.h>

void pub_task(void *param)
{
  while (true)
  {
    // Serial.println("pub_task");
    delay(10);
    if (!rmw_uros_epoch_synchronized()) // 判断时间是否同步
    {
      rmw_uros_sync_session(1000); //  同步时间
      continue;
    }
    connected_agent = true;
    rclc_executor_spin_some(&executor_pub, RCL_MS_TO_NS(100)); // 循环处理数据
  }
  vTaskDelete(NULL);
}

void sub_task(void *param)
{
  while (true)
  {
    // Serial.println("sub_task");
    delay(10);
    rclc_executor_spin_some(&executor_sub, RCL_MS_TO_NS(100));
  }
  vTaskDelete(NULL);
}

void stepper_run(void *param)
{
  while (1)
  {
    if (montor_start)
    {
      myStepper.step(2048);
    }
    else
      myStepper.step(0);
  }
  vTaskDelete(NULL);
}

void setup()
{
  Serial.begin(115200);
  IPAddress agent_ip;                                                  // 设置通过WIFI进行MicroROS通信
  agent_ip.fromString("192.168.31.194");                               // 从字符串获取IP地址
  set_microros_wifi_transports("WHCKKJ", "WHCKKJ456", agent_ip, 8888); // 设置wifi名称，密码，电脑IP,端口号
  // set_microros_serial_transports(Serial);
  delay(2000); // 延时时一段时间，等待设置完成

  sub_node_init();
  delay(2000); // 延时时一段时间，等待设置完成
  pub_node_init();

  pinMode(Trig, OUTPUT);     // 初始化舵机和雷达
  pinMode(Echo, INPUT);      // 要检测引脚上输入的脉冲宽度，需要先设置为输入状态
  servo1.setPeriodHertz(50); // Standard 50hz servo
  servo1.attach(4, 500, 2500);
  servo1.write(90.0);

  init_oled();

  myStepper.setSpeed(350); // 测出
                           // xTaskCreatePinnedToCore(, "stepper_run", 10240, NULL, 1, NULL, 1);
                           // xTaskCreatePinnedToCore(microros_task, "microros_task", 10240, NULL, 1, NULL, 0);

  xTaskCreate(
      stepper_run,   /* Task function. */
      "stepper_run", /* String with name of task. */
      10000,         /* Stack size in bytes. */
      NULL,          /* Parameter passed as input of the task */
      1,             /* Priority of the task. */
      NULL);         /* Task handle. */

  xTaskCreate(
      sub_task,   /* Task function. */
      "sub_task", /* String with name of task. */
      10000,      /* Stack size in bytes. */
      NULL,       /* Parameter passed as input of the task */
      1,          /* Priority of the task. */
      NULL);      /* Task handle. */

  // xTaskCreate(
  //     pub_task,   /* Task function. */
  //     "pub_task", /* String with name of task. */
  //     10000,      /* Stack size in bytes. */
  //     NULL,       /* Parameter passed as input of the task */
  //     1,          /* Priority of the task. */
  //     NULL);      /* Task handle. */
}

void loop()
{

  if (laser_start)
  {
    // if (!connected_agent)
    //   return;

    static float ranges[PCOUNT + 1];
    for (int i = 0; i < int(180 / PCOUNT); i++)
    {
      int64_t start_scan_time = rmw_uros_epoch_millis();
      for (int j = 0; j < PCOUNT; j++)
      {
        int angle = i * 10 + j;
        ranges[j] = get_distance(angle);
      }
      pub_msg.angle_min = float(i * 10) / 180 * PI;       // 结束角度
      pub_msg.angle_max = float(i * (10 + 1)) / 180 * PI; // 结束角度

      int64_t current_time = rmw_uros_epoch_millis();
      pub_msg.scan_time = float(current_time - start_scan_time) * 1e-3;
      pub_msg.time_increment = pub_msg.scan_time / PCOUNT;
      pub_msg.header.stamp.sec = current_time * 1e-3;
      pub_msg.header.stamp.nanosec = current_time - pub_msg.header.stamp.sec * 1000;
      pub_msg.ranges.data = ranges;
      pub_msg.ranges.capacity = PCOUNT;
      pub_msg.ranges.size = PCOUNT;
      if (RCL_RET_OK != rcl_publish(&publisher, &pub_msg, NULL))
      {
        Serial.println("Failed to publish message.");
      }
      else
      {
        Serial.println("Message published successfully.");
      }

      // if receive a stop laser command
      if (laser_start == false)
      {
        servo1.write(90.0);
        return;
      }
    }
  }
}

void laser_task()
{
  // if (!connected_agent)
  //   return;

  static float ranges[PCOUNT + 1];
  while (1)
  {
    for (int i = 0; i < int(180 / PCOUNT); i++)
    {
      int64_t start_scan_time = rmw_uros_epoch_millis();
      for (int j = 0; j < PCOUNT; j++)
      {
        int angle = i * 10 + j;
        ranges[j] = get_distance(angle);
      }
      pub_msg.angle_min = float(i * 10) / 180 * PI;       // 结束角度
      pub_msg.angle_max = float(i * (10 + 1)) / 180 * PI; // 结束角度

      int64_t current_time = rmw_uros_epoch_millis();
      pub_msg.scan_time = float(current_time - start_scan_time) * 1e-3;
      pub_msg.time_increment = pub_msg.scan_time / PCOUNT;
      pub_msg.header.stamp.sec = current_time * 1e-3;
      pub_msg.header.stamp.nanosec = current_time - pub_msg.header.stamp.sec * 1000;
      pub_msg.ranges.data = ranges;
      pub_msg.ranges.capacity = PCOUNT;
      pub_msg.ranges.size = PCOUNT;
      // rcl_publish(&publisher, &pub_msg, NULL);

      if (RCL_RET_OK != rcl_publish(&publisher, &pub_msg, NULL))
      {
        Serial.println("Failed to publish message.");
      }
      else
      {
        Serial.println("Message published successfully.");
      }
    }
  }
}

float get_distance(int angle)
{
  static double mtime;
  servo1.write(angle);     // 移动到指定角度
  delay(25);               // 稳定身形
  digitalWrite(Trig, LOW); // 测量距离
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10); // 产生一个10us的高脉冲去触发SR04
  digitalWrite(Trig, LOW);
  mtime = pulseIn(Echo, HIGH);                  // 检测脉冲宽度，注意返回值是微秒us
  float detect_distance = mtime / 58.0 / 100.0; // 计算出距离,输出的距离的单位是厘米cm
  // Serial.printf("point(%d,%f)\n", angle, detect_distance);

  // oled show distace
  display.clearDisplay();  // 清空屏幕
  display.setCursor(0, 0); // 设置开始显示文字的坐标

  std::string str = "angle: ";
  str += std::to_string(angle);
  display.println(str.c_str());

  str = "distance: ";
  str += std::to_string(detect_distance);
  display.println(str.c_str());
  display.display();

  return detect_distance;
}

void sub_node_init()
{
  allocator_sub = rcl_get_default_allocator();                         // 初始化内存分配器
  rclc_support_init(&support_sub, 0, NULL, &allocator_sub);            // 创建初始化选项
  rclc_node_init_default(&node_sub, "esp32_listen", "", &support_sub); // 创建节点

  // sub init
  rclc_subscription_init_default(
      &subscriber_int,
      &node_sub,
      ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
      "topic_int");

  rclc_subscription_init_default(
      &subscriber_string,
      &node_sub,
      ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
      "topic_string");

  // the 2 is the count of callback functions
  rclc_executor_init(&executor_sub, &support_sub.context, 2, &allocator_sub); // 创建执行器
  rclc_executor_add_subscription(&executor_sub, &subscriber_int, &sub_msg_int, &callback_subscription_int, ON_NEW_DATA);
  rclc_executor_add_subscription(&executor_sub, &subscriber_string, &sub_msg_string, &callback_subscription_string, ON_NEW_DATA);

  sub_msg_string.data = micro_ros_string_utilities_init_with_size(100);
  // memset(test_array, 'z', ARRAY_LEN);
  // sub_msg_string.data.data = (char *)malloc(ARRAY_LEN * sizeof(char));
  sub_msg_string.data.size = 0;
  sub_msg_string.data.capacity = ARRAY_LEN;
}

void pub_node_init()
{
  allocator_pub = rcl_get_default_allocator(); // 初始化内存分配器
  // rclc_support_init(&support_pub, 0, NULL, &allocator_pub); // 创建初始化选项

  rcl_ret_t ret = rclc_support_init(&support_pub, 0, NULL, &allocator_pub);
  if (ret != RCL_RET_OK)
  {
    while (1)
    {
      Serial.print("Failed to initialize support_pub. Error code: ");
      Serial.println(ret);
      const char *error_string = rcl_get_error_string().str;
      if (error_string)
      {
        Serial.print("Error message: ");
        Serial.println(error_string);
        rcl_reset_error();
      }
      delay(1000);
    }
  }

  // rclc_node_init_default(&node_pub, "esp32_pub_laser", "", &support_pub); // 创建节点

  if (RCL_RET_OK != rclc_node_init_default(&node_pub, "esp32_pub_laser", "", &support_pub))
  {
    while (1)
    {

      Serial.println("Failed to rclc_node_init_default");
      delay(100);
    }
  }
  else
  {
    Serial.println("rclc_node_init_default successfully.");
  }

  // publisher init
  // rclc_publisher_init_default( // 发布初始化
  //     &publisher,
  //     &node_pub,
  //     ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, LaserScan),
  //     "/scan");

  if (RCL_RET_OK != rclc_publisher_init_default( // 发布初始化
                        &publisher,
                        &node_pub,
                        ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, LaserScan),
                        "/scan"))
  {
    while (1)
    {

      Serial.println("Failed to rclc_publisher_init_default");
      delay(100);
    }
  }
  else
  {
    Serial.println("rclc_publisher_init_default successfully.");
  }
  // rclc_executor_init(&executor_pub, &support_pub.context, 1, &allocator_pub); // 创建执行器

  // init pub message
  pub_msg.header.frame_id = micro_ros_string_utilities_set(pub_msg.header.frame_id, "laser"); // 初始化消息内容
  pub_msg.angle_increment = 1.0 / 180 * PI;
  pub_msg.range_min = 0.05;
  pub_msg.range_max = 5.0;
}

void init_oled()
{
  Wire.begin(18, 19);
  display = Adafruit_SSD1306(128, 64, &Wire);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // 设置OLED的I2C地址，默认0x3C
  display.clearDisplay();                    // 清空屏幕
  display.setTextSize(2);                    // 设置字体大小，最小为1
  display.setCursor(0, 0);                   // 设置开始显示文字的坐标
  display.setTextColor(SSD1306_WHITE);       // 设置字体颜色
  display.println("hello! f**k u...");       // 输出的字符
  display.display();                         // 必须有
}

void callback_subscription_int(const void *msgin)
{
  // Serial.println("received int");
  const std_msgs__msg__Int32 *msg = (const std_msgs__msg__Int32 *)msgin;
  Serial.println(msg->data);
  display.clearDisplay();              // 清空屏幕
  display.setTextSize(2);              // 设置字体大小，最小为1
  display.setCursor(0, 0);             // 设置开始显示文字的坐标
  display.setTextColor(SSD1306_WHITE); // 设置字体颜色
  display.println(msg->data);          // 输出的字符
  display.display();

  switch (msg->data)
  {
  case COMMAND_TYPE::LASER_START:
    laser_start = 1;
    break;
  case COMMAND_TYPE::LASER_STOP:
    laser_start = 0;
    break;
  case COMMAND_TYPE::MONTOR_START:
    montor_start = 1;
    break;
  case COMMAND_TYPE::MONTOR_STOP:
    montor_start = 0;
    break;
  default:
    break;
  }
}

void callback_subscription_string(const void *msgin)
{
  const std_msgs__msg__String *msg = (const std_msgs__msg__String *)msgin;

  Serial.println("received string");
  std::string res(msg->data.data);

  Serial.println(res.c_str());
  display.clearDisplay();              // 清空屏幕
  display.setTextSize(2);              // 设置字体大小，最小为1
  display.setCursor(0, 0);             // 设置开始显示文字的坐标
  display.setTextColor(SSD1306_WHITE); // 设置字体颜色
  display.println(res.c_str());        // 输出的字符
  display.display();

  if (res == "start laser")
    laser_start = 1;
  else if (res == "stop laser")
    laser_start = 0;
}
