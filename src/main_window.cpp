#include  <ros/ros.h>

//C++
#include <string>
#include <sstream>
#include <vector>


#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include <stdlib.h>
#include "../include/jaka_jog_panel/main_window.hpp"
#include "ui_main_window.h"

#include  <sensor_msgs/JointState.h>
#include <thread>


#include <fstream>

#include "libs/robot.h"
//#include "libs/conversion.h"

namespace Jaka_jog_panel
{

using namespace Qt;

  MainWindow::MainWindow(int argc, char** argv, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  {
    ui->setupUi(this);

    //joints.data[0] = 0;
    joints.data.resize(6);

    /*model = new QStandardItemModel();
    ui->tableView->setModel(model);
    model->setItem("0");*/

    //init joint text
    ui->lb_joint1->setText(QString::number(joints.data[0], 'f', 6));
    ui->lb_joint2->setText(QString::number(joints.data[1], 'f', 6));
    ui->lb_joint3->setText(QString::number(joints.data[2], 'f', 6));
    ui->lb_joint4->setText(QString::number(joints.data[3], 'f', 6));
    ui->lb_joint5->setText(QString::number(joints.data[4], 'f', 6));
    ui->lb_joint6->setText(QString::number(joints.data[5], 'f', 6));

    //init joint slider
    ui->joint1Slider->setMinimum(-4712389);
    ui->joint1Slider->setMaximum(4712389);
    //ui->joint1Slider->setVisible(false);
    //ui->joint1Slider->setSingleStep(1);

    ui->joint2Slider->setMinimum(-1483530);
    ui->joint2Slider->setMaximum(4625122);

    ui->joint3Slider->setMinimum(-3054326);
    ui->joint3Slider->setMaximum(3054326);

    ui->joint4Slider->setMinimum(-1483530);
    ui->joint4Slider->setMaximum(4625122);

    ui->joint5Slider->setMinimum(-4712389);
    ui->joint5Slider->setMaximum(4712389);

    ui->joint6Slider->setMinimum(-4712389);
    ui->joint6Slider->setMaximum(4712389);

   // ui->joint1Slider->setMovable(false);


    jTimer=new QTimer(this);
    jTimer->stop();
    jTimer->setInterval(Update_Timer) ;//设置定时周期，单位：毫秒
    connect(jTimer,SIGNAL(timeout()),this,SLOT(timer_timeout()));
    jTimer->start();

    MainWindow::Jog_Ros_Init(argc, argv);
    /*ros::init(argc, argv, "jaka_jog_panel");

    ros::NodeHandle nh;
    jog_command_pub = nh.advertise<sensor_msgs::JointState>("robot_jog_command", 10);*/
    //jog_command_pub.publish(joint_states);
    //MainWindow::Jog_Command_Callback(jog_command_pub);

    /*rosTimer=new QTimer(this);
    rosTimer->stop();
    rosTimer->setInterval(ros_Timer) ;//设置定时周期，单位：毫秒
    connect(rosTimer,SIGNAL(timeout()),this,SLOT(Jog_Command_Callback()));

    //connect(ui->joint1Slider, SIGNAL(on_joint1Slider_valueChanged(float)), ui->lb_joint1, SLOT(setValue(float)));
    //connect(ui->lb_joint1, SLOT(setText(QString::number(joints.data[0], 'f', 6))), ui->joint1Slider, SIGNAL(setValue(float)));
    //this->ui->tableView->setColumnWidth(0, 100);
    rosTimer->start();*/
  }

  MainWindow::~MainWindow()
  {
    delete ui;
  }

  void MainWindow::jointStateCallback(const sensor_msgs::JointState::ConstPtr& msg)
  {
    //get joint position
    nowJointpose[0] = msg->position[0];
    nowJointpose[1] = msg->position[1];
    nowJointpose[2] = msg->position[2];
    nowJointpose[3] = msg->position[3];
    nowJointpose[4] = msg->position[4];
    nowJointpose[5] = msg->position[5];
  }

  //press button
  void MainWindow::on_joint1Left_pressed()
  {
    joints.data[0] -= 0.1;
    joints.data[0] = joints.data[0] < -4.7123889 ? -4.7123889 : joints.data[0];
    ui->joint1Slider->setValue(joints.data[0]*1000000);

    if(Real_Robot_Flag)
      robot.jog(0, CONTINUE, COORD_JOINT, -0.2, 10);
    //jog_command_pub.publish(joint_states);
    //MainWindow::Jog_Command_Callback(jog_command_pub);
  }
  void MainWindow::on_joint1Left_released()
  {
    if(Real_Robot_Flag)
      robot.jog_stop(-1);
  }

  void MainWindow::on_joint1Right_pressed()
  {
    joints.data[0] += 0.1;
    joints.data[0] = joints.data[0] > 4.7123889 ? 4.7123889 : joints.data[0];
    ui->joint1Slider->setValue(joints.data[0]*1000000);

    if(Real_Robot_Flag)
      robot.jog(0, CONTINUE, COORD_JOINT, 0.2, 10);
  }
  void MainWindow::on_joint1Right_released()
  {
    if(Real_Robot_Flag)
      robot.jog_stop(-1);
  }

  void MainWindow::on_joint2Left_pressed()
  {
    joints.data[1] -= 0.1;
    joints.data[1] = joints.data[1] < -1.483530 ? -1.483530 : joints.data[1];
    ui->joint2Slider->setValue(joints.data[1]*1000000);

    if(Real_Robot_Flag)
      robot.jog(1, CONTINUE, COORD_JOINT, -0.2, 10);
  }
  void MainWindow::on_joint2Left_released()
  {
    if(Real_Robot_Flag)
      robot.jog_stop(-1);
  }

  void MainWindow::on_joint2Right_pressed()
  {
    joints.data[1] += 0.1;
    joints.data[1] = joints.data[1] > 4.625122 ? 4.625122 : joints.data[1];
    ui->joint2Slider->setValue(joints.data[1]*1000000);

    if(Real_Robot_Flag)
      robot.jog(1, CONTINUE, COORD_JOINT, 0.2, 10);
  }
  void MainWindow::on_joint2Right_released()
  {
    if(Real_Robot_Flag)
      robot.jog_stop(-1);
  }

  void MainWindow::on_joint3Left_pressed()
  {
    joints.data[2] -= 0.1;
    joints.data[2] = joints.data[2] < -3.054326 ? -3.054326 : joints.data[2];
    ui->joint3Slider->setValue(joints.data[2]*1000000);

    if(Real_Robot_Flag)
      robot.jog(2, CONTINUE, COORD_JOINT, -0.2, 10);
  }
  void MainWindow::on_joint3Left_released()
  {
    if(Real_Robot_Flag)
      robot.jog_stop(-1);
  }

  void MainWindow::on_joint3Right_pressed()
  {
    joints.data[2] += 0.1;
    joints.data[2] = joints.data[2] > 3.054326 ? 3.054326 : joints.data[2];
    ui->joint3Slider->setValue(joints.data[2]*1000000);

    if(Real_Robot_Flag)
      robot.jog(2, CONTINUE, COORD_JOINT, 0.2, 10);
  }
  void MainWindow::on_joint3Right_released()
  {
    if(Real_Robot_Flag)
      robot.jog_stop(-1);
  }

  void MainWindow::on_joint4Left_pressed()
  {
    joints.data[3] -= 0.1;
    joints.data[3] = joints.data[3] < -1.483530 ? -1.483530 : joints.data[3];
    ui->joint4Slider->setValue(joints.data[3]*1000000);

    if(Real_Robot_Flag)
      robot.jog(3, CONTINUE, COORD_JOINT, -0.2, 10);
  }
  void MainWindow::on_joint4Left_released()
  {
    if(Real_Robot_Flag)
      robot.jog_stop(-1);
  }

  void MainWindow::on_joint4Right_pressed()
  {
    joints.data[3] += 0.1;
    joints.data[3] = joints.data[3] > 4.625122 ? 4.625122 : joints.data[3];
    ui->joint4Slider->setValue(joints.data[3]*1000000);

    if(Real_Robot_Flag)
      robot.jog(3, CONTINUE, COORD_JOINT, 0.2, 10);
  }
  void MainWindow::on_joint4Right_released()
  {
    if(Real_Robot_Flag)
      robot.jog_stop(-1);
  }

  void MainWindow::on_joint5Left_pressed()
  {
    joints.data[4] -= 0.1;
    joints.data[4] = joints.data[4] < -4.712389 ? -4.712389 : joints.data[4];
    ui->joint5Slider->setValue(joints.data[4]*1000000);

    if(Real_Robot_Flag)
      robot.jog(4, CONTINUE, COORD_JOINT, -0.2, 10);
  }
  void MainWindow::on_joint5Left_released()
  {
    if(Real_Robot_Flag)
      robot.jog_stop(-1);
  }

  void MainWindow::on_joint5Right_pressed()
  {
    joints.data[4] += 0.1;
    joints.data[4] = joints.data[4] > 4.7123889 ? 4.7123889 : joints.data[4];
    ui->joint5Slider->setValue(joints.data[4]*1000000);

    if(Real_Robot_Flag)
      robot.jog(4, CONTINUE, COORD_JOINT, 0.2, 10);
  }
  void MainWindow::on_joint5Right_released()
  {
    if(Real_Robot_Flag)
      robot.jog_stop(-1);
  }

  void MainWindow::on_joint6Left_pressed()
  {
    joints.data[5] -= 0.1;
    joints.data[5] = joints.data[5] < -4.7123896 ? -4.712389 : joints.data[5];
    ui->joint6Slider->setValue(joints.data[5]*1000000);

    if(Real_Robot_Flag)
      robot.jog(5, CONTINUE, COORD_JOINT, -0.2, 10);
  }
  void MainWindow::on_joint6Left_released()
  {
    if(Real_Robot_Flag)
      robot.jog_stop(-1);
  }


  void MainWindow::on_joint6Right_pressed()
  {
    joints.data[5] += 0.1;
    joints.data[5] = joints.data[5] > 4.7123889 ? 4.7123889 : joints.data[5];
    ui->joint6Slider->setValue(joints.data[5]*1000000);

    if(Real_Robot_Flag)
      robot.jog(5, CONTINUE, COORD_JOINT, 0.2, 10);
  }
  void MainWindow::on_joint6Right_released()
  {
    //std::cout<<"Jog Stop"<<std::endl;
    if(Real_Robot_Flag)
      robot.jog_stop(-1);
  }


  //slider change
  void MainWindow::on_joint1Slider_valueChanged(int value)
  {
    if(Real_Robot_Flag)
      ui->joint1Slider->setValue(joints.data[0]*1000000);
    else
      joints.data[0] = (float)ui->joint1Slider->value()/1000000;
  }

  void MainWindow::on_joint2Slider_valueChanged(int value)
  {
    if(Real_Robot_Flag)
      ui->joint2Slider->setValue(joints.data[1]*1000000);
    else
      joints.data[1] = (float)ui->joint2Slider->value()/1000000;
  }

  void MainWindow::on_joint3Slider_valueChanged(int value)
  {
    if(Real_Robot_Flag)
      ui->joint3Slider->setValue(joints.data[2]*1000000);
    else
      joints.data[2] = (float)ui->joint3Slider->value()/1000000;
  }

  void MainWindow::on_joint4Slider_valueChanged(int value)
  {
    if(Real_Robot_Flag)
      ui->joint4Slider->setValue(joints.data[3]*1000000);
    else
      joints.data[3] = (float)ui->joint4Slider->value()/1000000;
  }

  void MainWindow::on_joint5Slider_valueChanged(int value)
  {
    if(Real_Robot_Flag)
      ui->joint5Slider->setValue(joints.data[4]*1000000);
    else
      joints.data[4] = (float)ui->joint5Slider->value()/1000000;
  }

  void MainWindow::on_joint6Slider_valueChanged(int value)
  {
    if(Real_Robot_Flag)
      ui->joint6Slider->setValue(joints.data[5]*1000000);
    else
      joints.data[5] = (float)ui->joint6Slider->value()/1000000;
  }

  //Timer Callback
  void MainWindow::timer_timeout()
  {
    if(Real_Robot_Flag)
    {
      //JointValue joint_pose;

      robot.get_joint_position(&joint_pose);

      ui->lb_joint1->setText(QString::number(joint_pose.jVal[0] * 180 / PI, 'f', 6));
      ui->lb_joint2->setText(QString::number(joint_pose.jVal[1] * 180 / PI, 'f', 6));
      ui->lb_joint3->setText(QString::number(joint_pose.jVal[2] * 180 / PI, 'f', 6));
      ui->lb_joint4->setText(QString::number(joint_pose.jVal[3] * 180 / PI, 'f', 6));
      ui->lb_joint5->setText(QString::number(joint_pose.jVal[4] * 180 / PI, 'f', 6));
      ui->lb_joint6->setText(QString::number(joint_pose.jVal[5] * 180 / PI, 'f', 6));

      MainWindow::Jog_Command_Callback(jog_command_pub);
    }

    else
    {
      ui->lb_joint1->setText(QString::number(joints.data[0] * 180 / PI, 'f', 6));
      ui->lb_joint2->setText(QString::number(joints.data[1] * 180 / PI, 'f', 6));
      ui->lb_joint3->setText(QString::number(joints.data[2] * 180 / PI, 'f', 6));
      ui->lb_joint4->setText(QString::number(joints.data[3] * 180 / PI, 'f', 6));
      ui->lb_joint5->setText(QString::number(joints.data[4] * 180 / PI, 'f', 6));
      ui->lb_joint6->setText(QString::number(joints.data[5] * 180 / PI, 'f', 6));

      MainWindow::Jog_Command_Callback(jog_command_pub);
    }

    //MainWindow::Jog_Command_Callback(jog_command_pub);
  }



  void MainWindow::Jog_Ros_Init(int argc, char **argv)
  {
    ros::init(argc, argv, "jaka_jog_panel");
    ros::NodeHandle nh;

    jog_command_pub = nh.advertise<sensor_msgs::JointState>("robot_jog_command", 10);//cmd publisher

  }

  //void MainWindow::Jog_Command_Callback(ros::Publisher joint_states_pub)
  void MainWindow::Jog_Command_Callback(ros::Publisher &Publish)
  {

    //JointValue joint_pose;
    sensor_msgs::JointState joint_states;

    joint_states.position.clear(); // clear position vector

    if(Real_Robot_Flag)
    {
      for(int i = 0; i < 6; i++)
      {
        joint_states.position.push_back(joint_pose.jVal[i]);
        int j = i+1;
        joint_states.name.push_back("joint_"+ std::to_string(j));
        joint_states.header.stamp = ros::Time::now();
      }
    }
    else
    {
      for(int i = 0; i < 6; i++)
      {
        joint_states.position.push_back(joints.data[i]);
        int j = i+1;
        joint_states.name.push_back("joint_"+ std::to_string(j));
        joint_states.header.stamp = ros::Time::now();
      }
    }


    Publish.publish(joint_states); // publish data
    //std::cout << "jog" << std::endl;
  }

  //robot connect
  void MainWindow::on_connect_button_pressed()
  {
    if(!robot.login_in(RobotIP.c_str()))
      if(!robot.power_on())
        if(!robot.enable_robot())
        {
          std::cout<<"Robot Connect"<<std::endl;
          Real_Robot_Flag = true;
        }
  }

  void MainWindow::on_disconnect_button_pressed()
  {
    robot.disable_robot();
    robot.power_off();
    robot.login_out();
    Real_Robot_Flag = false;
    std::cout<<"Robot Disconnect"<<std::endl;
  }

  void MainWindow::on_lineEdit_textChanged(const QString &arg1)
  {
    //robotIP = arg1.toStdString();
    //cout << robotIP << endl;
    RobotIP = arg1.toStdString();
    //printf("%s", RobotIP);

    //QByteArray IP = arg1.toLatin1();
    //RobotIP = IP.data();
    //RobotIP = arg1.toLocal8Bit();
    //std::cout << robotIP << std::endl;
    //RobotIP = "192.168.0.0";
    //std::cout << typeid(RobotIP).name() << std::endl;
    //std::cout << RobotIP << std::endl;
  }




  //new
  //直线运动按钮 只有当为非阻塞(FALSE)的时候能用停止按钮
  void MainWindow::on_line_moveButton_clicked()
  {
      CartesianPose cart;
      cart.tran.x = ui->input_x_edit->text().toDouble();
      cart.tran.y = ui->input_y_edit->text().toDouble();
      cart.tran.z = ui->input_z_edit->text().toDouble();
      cart.rpy.rx = (ui->input_rx_edit->text().toDouble()) * PI /180;
      cart.rpy.ry = (ui->input_ry_edit->text().toDouble()) * PI /180;
      cart.rpy.rz = (ui->input_rz_edit->text().toDouble())* PI /180;

     int ret =  robot.linear_move(&cart, ABS, FALSE, 10);
     if(ret==0){
         ui->display->append("ok");
     }else{
         ui->display->append("erro");
     }
  }
  //停止运动按钮
  void MainWindow::on_motion_stop_clicked()
   {
       if(Real_Robot_Flag)
         robot.motion_abort();
   }




  //new2
  //打开文件
   void MainWindow::process_line(QByteArray line,int& sum,int& count)

  {
        QString line_copy = line;
        CartesianPose Cart;
        line_copy.remove('[');
        line_copy.remove(']');
        QStringList strList = line_copy.split(',');
        if (strList.size() == 6) {
             Cart.tran.x = strList[0].toDouble();
             Cart.tran.y = strList[1].toDouble();
             Cart.tran.z = strList[2].toDouble();
             Cart.rpy.rx = strList[3].toDouble()* PI /180;
            Cart.rpy.ry = strList[4].toDouble()* PI /180;
            Cart.rpy.rz = strList[5].toDouble()* PI /180;
             int ret =  robot.linear_move(&Cart, ABS, TRUE, 5);
              if(ret==0){
                  ui->display_2->append("成功移动到："+line);
                   count ++;
                   sum++;
                }
            }
              else{
                  ui->display_2->append("不合法的点"+line);
                  sum++;
            }

      
  }




 //连接ip  作为客户端
  void MainWindow::on_connect_IP_clicked()
  {          QList<QByteArray> receivedDataList;
             QTcpSocket* socket = new QTcpSocket(this);
                // 连接到特定的IP和端口
             QString ip_input = ui->input_IP->text();
             QString port_input = ui->input_port->text();
             socket->connectToHost(QHostAddress(ip_input), port_input.toShort());
             // 定义一个 QByteArray 对象用于存储消息
             QByteArray messageData;
             // 监听 socket 的 readyRead 信号，当有数据可读时触发
             connect(socket, &QTcpSocket::connected, this,[this]{
                 ui->display_2->setText("connected");
                });
             connect(socket, &QTcpSocket::readyRead, this, [=](){
                  QByteArray data = socket->readAll();
                  ui->display_2->append("正在处理："+QString::fromUtf8(data));
                  CartesianPose Cart = extractDoublesFromByteArray(data);
                  int ret  =  robot.linear_move(&Cart, ABS, TRUE, 5);
                   if(ret==0){
                    ui->display_2->setText("成功移动到："+QString::fromUtf8(data));
                    }

                  else{
                      ui->display_2->setText("不合法的点"+QString::fromUtf8(data));
                  }

             });
                // 监听 socket 的 disconnected 信号，当连接断开时触发
             connect(socket, &QTcpSocket::disconnected, this, [this,socket, &messageData]() {
                    // 关闭连接
                    ui->display_2->setText("disconnected");
                    socket->close();
                    socket->deleteLater();
                });
         }




//ByteArrayToDoubles
CartesianPose MainWindow::extractDoublesFromByteArray(const QByteArray &byteArray) {
   QString str  =  QString::fromUtf8(byteArray);
   ui->display_2->append(str);
   str.remove('[');
   str.remove(']');
   QStringList strList = str.split(',');
   CartesianPose Cart;
   if (strList.size() == 6) {
       Cart.tran.x = strList[0].toDouble();
       Cart.tran.y = strList[1].toDouble();
       Cart.tran.z = strList[2].toDouble();
       Cart.rpy.rx = strList[3].toDouble()* PI /180;
       Cart.rpy.ry = strList[4].toDouble()* PI /180;
       Cart.rpy.rz = strList[5].toDouble()* PI /180;
    return Cart;
   }
}




//
// void MainWindow::on_openfile_clicked()
// {
//     QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"),
//                                                     "/home",
//                                                     "*.txt");
//     if (fileName.isEmpty()) {
//         QMessageBox::warning(this, "警告", "请打开一个txt文件");
//         return;
//     }

//     // 创建一个新线程，并将文件名传递给线程函数
//     std::thread fileThread(&MainWindow::processFileInThread, this, fileName.toStdString());
//     fileThread.detach(); // 分离线程，允许它在后台运行
// }

// void MainWindow::processFileInThread(const std::string& fileName)
// {
//     std::ifstream file(fileName);
//     if (!file.is_open()) {
//         // 文件打开失败，处理错误（这里可以更新GUI显示错误信息）
//         return;
//     }

//     int count = 0;
//     std::string line;
//     while (std::getline(file, line)) {
//         // 在这里处理每行的内容，你可以根据需要进行具体的处理
//         // ...

//         count++;
//     }
//     file.close();

//     // 文件处理完成后，可以更新GUI显示结果
//     // ...
// }
void MainWindow::on_openfile_clicked()
{  QString filename = ui->input_filename->text();
   QFile* readFile=new QFile(filename);
      if (!readFile->open(QIODevice::ReadOnly | QIODevice::Text)){
          ROS_INFO("erro to open");
      }
        int sum = 0;
        int count = 0;
      while (!readFile->atEnd()) {

          QByteArray line = readFile->readLine();
          process_line(line,sum,count);
      }
      ui->display_2->append("总点数："+QString::number(sum));
      ui->display_2->append("成功处理点数："+QString::number(count));
  ROS_INFO("1");

    return;
}










//test
  void MainWindow::on_test_clicked()
  {
//      CartesianPose cart;
//      cart.tran.x = 300; cart.tran.y = 300; cart.tran.z = 100;
//      cart.rpy.rx = 180 * PI / 180; cart.rpy.ry = 0 * PI / 180; cart.rpy.rz = 0 * PI / 180;
//      //笛卡尔空间运动，其中 ABS 代表绝对运动， FALSE 代表指令是非阻塞的， 10 代表速度为 10mm/s
//      printf("rx=%f , ry=%f, rz=%f\n", cart.rpy.rx, cart.rpy.ry, cart.rpy.rz);
//      robot.linear_move(&cart, ABS, FALSE, 200, 10 ,1,NULL);

//      cart.tran.x = 150; cart.tran.y = 300;
//      //笛卡尔空间扩展运动，其中 ABS 代表绝对运动， FALSE 代表指令是非阻塞的， 20 代表最大速度为20mm/s ,10 代表加速度为 10mm/s2,5 代表圆弧过度半径为 5mm
//      demo.linear_move(&cart, ABS, FALSE, 20, 10, 5, NULL);
//      cart.tran.x = 150; cart.tran.y = 250;
//      demo.linear_move(&cart, ABS, FALSE, 20, 10, 5, NULL);
//      cart.tran.x = 225; cart.tran.y = 250;
//      demo.linear_move(&cart, ABS, FALSE, 20, 10, 5, NULL);
//      cart.tran.x = 300; cart.tran.y = 250;
//      demo.linear_move(&cart, ABS, FALSE, 20, 10, 5, NULL);
//      cart.tran.x = 300; cart.tran.y = 300;
//      demo.linear_move(&cart, ABS, FALSE, 20, 10, 5, NULL);
//      Sleep(3000);
//      }
      //预期是过一会出现0
      int ret;
      CartesianPose cart;
      cart.tran.x = 250; cart.tran.y = -250; cart.tran.z = 400;
      cart.rpy.rx = 180 * PI / 180; cart.rpy.ry = 40 * PI / 180; cart.rpy.rz = 130 * PI / 180;
      if(Real_Robot_Flag){
          ret = robot.linear_move(&cart,ABS,TRUE,10,5,0,NULL);
      }
      ui->display_2->setText("1111");
      ui->display_2->setText(QString::number(ret));


  }


  //预期立即出现100
  void MainWindow::on_test_2_clicked()
  {
      int ret;
      CartesianPose cart;
      cart.tran.x = 250; cart.tran.y = -250; cart.tran.z = 400;
      cart.rpy.rx = 180 * PI / 180; cart.rpy.ry = 40 * PI / 180; cart.rpy.rz = 130 * PI / 180;
      if(Real_Robot_Flag){
          ret = robot.linear_move(&cart,ABS,FALSE,20,10,0,NULL);
          cart.tran.x = 200;
          CartesianPose tcp_pos;
          robot.get_tcp_position(&tcp_pos);
          std::cout << "tcp_pos is :\n x: " << tcp_pos.tran.x << " y: " << tcp_pos.tran.y << "z: " << tcp_pos.tran.z << std::endl;
          std::cout << "rx: " << tcp_pos.rpy.rx << " ry: " << tcp_pos.rpy.ry << " rz: " << tcp_pos.rpy.rz << std::endl;
          robot.linear_move(&cart,ABS,FALSE,20,10,0,NULL);
      }
      ui->display_2->setText("1111");
      ui->display_2->setText(QString::number(ret+100));

  }






}

//int main(int argc, char *argv[])
//{
//
//    return 0;
//}
/*int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Jakajogpanel::QMainWindow w;
    w.show();

    return a.exec();
}*/

//#include <pluginlib/class_list_macros.h>
//PLUGINLIB_EXPORT_CLASS(Jaka_jog_panel::MainWindow,rviz::Panel)



















