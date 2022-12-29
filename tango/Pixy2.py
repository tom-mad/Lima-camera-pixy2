import PyTango
from Lima import Core
from Lima import Pixy2 as PixyAcq
from Lima.Server import AttrHelper


class Pixy2(PyTango.Device_4Impl):
    Core.DEB_CLASS(Core.DebModApplication, 'LimaCCDs')

#------------------------------------------------------------------
#    Device constructor
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def __init__(self,*args) :
        PyTango.Device_4Impl.__init__(self,*args)
        self.init_device()

#------------------------------------------------------------------
#    Device destructor
#------------------------------------------------------------------
    def delete_device(self):
        pass

#------------------------------------------------------------------
#    Device initialization
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def init_device(self):
        self.set_state(PyTango.DevState.ON)
        self.get_device_properties(self.get_device_class())


#==================================================================
#
#    Pixy read/write attribute methods
#
#==================================================================
    def __getattr__(self, name):
        return AttrHelper.get_attr_4u(self, name, _PixyCam)


#==================================================================
#
#    PixyClass class definition
#
#==================================================================
class PixyClass(PyTango.DeviceClass):

    class_property_list = {}

    device_property_list = {}

    attr_list = {}

    def __init__(self,name) :
        PyTango.DeviceClass.__init__(self,name)
        self.set_type(name)

#----------------------------------------------------------------------------
# Plugins
#----------------------------------------------------------------------------


_PixyCam = None
_PixyInterface = None

def get_control(**keys) :
    global _PixyCam 
    global _PixyInterface
    
    if _PixyCam is None:
        _PixyCam = PixyAcq.Camera()
        _PixyInterface = PixyAcq.Interface(_PixyCam)

    control = Core.CtControl(_PixyInterface)

    return control

def get_tango_specific_class_n_device():
    return PixyClass,Pixy2
