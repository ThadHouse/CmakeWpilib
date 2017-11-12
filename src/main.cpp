#include "CameraServer.h"
#include "networktables/NetworkTableInstance.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

int main() {
  auto ntInstance = nt::NetworkTableInstance::GetDefault();

  // Input team here to start
  ntInstance.StartClientTeam(9999);
  auto cameraServer = frc::CameraServer::GetInstance();
  cameraServer->AddAxisCamera("172.22.11.2:1181");

  auto cvSource = cameraServer->PutVideo("CvSource", 640, 480);
  auto cvSink = cameraServer->GetVideo("CvSink");

  cv::Mat input;
  cv::Mat hsv;

  while (true)
  {
    auto frameTime = cvSink.GrabFrame(input);
    if (!frameTime) continue;

    cv::cvtColor(input, hsv, cv::COLOR_BGR2HSV);

    cvSource.PutFrame(hsv);
  }


}
