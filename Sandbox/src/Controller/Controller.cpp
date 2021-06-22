#include "Controller.h"

Controller::Controller(const ControllerProps& controllerProps)
  : m_Props(controllerProps)
{
  Init();
  m_Running = true;
  t_DataThread = std::thread(&Controller::DataCollectionThread, this);
}

Controller::~Controller()
{
  m_Running = false;
  t_DataThread.join();
}

void Controller::Init()
{
  Ancora::SocketClientProps props = Ancora::SocketClientProps();
  props.Port = m_Props.ControllerPort;
  m_Controller = Ancora::SocketClient::Create(props);

  m_Controller->Connect(m_Props.ControllerAddress);
}

void Controller::DataCollectionThread()
{
  while (m_Running)
  {
    m_Controller->Send("g");
    std::string data;
    data = m_Controller->Read();
    m_ControllerData.Data = std::stod(data);
  }
}

Ancora::Ref<Controller> Controller::Create(const ControllerProps& controllerProps)
{
  return Ancora::CreateRef<Controller>(controllerProps);
}
