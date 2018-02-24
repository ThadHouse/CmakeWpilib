#include "llvm/StringRef.h"
#include "ntcore.h"
#include <iostream>

#include <llvm/raw_ostream.h>
#include <cscore.h>
#include <opencv2/core.hpp>

int main() {
  auto inst = NT_GetDefaultInstance();
  (void)inst;
#ifndef _WIN32
  cs::UsbCamera camera{"usbcam", 0};
  camera.SetVideoMode(cs::VideoMode::kMJPEG, 320, 240, 30);
  cs::MjpegServer mjpegServer{"httpserver", 8081};
  mjpegServer.SetSource(camera);
  cs::CvSink cvsink{"cvsink"};
  cvsink.SetSource(camera);
  cs::CvSource cvsource{"cvsource", cs::VideoMode::kMJPEG, 320, 240, 30};
  cs::MjpegServer cvMjpegServer{"cvhttpserver", 8082};
  cvMjpegServer.SetSource(cvsource);

  cv::Mat test;
  cv::Mat flip;
  for (;;) {
    uint64_t time = cvsink.GrabFrame(test);
    if (time == 0) {
      std::cout << "error: " << cvsink.GetError() << std::endl;
      continue;
    }
    std::cout << "got frame at time " << time << " size " << test.size()
              << std::endl;
    cv::flip(test, flip, 0);
    cvsource.PutFrame(flip);
  }

  return 0;
#endif
}
