namespace pixy2
{
  class Interface : HwInterface
  {
%TypeHeaderCode
#include <pixy2/Interface.h>
%End
  public:
    Interface(pixy2::Camera& cam /KeepReference/);
    virtual ~Interface();

    //- From HwInterface
    virtual void	getCapList(std::vector<HwCap> &cap_list /Out/) const;
    virtual void	reset(ResetLevel reset_level);
    virtual void 	prepareAcq();
    virtual void 	startAcq();
    virtual void 	stopAcq();
    virtual void 	getStatus(StatusType& status /Out/);
    virtual int 	getNbHwAcquiredFrames();

  private:
    Interface(const pixy2::Interface&);
  };
};
