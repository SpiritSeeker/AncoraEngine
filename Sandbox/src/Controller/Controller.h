#pragma once

#include <Ancora.h>

struct ControllerProps
{
  std::string ControllerAddress = "192.168.29.200";
  uint32_t ControllerPort = 8347;
};

struct ControllerData
{
  double Data;
};

class Controller
{
public:
  Controller(const ControllerProps& controllerProps);
  ~Controller();

  void Init();
  const ControllerData& GetData() { return m_ControllerData; }

  static Ancora::Ref<Controller> Create(const ControllerProps& controllerProps = ControllerProps());
private:
  void DataCollectionThread();
private:
  ControllerProps m_Props;
  Ancora::Ref<Ancora::SocketClient> m_Controller;
  ControllerData m_ControllerData;
  std::thread t_DataThread;
  bool m_Running;
};
