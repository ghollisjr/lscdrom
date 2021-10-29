#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/cdrom.h>
#include <Options.hh>
#include <string>
#include <iostream>
#include <climits>

typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

int main(int argc, char** argv) {
  //argument parsing
  OptionSpec options;
  options.AddOption('d',"device",required_argument,"drive block device path");
  options.AddOption('h',"help",no_argument,"show this help message");
  options.AddOption('v',"verbose",no_argument,"print more info");
  Flags flags;
  std::vector<std::string> leftovers;
  parseargs(argc,argv,options,flags,leftovers);
  if(flags.Check('h')) {
    std::cerr << "Usage: lscdrom [options]" << std::endl << std::endl;
    std::cerr << options.GetOptionDesc() << std::endl << std::endl;
    std::cerr << "Status values:" << std::endl;
    std::cerr << "CDS_NO_INFO" << std::endl;
    std::cerr << "CDS_NO_DISC" << std::endl;
    std::cerr << "CDS_TRAY_OPEN" << std::endl;
    std::cerr << "CDS_DRIVE_NOT_READY" << std::endl;
    std::cerr << "CDS_DISC_OK" << std::endl;
    return 1;
  }
  bool verbose = flags.Check('v');
  std::vector<std::string> devicepaths;
  flags.GetArgs('d',devicepaths);
  std::string devicepath = "/dev/cdrom";
  if(devicepaths.size()) {
    devicepath = devicepaths[devicepaths.size()-1];
  }

  //device query
  int fd = open(devicepath.c_str(),O_RDONLY);
  int status = ioctl(fd,CDROM_DRIVE_STATUS, CDSL_NONE);
  close(fd);
  if(verbose) {
    std::cout << "Device: " << devicepath << std::endl;
  }

  switch(status) {
  case CDS_NO_INFO:
    std::cout << "CDS_NO_INFO" << std::endl;
    break;
  case CDS_NO_DISC:
    std::cout << "CDS_NO_DISC" << std::endl;
    break;
  case CDS_TRAY_OPEN:
    std::cout << "CDS_TRAY_OPEN" << std::endl;
    break;
  case CDS_DRIVE_NOT_READY:
    std::cout << "CDS_DRIVE_NOT_READY" << std::endl;
    break;
  case CDS_DISC_OK:
    std::cout << "CDS_DISC_OK" << std::endl;
    break;
  default: break;
  }
  return 0;
}
