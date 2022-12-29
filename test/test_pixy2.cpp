#include "pixy2/Interface.h"
#include "pixy2/Camera.h"
#include "lima/CtTestApp.h"

DEB_GLOBAL(DebModTest);

using namespace lima;
using namespace lima::pixy2;

class TestApp : public CtTestApp
{
    DEB_CLASS_NAMESPC(DebModTest, "TestApp", "Simulator");

  public:
    class Pars : public CtTestApp::Pars
    {
      DEB_CLASS_NAMESPC(DebModTest, "TestApp::Pars", "Simulator");
    public:
      Pars();
    };

    TestApp(int argc, char *argv[]) : CtTestApp(argc, argv) {}

  protected:
    virtual CtTestApp::Pars *getPars();
    virtual CtControl *getCtControl();
    virtual index_map getIndexMap() { return {}; }
    virtual void configureAcq(const index_map& indexes);

    AutoPtr<Pars> m_pars;
    AutoPtr<Camera> m_cam;
    AutoPtr<HwInterface> m_interface;
    AutoPtr<CtControl> m_ct;
};

TestApp::Pars::Pars()
{
  DEB_CONSTRUCTOR();

  // TODO: Add options
  //m_opt_list.insert(MakeOpt(cam_mode, "", "--option", "description"));

}

CtTestApp::Pars *TestApp::getPars()
{
  m_pars = new Pars();
  return m_pars;
}

CtControl *TestApp::getCtControl()
{
  DEB_MEMBER_FUNCT();

  m_cam = new Camera();
  m_interface = new Interface(*m_cam);
  m_ct = new CtControl(m_interface);
  return m_ct;
}

void TestApp::configureAcq(const index_map& indexes)
{
  DEB_MEMBER_FUNCT();

}


int main(int argc, char *argv[])
{
  DEB_GLOBAL_FUNCT();

  try {
    TestApp app(argc, argv);
    app.run();
  } catch (Exception& e) {
    DEB_ERROR() << "LIMA Exception:" << e.getErrMsg();
  }
  
  return 0;
}
